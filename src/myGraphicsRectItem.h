#ifndef MYGRAPHICSRECTITEM_H
#define MYGRAPHICSRECTITEM_H

#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsEllipseItem>
#include <QApplication>
#include <QGraphicsView>

struct rectParam
{
	int x, y, w, h;
};

class MyGraphicsRectItem : public QGraphicsRectItem
{

public:

	explicit MyGraphicsRectItem(QGraphicsItem *parent = 0);

	void reset(int a, int b, int w, int h, double s);
	void setvisibility(bool v);

	void move(QPoint p);
	void move(int x, int y);
	void moveX(int x);
	void moveY(int y);
	void moveEdgeLeft(int x);
	void moveEdgeRight(int x);
	void moveEdgeUp(int y);
	void moveEdgeDown(int y);

	void setMousePosInScene(QPointF sceneP);

	void zoom(double s);

	bool isActive(QWheelEvent *event);
	bool isActive(QMouseEvent *event);

	rectParam getStateParams();

	QPoint getRectUpLeft();

	int getRectWidth();
	int getRectHeight();

private:
	
	void adjust();

public:

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);

private:

	int  ox, oy, cw, ch;

	double scale;

	int oldx, oldy;

	int activeMode;

	QPointF mouseScenePos;

};

#endif // MYGRAPHICSRECTITEM_H