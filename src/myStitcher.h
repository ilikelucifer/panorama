#ifndef MYSTITCHER_H
#define MYSTITCHER_H



#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/stitcher.hpp"
#include "opencv2/stitching/warpers.hpp"
#include "opencv2/nonfree/features2d.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

#define CALC_POWER (18e6)



class MyStitcher
{
public:
	enum { ORIG_RESOL = -1 };
	enum Status { OK, ERR_NEED_MORE_IMGS, ERR_NO_ENOUGH_MATCH, ERR_INVALID_CAMERA_PARAM};

	// Creates stitcher with default parameters
	static MyStitcher createDefault(double workScale = 0.6, double seamScale = 0.1, 
		int blendLayer = 5, bool try_use_gpu = false, bool exp_comp = false, bool is_wave = false);


	double panoConfidenceThresh() const { return conf_thresh_; }
	void setPanoConfidenceThresh(double conf_thresh) { conf_thresh_ = conf_thresh; }

	bool waveCorrection() const { return do_wave_correct_; }
	void setWaveCorrection(bool flag) { do_wave_correct_ = flag; }

	detail::WaveCorrectKind waveCorrectKind() const { return wave_correct_kind_; }
	void setWaveCorrectKind(detail::WaveCorrectKind kind) { wave_correct_kind_ = kind; }

	Ptr<detail::FeaturesFinder> featuresFinder() { return features_finder_; }
	const Ptr<detail::FeaturesFinder> featuresFinder() const { return features_finder_; }
	void setFeaturesFinder(Ptr<detail::FeaturesFinder> features_finder)
	{
		features_finder_ = features_finder;
	}

	Ptr<detail::FeaturesMatcher> featuresMatcher() { return features_matcher_; }
	const Ptr<detail::FeaturesMatcher> featuresMatcher() const { return features_matcher_; }
	void setFeaturesMatcher(Ptr<detail::FeaturesMatcher> features_matcher)
	{
		features_matcher_ = features_matcher;
	}

	const cv::Mat& matchingMask() const { return matching_mask_; }
	void setMatchingMask(const cv::Mat &mask)
	{
		CV_Assert(mask.type() == CV_8U && mask.cols == mask.rows);
		matching_mask_ = mask.clone();
	}

	Ptr<detail::BundleAdjusterBase> bundleAdjuster() { return bundle_adjuster_; }
	const Ptr<detail::BundleAdjusterBase> bundleAdjuster() const { return bundle_adjuster_; }
	void setBundleAdjuster(Ptr<detail::BundleAdjusterBase> bundle_adjuster)
	{
		bundle_adjuster_ = bundle_adjuster;
	}

	Ptr<WarperCreator> warper() { return warper_; }
	const Ptr<WarperCreator> warper() const { return warper_; }
	void setWarper(Ptr<WarperCreator> creator) { warper_ = creator; }

	Ptr<detail::ExposureCompensator> exposureCompensator() { return exposure_comp_; }
	const Ptr<detail::ExposureCompensator> exposureCompensator() const { return exposure_comp_; }
	void setExposureCompensator(Ptr<detail::ExposureCompensator> exposure_comp)
	{
		exposure_comp_ = exposure_comp;
	}

	Ptr<detail::SeamFinder> seamFinder() { return seam_finder_; }
	const Ptr<detail::SeamFinder> seamFinder() const { return seam_finder_; }
	void setSeamFinder(Ptr<detail::SeamFinder> seam_finder) { seam_finder_ = seam_finder; }

	Ptr<detail::Blender> blender() { return blender_; }
	const Ptr<detail::Blender> blender() const { return blender_; }
	void setBlender(Ptr<detail::Blender> b) { blender_ = b; }

	Status estimateTransform(InputArray images, const std::vector<std::vector<Rect> > &rois);

	Status stitch(InputArray images, const std::vector<std::vector<Rect> > &rois, OutputArray pano);

	std::vector<int> component() const { return indices_; }
	std::vector<detail::CameraParams> cameras() const { return cameras_; }
	double workScale() const { return work_scale_; }


	//----------------------------自定义函数------------------------
	void setSeamScale(double seam_scale){ seam_scale_ = seam_scale; }
	void setWorkScale(double work_scale){ work_scale_ = work_scale; }
	void setExpComposeState(bool is_comp){ is_exp_compose_ = is_comp; }

	double seamScale() const { return seam_scale_; };

	void writeCameraParams(const string& name = "");

	void showMatches(const string& showName = "match", float scale = 0.2);

	bool refineMatch(float thd = 300);
	bool refineMatch1(float thd = 300);

	Status myComposePanorama(OutputArray pano);


private:
	MyStitcher() {}

	Status myMatchImages();

	void estimateCameraParams();

	double conf_thresh_;
	Ptr<detail::FeaturesFinder> features_finder_;
	Ptr<detail::FeaturesMatcher> features_matcher_;
	cv::Mat matching_mask_;
	Ptr<detail::BundleAdjusterBase> bundle_adjuster_;
	bool do_wave_correct_;
	detail::WaveCorrectKind wave_correct_kind_;
	Ptr<WarperCreator> warper_;
	Ptr<detail::ExposureCompensator> exposure_comp_;
	Ptr<detail::SeamFinder> seam_finder_;
	Ptr<detail::Blender> blender_;

	std::vector<cv::Mat> imgs_;
	std::vector<std::vector<cv::Rect> > rois_;
	std::vector<cv::Size> full_img_sizes_;
	std::vector<detail::ImageFeatures> features_;
	std::vector<detail::MatchesInfo> pairwise_matches_;
	std::vector<cv::Mat> seam_est_imgs_;
	std::vector<int> indices_;
	std::vector<detail::CameraParams> cameras_;
	double work_scale_;
	double seam_scale_;
	double seam_work_aspect_;
	double warped_image_scale_;

	bool is_exp_compose_;
};





#endif