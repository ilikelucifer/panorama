#include "glwidget.h"
#include <QtGui>
#include <QtCore>
#include <QtOpenGL>
#include <QOpenGLFunctions_1_0>


GLWidget::GLWidget(QWidget *parent) :
QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	setAutoBufferSwap(true);

	hAngle = 0;   vAngle = 0;
	xscale = 1.0f; yscale = 1.0f;
	origPosX = 0, origPosY = 0;

	isRealSense = true;
	fov = 60;

	mov = QPointF(0, 0);
}

GLWidget::~GLWidget()
{

}

QPointF GLWidget::getMovement()
{
	return mov;
}

void GLWidget::init()
{
	resetView();
	setPanoMap();
}

void GLWidget::resetView()
{
	hAngle = 0;   vAngle = 0;
	xscale = 1.0f; yscale = 1.0f;
	updateGL();
}

void GLWidget::initializeGL()
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);  // 设置着色模式，可为光滑着色或者恒定着色
	glClearColor(0, 0, 0, 0); // 清空当前所有色
	glClearDepth(1.0);        // 指定深度缓冲区的清除值
	glEnable(GL_DEPTH_TEST);  // 开启多项功能，此处为
	glDepthFunc(GL_LEQUAL);   // 启用深度测试。 根据坐标的远近自动隐藏被遮住的图形（材料）
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // 指定特定于实现的提示 此处为颜色和纹理坐标插补的质量
	glGenTextures(1, &panoTexture);

	init();
}


void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (isRealSense)
	{
		gluPerspective(fov, (float)width() / height(), 0, 10);
	}
	else
	{
		if (width() < height())
		{
			glOrtho(-1, 1, -(float)height() / width(), (float)height() / width(), -1, 1);
		}
		else
		{
			glOrtho(-(float)width() / height(), (float)width() / height(), -1, 1, -1, 1);
		}
	}

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();  //重置当前指定的矩阵为单位矩阵.
	glTranslatef(0.0, 0.0, 0.0); // 将绘制平面移动到屏幕的左半平面和里面
	if (!isRealSense)
	{
		glScalef(xscale, yscale, 1);
	}
	glRotatef(hAngle, 1, 0, 0);
	glRotatef(vAngle, 0, 1, 0);

	glBindTexture(GL_TEXTURE_2D, panoTexture);
	glBegin(GL_QUADS);
	for (int i = 0; i < PANO_ROW; i++)
	{
		for (int j = 0; j < PANO_COL; j++)
		{
			glTexCoord2f(panoImageCoord[i][j][0], panoImageCoord[i][j][1]);
			glVertex3f(panoVerticeCoord[i][j][0], panoVerticeCoord[i][j][1], panoVerticeCoord[i][j][2]);
			glTexCoord2f(panoImageCoord[i][j + 1][0], panoImageCoord[i][j + 1][1]);
			glVertex3f(panoVerticeCoord[i][j + 1][0], panoVerticeCoord[i][j + 1][1], panoVerticeCoord[i][j + 1][2]);
			glTexCoord2f(panoImageCoord[i + 1][j + 1][0], panoImageCoord[i + 1][j + 1][1]);
			glVertex3f(panoVerticeCoord[i + 1][j + 1][0], panoVerticeCoord[i + 1][j + 1][1], panoVerticeCoord[i + 1][j + 1][2]);
			glTexCoord2f(panoImageCoord[i + 1][j][0], panoImageCoord[i + 1][j][1]);
			glVertex3f(panoVerticeCoord[i + 1][j][0], panoVerticeCoord[i + 1][j][1], panoVerticeCoord[i + 1][j][2]);
		}
	}
	glEnd();

}


void GLWidget::resizeGL(int width, int height)
{
	if (0 == height)   height = 1;
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}



void GLWidget::moveView(float x, float y, float scalar)
{
	hAngle -= x; vAngle -= y;
	if (hAngle > 180)  hAngle = -180;
	if (hAngle < -180) hAngle = 180;

	updateGL();
}


void GLWidget::loadPanoTexture(Mat& tex)
{
	if (tex.empty())
	{
		qWarning("Cannot open pano image...");
		tex = Mat::zeros(128, 128, CV_8UC3);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, panoTexture);
		glPixelStorei(GL_UNPACK_ALIGNMENT, tex.step);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, tex.step / tex.channels());
		glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.cols, tex.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, tex.data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}


void GLWidget::setPanoMap()
{
#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < PANO_ROW + 1; i++)
	{
		float phi = (float)i / PANO_ROW * pi;
		for (int j = 0; j < PANO_COL + 1; j++)
		{
			float theta = pi / 2 + (float)j / PANO_COL * pi * 2;

			float R_xz = sin(phi);
			panoVerticeCoord[i][j][0] = R_xz*cos(theta);
			panoVerticeCoord[i][j][1] = cos(phi);
			panoVerticeCoord[i][j][2] = R_xz*sin(theta);

			panoImageCoord[i][j][0] = (float)j / (PANO_COL);
			panoImageCoord[i][j][1] = (float)i / (PANO_ROW);
		}
	}
}


void GLWidget::changeViewMode()
{
	isRealSense = !isRealSense;

	if (!isRealSense)
	{
		xscale = 1.0;
		yscale = 1.0;
	}

	updateGL();
}


void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
	emit usrActive(true);
	if (e->buttons() == Qt::LeftButton)
	{
		float delta_x = e->x() - origPosX;
		float delta_y = e->y() - origPosY;

		mov = QPointF(delta_x, delta_y);

		float x = delta_x * 90 / width();
		float y = delta_y * 90 / height();

		moveView(y, x, 1);
	}

	origPosX = e->x();
	origPosY = e->y();
}

void GLWidget::mousePressEvent(QMouseEvent *e)
{
	emit usrActive(true);
	origPosX = e->x();
	origPosY = e->y();
}


void GLWidget::wheelEvent(QWheelEvent *event)
{
	emit usrActive(true);
	int numDegrees = event->delta();
	while (numDegrees >= 120)
	{
		xscale *= 1.25; yscale *= 1.25;

		fov *= 1.1;
		fov = fov < 90 ? fov : 90;

		numDegrees -= 120;
	}
	while (numDegrees <= -120)
	{
		xscale *= 0.75; yscale *= 0.75;

		fov /= 1.1;
		fov = fov > 20 ? fov : 20;

		numDegrees += 120;
	}

	updateGL();
}

