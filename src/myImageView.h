#ifndef MYIMAGEVIEW_H
#define MYIMAGEVIEW_H

#include <QGraphicsView>
#include <QApplication>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QScrollBar>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <math.h>
#include "myGraphicsEllipseItem.h"
#include "myGraphicsRectItem.h"
#include <iostream>
#include <vector>

using namespace std;


class MyImageView : public QGraphicsView
{
	Q_OBJECT

public:
	explicit MyImageView(int circleNum = 0, QWidget* parent = 0);

	~MyImageView();

	void setPixmap(QImage src);
	void loadPixmap(QString src_path_name);
	void addItem(QGraphicsItem *item);

	void reset(bool f);
	void resetImg(bool f);
	
	void resetCircle(int idx);

	void setVisibility(bool v, int idx);
	void setVisibility(bool v);
	void setItemMovable(bool v, int idx);
	void setItemMovable(bool v);

private:


protected:

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);

signals:
	void circleMoved(QPointF t, int idx = 0);
	void circleResized(double r, int idx = 0);

private slots:
	
void setItemPos(QPointF t, int idx = 0);
void setItemSize(double r, int idx = 0);
void setItemPosX(double x, int idx = 0);
void setItemPosY(double y, int idx = 0);

private:

	QGraphicsScene *_scene;
	QGraphicsPixmapItem *_graph;
	QPixmap _pixmap;
	QPixmap _pixmap_bk;

	vector<MyGraphicsEllipseItem*> _circles;

// 	vector<QPointF> _accPos; //累计圆心位置
// 	vector<double> _accRadius;	//累计半径

	int circle_num;

	int circle_acitve_idx;

	int oldx, oldy;

	bool itemMovable;
};


#endif