#include "renderwindow.h"
#include "ui_renderwindow.h"


RenderWindow::RenderWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::RenderWindow)
{
	ui->setupUi(this);

	setFixedSize(this->width(), this->height());

// 	setWindowFlags(Qt::CustomizeWindowHint);

	m_gl = new GLWidget(this);
	ui->scrollArea->setWidget(m_gl);

}

RenderWindow::~RenderWindow()
{
	delete ui;
	delete m_gl;
}


void RenderWindow::updatePanoImg(Mat &img)
{
	srcPanoImg = img;

	m_gl->loadPanoTexture(srcPanoImg);
	m_gl->updateGL();
}


void RenderWindow::showEvent(QShowEvent *e)
{
	QMainWindow::showEvent(e);
	m_gl->loadPanoTexture(srcPanoImg);
}



void RenderWindow::on_pushButton_resetView_clicked()
{
	m_gl->resetView();
}


void RenderWindow::on_pushButton_viewMode_clicked()
{
	m_gl->changeViewMode();
}


void RenderWindow::on_pushButton_workMode_clicked()
{
	emit panoImgChanged();
}


void RenderWindow::closeEvent(QCloseEvent *e)
{
	QMainWindow::closeEvent(e);

	emit windowClosed(true);
}
