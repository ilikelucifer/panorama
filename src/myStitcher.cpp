#include "myStitcher.h"



MyStitcher MyStitcher::createDefault(double workScale, double seamScale, int blendLayer, bool try_use_gpu, bool exp_comp, bool is_wave)
{
	MyStitcher stitcher;

	stitcher.setSeamScale(seamScale);
	stitcher.setWorkScale(workScale);

	stitcher.setPanoConfidenceThresh(1.0);
	stitcher.setWaveCorrection(is_wave);
	stitcher.setWaveCorrectKind(detail::WAVE_CORRECT_HORIZ);
	stitcher.setFeaturesMatcher(new detail::BestOf2NearestMatcher(try_use_gpu));
	stitcher.setBundleAdjuster(new detail::BundleAdjusterRay());

#if defined(HAVE_OPENCV_GPU) && !defined(DYNAMIC_CUDA_SUPPORT)
	if (try_use_gpu && gpu::getCudaEnabledDeviceCount() > 0)
	{
#if defined(HAVE_OPENCV_NONFREE)
		stitcher.setFeaturesFinder(new detail::SurfFeaturesFinderGpu());
#else
		stitcher.setFeaturesFinder(new detail::OrbFeaturesFinder());
#endif
		stitcher.setWarper(new SphericalWarperGpu());
		stitcher.setSeamFinder(new detail::GraphCutSeamFinderGpu());
	}
	else
#endif
	{
#ifdef HAVE_OPENCV_NONFREE
		stitcher.setFeaturesFinder(new detail::SurfFeaturesFinder());
#else
		stitcher.setFeaturesFinder(new detail::OrbFeaturesFinder());
#endif
		stitcher.setWarper(new SphericalWarper());
		stitcher.setSeamFinder(new detail::GraphCutSeamFinder(detail::GraphCutSeamFinderBase::COST_COLOR));
	}

	stitcher.setExposureCompensator(new detail::BlocksGainCompensator());
	stitcher.setBlender(new detail::MultiBandBlender(try_use_gpu));

	stitcher.setExpComposeState(exp_comp);

	return stitcher;
}


MyStitcher::Status MyStitcher::estimateTransform(InputArray images, const vector<vector<Rect> > &rois)
{
	images.getMatVector(imgs_);
	rois_ = rois;

	Status status;

	if ((status = myMatchImages()) != OK)
		return status;

	estimateCameraParams(); //相机参数估计部分涉及到迭代优化算法，不能保证每次都能得到最优参数，需要多做几次才能成功，需要优化

	return OK;
}


