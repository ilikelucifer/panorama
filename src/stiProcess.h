#ifndef STIPROCESS_H
#define STIPROCESS_H

#include <fstream>
#include <string>
#include <sstream>
#include "stitchTest.h"
#include "algorithms.h"
 

#define IMG_NUM 2

using namespace std;
using namespace cv;


struct ImgCorrectParams
{
	double cx, cy, cr, ang;
};


class StiProcess
{

public:
	
	StiProcess(const string&img_path, const string& cam_path, const string& common_path, int size = 1500, double scale = 0.5, int test_mode = 0);
	~StiProcess();	
	
	Mat exec();
	
	void setFusionArgs(float seam_scale, int blend_layer, bool isexp);
	void setStiMode(int mode);
	void setStitchSize(int size);
	void setStitchScale(double scale);

	void loadMaps(const Mat& mapx, const Mat& mapy);


private:

	Mat execStitching();

	bool readCalibParams();
	bool processSingle(int idx);
	
	bool readCommonParams();


	//----------------���Ա����--------------
	string _commonPath; //�������������ļ�����Ŀ¼
	string _imgPath; //���ͼ���ļ�Ŀ¼
	string _camPath; //�����������ļ�Ŀ¼

	Mat _correctImg;
	Mat _HDmapX, _HDmapY;
	Mat _sHDmapX, _sHDmapY;
	Mat _panoImg;

	//����չ������
	vector<ImgCorrectParams> _correct_params;
	int _fuse_band;
	double _map_curve;
	double _crop_ratio;
	double _half_fov;

	vector<Mat> _imgs;

	float _seamScale;
	int _blendLayer;
	bool _isExposeComp;

	int _stitch_size;

	double _stitch_scale;

	int _testMode;

};





















#endif
