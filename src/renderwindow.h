#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QtOpenGL>
#include "glwidget.h"
#include "algorithms.h"

using namespace std;

namespace Ui{
	class RenderWindow;
}

class RenderWindow :public QMainWindow
{
	Q_OBJECT

public:
	explicit RenderWindow(QWidget *parent = 0);
	~RenderWindow();

	GLWidget *m_gl;

	void updatePanoImg(Mat &img);

protected:
	void showEvent(QShowEvent *e);
	void closeEvent(QCloseEvent *e);


signals:
	void windowClosed(bool f);
	void panoImgChanged();

private slots:
	
	void on_pushButton_resetView_clicked();
	void on_pushButton_viewMode_clicked();
	void on_pushButton_workMode_clicked();

private:

	Mat srcPanoImg;

	Ui::RenderWindow *ui;
};









#endif