#ifndef ALGORITHMS_H
#define ALGORITHMS_H

/*
	�㷨��
*/

#include <opencv2/opencv.hpp>
#include "myStitcher.h"
#include <iostream>

using namespace std;
using namespace cv;

#define PI (3.141592653)
#define PI_2 (1.5707963268)
#define PI_4 (0.78539816)
#define PI2 (6.28318530718)
#define PI_OVER_180 (0.0174532925199)

#define BLACKLINEOFF (0.71f)

#define IMG_FORMAT CV_8UC3
#define IMG_INTER_METHOD CV_INTER_LINEAR

enum LineDir
{
	VERTICAL_LEFT = 1,
	VERTICAL_RIGHT,
	HORIZONTAL_UP,
	HORIZONTAL_DOWN
};



//����ͼ��ü�
void fisheyeImgCrop(InputArray in, int cx, int cy, int cr, OutputArray out);

//����ͼ����ת
void fisheyeImgRotate(InputArray in, float angle, OutputArray out);

//��ֱͨ�����ɵ�ͼ��ߴ���ص�map
void calcCorrectMap(Size2i size, Mat& mapX, Mat& mapY, float mapCurve, float half_fov, float lat_angle, float lon_angle);
void calcCorrectMapTop(Size2i size, Mat& mapX, Mat& mapY, float mapCurve, float half_fov);

//���ɱ�׼��һ�������ĵĹ���map
void calcStandardMap(Size2i size, Mat& mapX, Mat& mapY, float mapCurve, float half_fov, float lat_angle, float lon_angle);
void calcStandardMapTop(Size2i size, Mat& mapX, Mat& mapY, float mapCurve, float half_fov);

void calcIndividualMap(InputArray mapXIn, InputArray mapYIn, OutputArray mapXOut, OutputArray mapYOut, double angle, double centerX, double centerY, double R); //���ݱ�׼map�������ͼ����Ի���У��map


void imgFuser(InputArray in, OutputArray out, Size2i size, int pos1, int pos2, float delta, bool gaussf = true);

void generateGaussKernel(float delta, int R, float*gaussKernel);

//�жϰ뾶�ص�����ƽ��
float bandMatcher(InputArray in, int pos, int band, float begin, float end, int& trans, int method=0, bool debug=false);

//���ͼ������Ӧ��ֵ��ֵ��
int otsu(InputArray in);

//ɨ���߷�Ѱ��Բ�ĳ�ʼλ��
Point3f findCenterByScan(InputArray in, int gray_thd, int sensity, bool debug, string name = "result");


Vec3f rotateWithAxis(Vec3f in, Vec3f axis, float angle);
void sphericalTrans(float lat_in, float lon_in, Vec3f axis, float angle, float &lat_out, float &lon_out);


Vec3b bilinearInterpolate(InputArray in, Point2f pos, Size2i size);

void imgHorizontalMove(InputArray in, OutputArray out, int mov);

void imgVerticalMove(InputArray in, OutputArray out, int mov);

void imgMove(InputArray in, OutputArray out, int movx, int movy);

void imgMaskFilter(InputArray in, InputArray mask, OutputArray out);

void imgSlopeEdgeHorizon(InputArray in, int startLine, int edgeWidth, int dir, OutputArray out);

void imgSlopeEdgeVertical(InputArray in, int startLine, int edgeWidth, int dir, OutputArray out);

void imgSlopeEdge(InputArray in, int startLine, int fuseRadius, LineDir dir, OutputArray out);

bool imgStitcher(InputArray in, OutputArray pano, const vector<vector<Rect> > &rois, 
	double workScale = 0.5, double seamScale = 0.1, int blendLayer = 5, const string& xml_name = "", 
	float show_scale = 0.2, bool useGPU = false, bool isExpComp = false, bool is_wave = false, bool showDebug = false);


void showImg(const string& name, InputArray img, float scale = 1.0);

void imgWarp(InputArray in, OutputArray out, Size size, int searchRange = 200, int offRange = 10, int darkNumThd = 10, bool debug = false);

void imgWarp_s(InputArray in, OutputArray out, Size size, int searchRange = 200, bool debug = false);


template<class T>
string num2str(T val)
{
	stringstream ss;
	string str;

	ss << val;
	ss >> str;

	return str;
}


#endif // !ALGORITHMS_H
