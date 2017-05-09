#include "stiProcess.h"

StiProcess::StiProcess(const string&img_path, const string& cam_path, const string& common_path, int size, double scale, int test_mode) :
_imgPath(img_path), _camPath(cam_path), _commonPath(common_path), _stitch_size(size), _stitch_scale(scale), _testMode(test_mode)
{

	//给定默认值
	_seamScale = 0.1;
	_blendLayer = 5;
	_stitch_size = 1500;
	_stitch_scale = 0.5;
	_testMode = 0;

}


StiProcess::~StiProcess()
{

}


void StiProcess::loadMaps(const Mat& mapx, const Mat& mapy)
{
	_HDmapX = mapx;
	_HDmapY = mapy;

	if (_HDmapX.empty() || _HDmapY.empty())
	{
		cout << "This are no valid base maps!" << endl;
	}
}


Mat StiProcess::exec()
{
	if (readCommonParams())
	{
		if (readCalibParams())
		{		
			return execStitching();
		}
	}

	return Mat();
}


void StiProcess::setStiMode(int mode)
{
	_testMode = mode;
}


void StiProcess::setStitchSize(int size)
{
	_stitch_size = size;
}


void StiProcess::setStitchScale(double scale)
{
	_stitch_scale = scale;
}


void StiProcess::setFusionArgs(float seam_scale, int blend_layer, bool isexp)
{
	_seamScale = seam_scale;
	_blendLayer = blend_layer;
	_isExposeComp = isexp;
}


Mat StiProcess::execStitching()
{
	int64 tic = cvGetTickCount();
	int64 toc;

	_sHDmapX.create(_stitch_size, _stitch_size * 2, CV_32FC1);
	_sHDmapY.create(_stitch_size, _stitch_size * 2, CV_32FC1);
	_correctImg.create(_stitch_size, _stitch_size * 2, IMG_FORMAT);

	_imgs.resize(IMG_NUM + 1);

	std::cout << "correcting begin ..." << endl;
	for (int i = 0; i < IMG_NUM; ++i)
	{
		if (!processSingle(i))
		{
			return Mat();
		}			
	}	

	//释放临时数组
	_sHDmapX.release(); _sHDmapY.release(); _correctImg.release();

	toc = cvGetTickCount();
	std::cout << "correcting accomplished, time elapsed: " + num2str<double>((double)(toc - tic) / getTickFrequency()) + " s. " << endl;

	//-------------stitch composepano-----------
	std::cout << "composing begin ..." << endl;
	tic = cvGetTickCount();

	Mat composPano;

	stitchTest mystitcher = stitchTest::creatDefault(true, _seamScale, _blendLayer, _testMode);
	mystitcher.setExposeureState(_isExposeComp);
	mystitcher.stitcher(_imgs, composPano, _camPath);

	//释放内存
	for (int i = 0; i < IMG_NUM + 1; ++i)
		_imgs[i].release();

	_imgs.clear();


	imgWarp_s(composPano, _panoImg, Size(_stitch_size * 2, _stitch_size), 500);

	toc = cvGetTickCount();
	std::cout << "composing accomplished, time elapsed: " + num2str<double>((double)(toc - tic) / getTickFrequency()) + " s. " << endl;

	return _panoImg;
}


bool StiProcess::processSingle(int idx)
{

	calcIndividualMap(_HDmapX, _HDmapY, _sHDmapX, _sHDmapY, _correct_params[idx].ang,
		_correct_params[idx].cx, _correct_params[idx].cy, _correct_params[idx].cr);

	Mat srcImg = imread(_imgPath + "/Image" + num2str<int>(idx + 1) + ".jpg");
	if (srcImg.empty())
	{
		std::cout << "can not find the correct image!" << endl;
		return false;
	}

	Mat scaleImg;
	resize(srcImg, scaleImg, Size(), _stitch_scale, _stitch_scale);
	srcImg.release();
	remap(scaleImg, _correctImg, _sHDmapX, _sHDmapY, IMG_INTER_METHOD);
	scaleImg.release();

	Mat img = _correctImg.colRange(_correctImg.cols*_crop_ratio, _correctImg.cols*(1.0 - _crop_ratio));

	if (idx == 0)
	{
		_imgs[0] = img.colRange(img.cols*0.5, img.cols).clone();
		_imgs[IMG_NUM] = img.colRange(0, img.cols*0.5).clone();
	}
	else
	{
		_imgs[idx] = img.clone();
	}

	return true;
}


bool StiProcess::readCommonParams()
{
	//载入calibration参数
	FileStorage fp;
	fp.open(_commonPath + "/common.xml", cv::FileStorage::READ);

	if (fp.isOpened())
	{		
		fp["correctCurve"] >> _map_curve;
		fp["halfFov"] >> _half_fov;
		_half_fov *= PI_OVER_180;
		fp["cropRatio"] >> _crop_ratio;

		fp.release();

		std::cout << "correct common parameters are loaded." << endl;

		return true;
	}
	else
	{
		std::cout << "can not find \"common.xml\" file!" << endl;
		return false;
	}
}


bool StiProcess::readCalibParams()
{
	//载入calibration参数
	FileStorage fp;
	fp.open(_camPath + "/calibration_2cam.xml", cv::FileStorage::READ);

	if (fp.isOpened())
	{
		FileNode cnode = fp["imgParam"];
		FileNodeIterator iter = cnode.begin();
		FileNodeIterator iter_end = cnode.end();

		_correct_params.clear();

		for (; iter != iter_end; iter++)
		{
			ImgCorrectParams cp;

			vector<double> var;
			(*iter)["param1"] >> var;
			cp.cx = var[0]*_stitch_scale; cp.cy = var[1] * _stitch_scale; cp.cr = var[2] * _stitch_scale;
			cp.ang = var[3] * PI_OVER_180;
			_correct_params.push_back(cp);
			var.clear();

			(*iter)["param2"] >> var;
			cp.cx = var[0] * _stitch_scale; cp.cy = var[1] * _stitch_scale; cp.cr = var[2] * _stitch_scale;
			cp.ang = var[3] * PI_OVER_180; 
			_correct_params.push_back(cp);
			var.clear();

		}

		fp.release();

		std::cout << "correct calibration parameters are loaded." << endl;

		return true;
	}
	else
	{
		std::cout << "can not find \"calibration_2cam.xml\" file!" << endl;
		return false;
	}
}


