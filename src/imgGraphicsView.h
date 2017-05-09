#ifndef IMGGRAPHICSVIEW_H
#define IMGGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QMouseEvent>
#include <QScrollBar>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QApplication>



class ImgGraphicsView: public QGraphicsView
{
	Q_OBJECT

public:
	explicit ImgGraphicsView(QWidget* parent = 0);
	

	void setPixmap(QImage src);
	void loadPixmap(QString src_path_name);
	void resetImg(bool f);

// 	void setAccPos();
// 	void setAccAngle();
	QPointF getAccPos();
	double getAccAngle();
	QPointF getAccTransPos();

	void resetPos();
	void resetAng();
	void resetTransPos();

protected:

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void wheelEvent(QWheelEvent *event);


signals:

	void mouseMoved(QPointF t);
	void mouseRotate(double ang);
	void mouseTransMoved(QPointF t);

private slots:

	void on_AccPos_changed(QPointF p);
	void on_AccPosX_changed(double x);
	void on_AccPosY_changed(double y);
	void on_AccAngle_changed(double a);
	void on_AccTransPosX_changed(double x);
	void on_AccTransPosY_changed(double y);

private:

	QGraphicsScene *_scene;
	QGraphicsPixmapItem *_graph;
	QPixmap _pixmap;
	QPixmap _pixmap_bk;

	QPointF _imgCenter; 

	QPointF accPos;
	QPointF accTransPos;
	double accAng;

	int oldx, oldy;
};


#endif