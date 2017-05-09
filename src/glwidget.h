#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "glut.h"



using namespace cv;

#define pi (3.141592653f)
#define PANO_ROW 90
#define PANO_COL 180

class GLWidget : public QGLWidget
{
	Q_OBJECT

public:
	explicit GLWidget(QWidget *parent = 0);
	~GLWidget();

	void resetView();
	void changeViewMode();
	void setPanoMap();
	void loadPanoTexture(Mat& tex);
	void init();

	QPointF getMovement();


protected:
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void wheelEvent(QWheelEvent *event);



	private slots:


signals :

	void usrActive(bool);

private:

	void moveView(float x, float y, float scalar);
	void initializeGL();    // 初始化，通常用于设置一些前景色
	void paintGL();         // 渲染整个场景
	void resizeGL(int width, int height);   // 窗口大小变化时合理显示

	// 资源
	GLuint panoTexture;                      // 存储最终的全景图纹理

	//pano坐标
	float panoVerticeCoord[PANO_ROW + 1][PANO_COL + 1][3];
	float panoImageCoord[PANO_ROW + 1][PANO_COL + 1][2];

	int origPosX, origPosY;
	float hAngle, vAngle, xscale, yscale;

	float fov;

	bool isRealSense;//视角切换;

	QPointF mov;

};

#endif // GLWIDGET_H
