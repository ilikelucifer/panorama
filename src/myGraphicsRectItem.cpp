#include "myGraphicsRectItem.h"

MyGraphicsRectItem::MyGraphicsRectItem(QGraphicsItem *parent) :
QGraphicsRectItem(parent)
{
	setPen(QPen(QColor(255, 0, 255), 1)); setBrush(QBrush(Qt::transparent));
	oldx = 0, oldy = 0;

	activeMode = -1;
}


rectParam MyGraphicsRectItem::getStateParams()
{
	return { ox, oy, cw, ch };
}


QPoint MyGraphicsRectItem::getRectUpLeft()
{
	return QPoint(ox, oy);
}


int MyGraphicsRectItem::getRectWidth()
{
	return cw;
}


int MyGraphicsRectItem::getRectHeight()
{
	return ch;
}


bool MyGraphicsRectItem::isActive(QWheelEvent *event)
{
	QRect rec(ox*scale, oy*scale, cw*scale, ch*scale);

	if (rec.contains(event->x(), event->y()))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool MyGraphicsRectItem::isActive(QMouseEvent *event)
{
	QRect rec(ox*scale, oy*scale, cw * scale, ch * scale);

	if (rec.contains(event->x(), event->y()))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void MyGraphicsRectItem::setvisibility(bool v)
{
	this->setEnabled(v);
	this->setVisible(v);
}


void MyGraphicsRectItem::move(QPoint p)
{
	ox = p.x();
	oy = p.y();
	adjust();
}


void MyGraphicsRectItem::move(int x, int y)
{
	ox = x;
	oy = y;
	adjust();
}


void MyGraphicsRectItem::moveX(int x)
{
	ox = x;
	adjust();
}


void MyGraphicsRectItem::moveY(int y)
{
	oy = y;
	adjust();
}


void MyGraphicsRectItem::moveEdgeLeft(int x)
{
	int ox_old = ox;
	ox = x;
	cw += (ox_old - ox);
	adjust();
}


void MyGraphicsRectItem::moveEdgeRight(int x)
{
	cw = x - ox;
	adjust();
}


void MyGraphicsRectItem::moveEdgeUp(int y)
{
	int oy_old = oy;
	oy = y;
	ch += (oy_old - oy);
	adjust();
}


void MyGraphicsRectItem::moveEdgeDown(int y)
{
	ch = y - oy;
	adjust();
}


void MyGraphicsRectItem::zoom(double s)
{
	scale = s;
	adjust();
}


void MyGraphicsRectItem::reset(int a, int b, int w, int h, double s)
{
	ox = a, oy = b, cw = w, ch = h, scale = s;
	adjust();
}


void MyGraphicsRectItem::setMousePosInScene(QPointF sceneP)
{
	mouseScenePos = sceneP;
}


void MyGraphicsRectItem::wheelEvent(QWheelEvent *event)
{
	int distance = event->delta();
	int numDegrees = distance / 8;
	int numSteps = numDegrees / 15;

// 	cr += numSteps / scale;
// 	adjust();
}


void MyGraphicsRectItem::mousePressEvent(QMouseEvent *event)
{	
	int sense_range = 10;

	if (abs(mouseScenePos.x() - ox) < sense_range && mouseScenePos.y() > oy && mouseScenePos.y() < (oy + ch))//左边界
	{
		setCursor(Qt::SizeHorCursor);
		activeMode = 1;
	}
	else if (abs(mouseScenePos.x() - (ox + cw)) < sense_range && mouseScenePos.y() > oy && mouseScenePos.y() < (oy + ch))//右边界
	{
		setCursor(Qt::SizeHorCursor);
		activeMode = 2;
	}
	else if (abs(mouseScenePos.y() - oy) < sense_range && mouseScenePos.x() > ox && mouseScenePos.x() < (ox + cw))//上边界
	{
		setCursor(Qt::SizeVerCursor);
		activeMode = 3;
	}
	else if (abs(mouseScenePos.y() - (oy + ch)) < sense_range && mouseScenePos.x() > ox && mouseScenePos.x() < (ox + cw))//下边界
	{
		setCursor(Qt::SizeVerCursor);
		activeMode = 4;
	}
	else// if (this->contains(QPointF(event->x(), event->y())))
	{
		setCursor(Qt::ClosedHandCursor);
		activeMode = 0;
	}

	oldx = event->x();
	oldy = event->y();
	
}

void MyGraphicsRectItem::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->x();
	int y = event->y();

	if (event->buttons() == Qt::LeftButton)
	{
		int delta_x = x - oldx;
		int delta_y = y - oldy;
		
		switch (activeMode)
		{
		case 0:
		{
			setCursor(Qt::ClosedHandCursor);
			ox += (delta_x / scale); 
			oy += (delta_y / scale);		
			break;
		}
		case 1:
		{
			setCursor(Qt::SizeHorCursor);
			ox += (delta_x / scale); 
			cw -= (delta_x / scale); 
			break;
		}
		case 2:
		{
			setCursor(Qt::SizeHorCursor);
			cw += (delta_x / scale);
			break;
		}
		case 3:
		{
			setCursor(Qt::SizeVerCursor);
			oy += (delta_y / scale);
			ch -= (delta_y / scale);
			break;
		}
		case 4:
		{
			setCursor(Qt::SizeVerCursor);
			ch += (delta_y / scale);
			break;
		}
	
		}

		adjust();	
	}

	oldx = x;
	oldy = y;
}


void MyGraphicsRectItem::mouseReleaseEvent(QMouseEvent *event)
{
	setCursor(Qt::OpenHandCursor);
}


void MyGraphicsRectItem::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_W:
		oy -= 1;
		break;
	case Qt::Key_S:
		oy += 1;
		break;
	case Qt::Key_A:
		ox -= 1;
		break;
	case Qt::Key_D:
		ox += 1;
		break;
	}

	adjust();		
}


void MyGraphicsRectItem::adjust()
{
	double X = ox*scale;
	double Y = oy*scale;
	double W = cw*scale;
	double H = ch*scale;

	this->setRect(0, 0, W, H);
	this->setPos(X, Y);
}