MyStitcher::Status MyStitcher::myComposePanorama(OutputArray pano)
{
	//相机参数是否合理，需要做检查
#if 0
	for (int i = 0; i < imgs_.size(); ++i)
	{
		if (isnan<double>((double)cameras_[i].focal) || isnan<double>((double)cameras_[i].ppx) ||
			isnan<double>((double)cameras_[i].ppy) || isnan<double>((double)cameras_[i].aspect))
		{
			LOGLN("INNALID camera parameters occerd!");

			return ERR_INVALID_CAMERA_PARAM;
		}

		Mat R = cameras_[i].R;

		for (int m = 0; m < R.rows; ++m)
		{
			for (int n = 0; n < R.cols;++n)
			{
				if (isnan<double>(R.at<double>(m,n)))
				{
					LOGLN("INNALID camera parameters occerd!");

					return ERR_INVALID_CAMERA_PARAM;
				}
			}
		}		
	}
#endif


#if ENABLE_LOG
	LOGLN("Warping images (auxiliary)... ");
	int64 t = getTickCount();
#endif

	vector<Point> corners(imgs_.size());
	vector<Mat> masks_warped(imgs_.size());
	vector<Mat> images_warped(imgs_.size());
	vector<Size> sizes(imgs_.size());
	vector<Mat> masks(imgs_.size());

	// Prepare image masks
// #pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < imgs_.size(); ++i)
	{
		masks[i].create(seam_est_imgs_[i].size(), CV_8U);
		masks[i].setTo(Scalar::all(255));
	}

	// Warp images and their masks
	Ptr<detail::RotationWarper> w = warper_->create(float(warped_image_scale_ * seam_work_aspect_));

	for (int i = 0; i < imgs_.size(); ++i)
	{
		Mat_<float> K;
		cameras_[i].K().convertTo(K, CV_32F);
		K(0, 0) *= (float)seam_work_aspect_;//focus
		K(0, 2) *= (float)seam_work_aspect_;//focus
		K(1, 1) *= (float)seam_work_aspect_;//主点x
		K(1, 2) *= (float)seam_work_aspect_;//主点y

		corners[i] = w->warp(seam_est_imgs_[i], K, cameras_[i].R, INTER_LINEAR, BORDER_REFLECT, images_warped[i]);
		sizes[i] = images_warped[i].size();

		w->warp(masks[i], K, cameras_[i].R, INTER_NEAREST, BORDER_CONSTANT, masks_warped[i]);
	}


	vector<Mat> images_warped_f(imgs_.size());
// #pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < imgs_.size(); ++i)
		images_warped[i].convertTo(images_warped_f[i], CV_32F);

#if ENABLE_LOG
	LOGLN("Warping images, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");
#endif

	// Find seams
	if (is_exp_compose_)
	{
		exposure_comp_->feed(corners, images_warped, masks_warped);
	}
	seam_finder_->find(images_warped_f, corners, masks_warped);

	// Release unused memory
	seam_est_imgs_.clear();
	images_warped.clear();
	images_warped_f.clear();
	masks.clear();

	
#if ENABLE_LOG
	LOGLN("Compositing...");
	t = getTickCount();
#endif

	double compose_scale = 1;
	//
	double compose_work_aspect = compose_scale / work_scale_;

	// Update warped image scale
	warped_image_scale_ *= static_cast<float>(compose_work_aspect);
	w = warper_->create((float)warped_image_scale_);

	// Update corners and sizes
// #pragma omp parallel for schedule(dynamic)
	for (size_t i = 0; i < imgs_.size(); ++i)
	{
		// Update intrinsics
		cameras_[i].focal *= compose_work_aspect;
		cameras_[i].ppx *= compose_work_aspect;
		cameras_[i].ppy *= compose_work_aspect;

		Mat K;
		cameras_[i].K().convertTo(K, CV_32F);
		Rect roi = w->warpRoi(full_img_sizes_[i], K, cameras_[i].R);
		corners[i] = roi.tl();
		sizes[i] = roi.size();
	}

	blender_->prepare(corners, sizes);

	Mat img_warped, img_warped_s;
	Mat dilated_mask, seam_mask, mask, mask_warped;

	for (size_t img_idx = 0; img_idx < imgs_.size(); ++img_idx)
	{

#if ENABLE_LOG
		LOGLN("Compositing image #" << indices_[img_idx] + 1);
#endif
		Mat K;
		cameras_[img_idx].K().convertTo(K, CV_32F);

		// Warp the current image
		w->warp(imgs_[img_idx], K, cameras_[img_idx].R, INTER_LINEAR, BORDER_REFLECT, img_warped);

		// Warp the current image mask
		mask.create(imgs_[img_idx].size(), CV_8U);
		mask.setTo(Scalar::all(255));
		w->warp(mask, K, cameras_[img_idx].R, INTER_NEAREST, BORDER_CONSTANT, mask_warped);

		// Compensate exposure
		if (is_exp_compose_)
		{
			exposure_comp_->apply((int)img_idx, corners[img_idx], img_warped, mask_warped);
		}

		img_warped.convertTo(img_warped_s, CV_16S);
		img_warped.release();
		mask.release();

		// Make sure seam mask has proper size
		dilate(masks_warped[img_idx], dilated_mask, Mat());
		resize(dilated_mask, seam_mask, mask_warped.size());

		mask_warped = seam_mask & mask_warped;

		// Blend the current image
		blender_->feed(img_warped_s, mask_warped, corners[img_idx]);
	}

	Mat result, result_mask;
	blender_->blend(result, result_mask);

#if ENABLE_LOG
	LOGLN("Compositing, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");
#endif

	// Preliminary result is in CV_16SC3 format, but all values are in [0,255] range,
	// so convert it to avoid user confusing
	result.convertTo(pano, CV_8U);

	return OK;
}


MyStitcher::Status MyStitcher::stitch(InputArray images, const vector<vector<Rect> > &rois, OutputArray pano)
{
	Status status = estimateTransform(images, rois);
	if (status != OK)
		return status;

	return myComposePanorama(pano);
}


