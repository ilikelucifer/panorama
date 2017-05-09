#ifndef MYIMAGEVIEWRECT_H
#define MYIMAGEVIEWRECT_H

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


class MyImageViewRect : public QGraphicsView
{
	Q_OBJECT

public:
	explicit MyImageViewRect(int rectNum, QWidget* parent = 0);

	~MyImageViewRect();

	void setPixmap(QImage src);
	void loadPixmap(QString src_path_name);
	void addItem(QGraphicsItem *item);

	void reset(bool f);
	void resetImg(bool f);

	void resetRect(int idx);

	void setVisibility(bool v, int idx);
	void setVisibility(bool v);

private:


protected:

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);

signals:
	void rectMoved(QPoint t, int idx = 0);

	private slots:

	void setItemPos(QPoint t, int idx = 0);
	void setItemPosX(int x, int idx = 0);
	void setItemPosY(int y, int idx = 0);

	void setItemLeftEdge(int xL, int idx = 0);
	void setItemRightEdge(int xR, int idx = 0);
	void setItemUpEdge(int yU, int idx = 0);
	void setItemDownEdge(int yD, int idx = 0);

private:

	QGraphicsScene *_scene;
	QGraphicsPixmapItem *_graph;
	QPixmap _pixmap;
	QPixmap _pixmap_bk;

	vector<MyGraphicsRectItem*> _rects;

	int rect_num;

	int rect_acitve_idx;

	int oldx, oldy;
};


#endif