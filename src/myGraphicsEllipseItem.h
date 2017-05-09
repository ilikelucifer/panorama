#ifndef MYGRAPHICSELLIPSEITEM_H
#define MYGRAPHICSELLIPSEITEM_H

#include <QObject>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QGraphicsView>

struct circleParam
{
	double x, y;
	double r;
};

class MyGraphicsEllipseItem : public QGraphicsEllipseItem
{

public:

	explicit MyGraphicsEllipseItem(QGraphicsEllipseItem *parent = 0);

	void reset(double a, double b, double r, double s);
	void setvisibility(bool v);
	void setMovable(bool v);

	void move(QPointF p);
	void move(double x, double y);
	void moveX(double x);
	void moveY(double y);
	void zoom(double s);
	void resize(double r);

	circleParam getStateParams();

	QPointF getCenterPos();

	double getRadius();

private:
	
	void adjust();

public:

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);

private:

	double  cx, cy, cr;

	double scale;

	int oldx, oldy;

	bool movable;

};

#endif // MyGraphicsEllipseItem_H