MyStitcher::Status MyStitcher::myMatchImages()
{
	features_.resize(imgs_.size());
	seam_est_imgs_.resize(imgs_.size());
	full_img_sizes_.resize(imgs_.size());

	LOGLN("Finding features...");
#if ENABLE_LOG
	int64 t = getTickCount();
#endif

	seam_work_aspect_ = seam_scale_ / work_scale_;

	for (int i = 0; i < imgs_.size(); ++i)
	{
		Mat img;

		full_img_sizes_[i] = imgs_[i].size();

		resize(imgs_[i], img, Size(), work_scale_, work_scale_);

		vector<Rect> rois(rois_[i].size());
		for (size_t j = 0; j < rois_[i].size(); ++j)
		{
			Point tl(cvRound(rois_[i][j].x * work_scale_), cvRound(rois_[i][j].y * work_scale_));
			Point br(cvRound(rois_[i][j].br().x * work_scale_), cvRound(rois_[i][j].br().y * work_scale_));
			rois[j] = Rect(tl, br);
		}
		(*features_finder_)(img, features_[i], rois);
		features_[i].img_idx = (int)i;
		LOGLN("Features in image #" << i + 1 << ": " << features_[i].keypoints.size());

		resize(imgs_[i], seam_est_imgs_[i], Size(), seam_scale_, seam_scale_);

	}

	// Do it to save memory
	features_finder_->collectGarbage();

	LOGLN("Finding features, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

	LOG("Pairwise matching");
#if ENABLE_LOG
	t = getTickCount();
#endif

	//自定义matchmask，因为知道图像拼接的序列
	Mat matchMask(features_.size(), features_.size(), CV_8U, Scalar::all(0));
	for (int i = 0; i < features_.size() - 1; ++i)
	{
		matchMask.at<char>(i, i + 1) = 1;
	}

	setMatchingMask(matchMask);

	(*features_matcher_)(features_, pairwise_matches_, matching_mask_);
	features_matcher_->collectGarbage();
	LOGLN("Pairwise matching, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

	// Leave only images we are sure are from the same panorama
	indices_ = detail::leaveBiggestComponent(features_, pairwise_matches_, (float)conf_thresh_);

	//自定义异常代码
	if (indices_.size() < imgs_.size())
	{
		cout << "can not find enough features to match the image series." << endl;
		return ERR_NO_ENOUGH_MATCH;
	}


	return OK;
}


void MyStitcher::estimateCameraParams()
{
	detail::HomographyBasedEstimator estimator;
	estimator(features_, pairwise_matches_, cameras_);

// #pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < cameras_.size(); ++i)
	{
		Mat R;
		cameras_[i].R.convertTo(R, CV_32F);
		cameras_[i].R = R;
		LOGLN("Initial intrinsic parameters #" << indices_[i] + 1 << ":\n " << cameras_[i].K());
	}

	bundle_adjuster_->setConfThresh(conf_thresh_);
	(*bundle_adjuster_)(features_, pairwise_matches_, cameras_);

	// Find median focal length and use it as final image scale
	vector<double> focals;
	for (size_t i = 0; i < cameras_.size(); ++i)
	{
		LOGLN("Camera #" << indices_[i] + 1 << ":\n" << cameras_[i].K());
		focals.push_back(cameras_[i].focal);
	}

	std::sort(focals.begin(), focals.end());
	if (focals.size() % 2 == 1)
		warped_image_scale_ = static_cast<float>(focals[focals.size() / 2]);
	else
		warped_image_scale_ = static_cast<float>(focals[focals.size() / 2 - 1] + focals[focals.size() / 2]) * 0.5f;

	//试验发现，波形校正容易导致相机参数出问题，考虑到我们只有三幅图像参与拼接，不需要做波形校正
	if (do_wave_correct_)
	{
		vector<Mat> rmats;
		for (size_t i = 0; i < cameras_.size(); ++i)
			rmats.push_back(cameras_[i].R);
		detail::waveCorrect(rmats, wave_correct_kind_);
		for (size_t i = 0; i < cameras_.size(); ++i)
			cameras_[i].R = rmats[i];
	}
}


//----------------------自定义函数-------------------
void MyStitcher::writeCameraParams(const string& name)
{
	FileStorage fs(name, FileStorage::WRITE);

	fs << "camera_param_list" << "[";

	for (int i = 0; i < cameras_.size(); ++i)
	{
		fs << "{:" << "focal" << cameras_[i].focal * work_scale_ << "aspect" << cameras_[i].aspect
			<< "principal" << "[:" << cameras_[i].ppx * work_scale_ << cameras_[i].ppy * work_scale_ << "]"
			<< "rotMat" << cameras_[i].R << "transMat" << cameras_[i].t  * work_scale_ << "}";
	}

	fs << "]";

	fs << "work_scale" << work_scale_;
	fs << "warped_image_scale" << warped_image_scale_;

	fs.release();

}



void MyStitcher::showMatches(const string& showName, float scale)
{
	for (int i = 0; i < pairwise_matches_.size(); ++i)
	{
		detail::MatchesInfo match_info = pairwise_matches_[i];
		if (match_info.dst_img_idx - match_info.src_img_idx == 1)
		{
// 			detail::ImageFeatures quary_img_feature = features_[match_info.src_img_idx];
// 			detail::ImageFeatures train_img_feature = features_[match_info.dst_img_idx];
// 
// 			vector<DMatch> new_matches;
// 			for (int k = 0; k < match_info.matches.size(); ++k)
// 			{
// 				DMatch match = match_info.matches[k];
// 				//inliers_mask为一个二值掩码，1表示匹配点对，0表示不是匹配点对
// 				if (match_info.inliers_mask[k] == 1) //当一对匹配点对的纵向误差很小（连线基本平行），说明是正确匹配点，如果发生交叉，则匹配错误
// 				{
// 					KeyPoint quary_pts = quary_img_feature.keypoints[match.queryIdx];
// 					KeyPoint train_pts = train_img_feature.keypoints[match.trainIdx];
// 
// 					if (fabs(quary_pts.pt.y - train_pts.pt.y) < 500)
// 					{
// 						new_matches.push_back(match);
// 					}
// 				}
// 			}

			Mat img_1, img_2, img_match;

			cv::resize(imgs_[match_info.src_img_idx], img_1, Size(), work_scale_, work_scale_); 
			cv::resize(imgs_[match_info.dst_img_idx], img_2, Size(), work_scale_, work_scale_); 

			drawMatches(img_1, features_[match_info.src_img_idx].keypoints, img_2, features_[match_info.dst_img_idx].keypoints, match_info.matches, img_match);
			
			ostringstream name;
			name << showName << match_info.src_img_idx << "-" << match_info.dst_img_idx;

			Mat imgscale;
			resize(img_match, imgscale, Size(), scale, scale);
			imshow(name.str(), imgscale);
		}
	}
}


//该函数会导致拼接错误，很多次出不来结果，还需要仔细研究
bool MyStitcher::refineMatch1(float thd)
{
// #pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < pairwise_matches_.size(); ++i)
	{
		detail::MatchesInfo match_info = pairwise_matches_[i];

		if (abs(match_info.src_img_idx - match_info.dst_img_idx) == 1)
		{
			//==================在此处添加内点过滤======================		
			detail::ImageFeatures quary_img_feature = features_[match_info.src_img_idx];
			detail::ImageFeatures train_img_feature = features_[match_info.dst_img_idx];

			vector<DMatch> new_matches;
			for (int k = 0; k < match_info.matches.size(); ++k)
			{
				DMatch match = match_info.matches[k];			
				//inliers_mask为一个二值掩码，1表示匹配点对，0表示不是匹配点对
				if (match_info.inliers_mask[k] == 1) //当一对匹配点对的纵向误差很小（连线基本平行），说明是正确匹配点，如果发生交叉，则匹配错误
				{
					KeyPoint quary_pts = quary_img_feature.keypoints[match.queryIdx];
					KeyPoint train_pts = train_img_feature.keypoints[match.trainIdx];

					if (fabs(quary_pts.pt.y - train_pts.pt.y) < thd)
					{

						new_matches.push_back(match);
					}
					
				}
			}

			pairwise_matches_[i].matches = new_matches;

		}
	}

	return true;
}


bool MyStitcher::refineMatch(float thd)
{
	// #pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < pairwise_matches_.size(); ++i)
	{
		detail::MatchesInfo match_info = pairwise_matches_[i];

		if (abs(match_info.src_img_idx - match_info.dst_img_idx) == 1)
		{
			//==================在此处添加内点过滤======================		
			detail::ImageFeatures quary_img_feature = features_[match_info.src_img_idx];
			detail::ImageFeatures train_img_feature = features_[match_info.dst_img_idx];

			for (int k = 0; k < match_info.matches.size(); ++k)
			{
				cout << match_info.matches.size();

				//inliers_mask为一个二值掩码，1表示匹配点对，0表示不是匹配点对
				if (match_info.inliers_mask[k] == 1) //当一对匹配点对的纵向误差很小（连线基本平行），说明是正确匹配点，如果发生交叉，则匹配错误
				{
					DMatch match = match_info.matches[k];

					KeyPoint quary_pts = quary_img_feature.keypoints[match.queryIdx];
					KeyPoint train_pts = train_img_feature.keypoints[match.trainIdx];

// 					float dist = fmaxf(fabs(quary_pts.pt.x - train_pts.pt.x), fabs(quary_pts.pt.y - train_pts.pt.y));

					if (fabs(quary_pts.pt.y - train_pts.pt.y) > thd)
					{
						match_info.inliers_mask[k] = 0;
						match_info.num_inliers--;
					}

				}
			}

			pairwise_matches_[i] = match_info;

		}
	}

	return true;
}
