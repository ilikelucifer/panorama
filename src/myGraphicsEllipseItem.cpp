#include "myGraphicsEllipseItem.h"

MyGraphicsEllipseItem::MyGraphicsEllipseItem(QGraphicsEllipseItem *parent) :
QGraphicsEllipseItem(parent)
{
	setPen(QPen(QColor(255, 0, 255), 1)); setBrush(QBrush(Qt::transparent));
	oldx = 0, oldy = 0;

	movable = true;
}


circleParam MyGraphicsEllipseItem::getStateParams()
{
	return { cx, cy, cr };
}


QPointF MyGraphicsEllipseItem::getCenterPos()
{
	return QPointF(cx, cy);
}


double MyGraphicsEllipseItem::getRadius()
{
	return cr;
}


void MyGraphicsEllipseItem::setvisibility(bool v)
{
	this->setEnabled(v);
	this->setVisible(v);
}


void MyGraphicsEllipseItem::setMovable(bool v)
{
	movable = v;
}


void MyGraphicsEllipseItem::move(QPointF p)
{
	cx = p.x();
	cy = p.y();
	adjust();
}


void MyGraphicsEllipseItem::move(double x, double y)
{
	cx = x;
	cy = y;
	adjust();
}


void MyGraphicsEllipseItem::moveX(double x)
{
	cx = x;
	adjust();
}


void MyGraphicsEllipseItem::moveY(double y)
{
	cy = y;
	adjust();
}


void MyGraphicsEllipseItem::zoom(double s)
{
	scale = s;
	adjust();
}


void MyGraphicsEllipseItem::resize(double r)
{
	cr = r;
	adjust();
}


void MyGraphicsEllipseItem::reset(double a, double b, double r, double s)
{
	cx = a, cy = b, cr = r, scale = s;
	adjust();
}


void MyGraphicsEllipseItem::wheelEvent(QWheelEvent *event)
{
	if (movable)
	{
		int distance = event->delta();
		int numDegrees = distance / 8;
		int numSteps = numDegrees / 15;

		cr += numSteps / scale;
		adjust();
	}
}


void MyGraphicsEllipseItem::mousePressEvent(QMouseEvent *event)
{
	if (movable)
	{
		setCursor(Qt::ClosedHandCursor);

		oldx = event->x();
		oldy = event->y();
	}
		
}

void MyGraphicsEllipseItem::mouseMoveEvent(QMouseEvent *event)
{
	if (movable)
	{
		int x = event->x();
		int y = event->y();

		if (event->buttons() == Qt::LeftButton)
		{
			int delta_x = x - oldx;
			int delta_y = y - oldy;

			setCursor(Qt::ClosedHandCursor);
			cx += (delta_x / scale); cy += (delta_y / scale);
			adjust();
		}

		oldx = x;
		oldy = y;
	}
}


void MyGraphicsEllipseItem::mouseReleaseEvent(QMouseEvent *event)
{
	if (movable)
	{
		setCursor(Qt::OpenHandCursor);
	}
}


void MyGraphicsEllipseItem::keyPressEvent(QKeyEvent *event)
{
	if (movable)
	{
		switch (event->key())
		{
		case Qt::Key_W:
			cy -= 1;
			break;
		case Qt::Key_S:
			cy += 1;
			break;
		case Qt::Key_A:
			cx -= 1;
			break;
		case Qt::Key_D:
			cx += 1;
			break;
		}

		adjust();
	}
}


void MyGraphicsEllipseItem::adjust()
{
	double X = (cx - cr)*scale;
	double Y = (cy - cr)*scale;
	double R = cr * 2 * scale;

	this->setRect(0, 0, R, R);
	this->setPos(X, Y);
}
