#include "myImageViewRect.h"

MyImageViewRect::MyImageViewRect(int rectNum, QWidget* parent) :
QGraphicsView(parent)
{
	setMouseTracking(false);
	setCursor(Qt::OpenHandCursor);

	setAlignment(Qt::AlignCenter);

	_scene = new QGraphicsScene();
	_scene->setBackgroundBrush(Qt::black);

	this->setScene(_scene);

	_graph = new QGraphicsPixmapItem();

	_scene->addItem(_graph);

	rect_num = 0;

	rect_acitve_idx = -1;

	for (int i = 0; i < rectNum; ++i)
	{
		MyGraphicsRectItem *rect = new MyGraphicsRectItem();
		rect->setPen(QPen(QColor(rand() % 256, rand() % 256, rand() % 256), 1));
		_rects.push_back(rect);
		_scene->addItem(_rects[rect_num]);
		rect_num++;
	}

	oldx = 0; oldy = 0;
}


MyImageViewRect::~MyImageViewRect()
{

}


void MyImageViewRect::setVisibility(bool v, int idx)
{
	if (idx >= 0 && idx < rect_num)
	{
		_rects[idx]->setvisibility(v);
	}
}


void MyImageViewRect::setVisibility(bool v)
{
	for (int i = 0; i < rect_num; ++i)
	{
		_rects[i]->setvisibility(v);
	}
}


void MyImageViewRect::resetImg(bool f)
{
	if (f)
	{
		_scene->setSceneRect(0, 0, _pixmap_bk.width(), _pixmap_bk.height());
		_pixmap = _pixmap_bk.scaled(QSize(_scene->width(), _scene->height()));
		_graph->setPixmap(_pixmap);
	}
	else
	{
		float width = this->width();
		float height = this->height();

		float scale_w = width / _pixmap_bk.width();
		float scale_h = height / _pixmap_bk.height();

		if (scale_w < scale_h)
		{
			_scene->setSceneRect(0, 0, this->width() - 4, int(_pixmap_bk.height()*(this->width() - 4) / _pixmap_bk.width()));
			_pixmap = _pixmap_bk.scaled(QSize(_scene->width(), _scene->height()));

		}
		else
		{
			_scene->setSceneRect(0, 0, int(_pixmap_bk.width()*(this->height() - 4) / _pixmap_bk.height()), this->height() - 4);
			_pixmap = _pixmap_bk.scaled(QSize(_scene->width(), _scene->height()));

		}

		_graph->setPixmap(_pixmap);
	}
}


void MyImageViewRect::resetRect(int idx)
{
	if (idx >= 0 && idx < rect_num)
	{
		//ÉèÖÃÔ²µÄÎ»ÖÃ
		double r = fmin(_pixmap_bk.width(), _pixmap_bk.height());
		double w = r*0.5;
		double h = r*0.6;
		double x = _pixmap_bk.width()*0.1;
		double y = _pixmap_bk.height()*0.1;
		double s = (double)_pixmap.width() / _pixmap_bk.width();

		int x_rand = rand() % 100; int y_rand = rand() % 100;

		_rects[idx]->reset(x + x_rand, y + y_rand, w, h, s);

		emit rectMoved(_rects[idx]->getRectUpLeft(), idx);
	}
}


void MyImageViewRect::reset(bool f)
{
	resetImg(f);

	for (int i = 0; i < rect_num; ++i)
	{
		resetRect(i);
	}
}


void MyImageViewRect::setPixmap(QImage src)
{
	_pixmap_bk = QPixmap::fromImage(src);
	_pixmap = QPixmap::fromImage(src);

	reset(false);
}


void MyImageViewRect::loadPixmap(QString src_path_name)
{
	_pixmap_bk.load(src_path_name);
	_pixmap.load(src_path_name);

	reset(false);
}


void MyImageViewRect::addItem(QGraphicsItem *item)
{
	_scene->addItem(item);
}


void MyImageViewRect::wheelEvent(QWheelEvent *event)
{
	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		int distance = event->delta();
		int numDegrees = distance / 8;
		int numSteps = numDegrees / 15;

		double scale = pow(1.2, numSteps);

		_scene->setSceneRect(0, 0, _scene->width() * scale, _scene->height() * scale);
		_pixmap = _pixmap_bk.scaled(QSize(_scene->width(), _scene->height()));
		_graph->setPixmap(_pixmap);

		double s = (double)_pixmap.width() / _pixmap_bk.width();

		for (int i = 0; i < rect_num; ++i)
		{
			_rects[i]->zoom(s);
		}
	}
	else
	{
// 		for (int i = 0; i < rect_num; ++i)
// 		{
// 			if (_rects[i]->isActive(event))
// 			{
// 				_rects[i]->wheelEvent(event);
// 				break;
// 			}
// 		}
	}
}


void MyImageViewRect::mousePressEvent(QMouseEvent *event)
{
	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		setCursor(Qt::ClosedHandCursor);
		oldx = event->x();
		oldy = event->y();
	}
	else
	{
		rect_acitve_idx = -1;

		QPointF p = mapToScene(event->pos());
		QTransform transf;
		QGraphicsItem *gp = _scene->itemAt(p, transf);
		for (int i = 0; i < rect_num; ++i)
		{
			if (gp == _rects[i])
			{
				_rects[i]->setMousePosInScene(p);
				rect_acitve_idx = i;
				_rects[i]->mousePressEvent(event);
				break;
			}
		}
	}
}


void MyImageViewRect::mouseMoveEvent(QMouseEvent *event)
{
	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		setCursor(Qt::ClosedHandCursor);

		int x = event->x();
		int y = event->y();

		if (event->buttons() == Qt::LeftButton)
		{
			int delta_x = x - oldx;
			int delta_y = y - oldy;

			int vx = this->horizontalScrollBar()->value();
			int vy = this->verticalScrollBar()->value();

			this->horizontalScrollBar()->setValue(vx - delta_x);
			this->verticalScrollBar()->setValue(vy - delta_y);
		}

		oldx = x;
		oldy = y;
	}
	else
	{
		if (rect_acitve_idx >= 0)
		{
			_rects[rect_acitve_idx]->mouseMoveEvent(event);
			emit rectMoved(_rects[rect_acitve_idx]->getRectUpLeft(), rect_acitve_idx);
		}

	}
}


void MyImageViewRect::mouseReleaseEvent(QMouseEvent *event)
{
	setCursor(Qt::OpenHandCursor);
	for (int i = 0; i < rect_num; ++i)
	{
		_rects[i]->mouseReleaseEvent(event);
	}
}


void MyImageViewRect::keyPressEvent(QKeyEvent *event)
{
	int step = 10;

	int vx = this->horizontalScrollBar()->value();
	int vy = this->verticalScrollBar()->value();

	switch (event->key())
	{
	case Qt::Key_Up:
		this->verticalScrollBar()->setValue(vy - step);
		break;
	case Qt::Key_Down:
		this->verticalScrollBar()->setValue(vy + step);
		break;
	case Qt::Key_Left:
		this->horizontalScrollBar()->setValue(vx - step);
		break;
	case Qt::Key_Right:
		this->horizontalScrollBar()->setValue(vx + step);
		break;
	case Qt::Key_R:
	{
		resetImg(false);
		double s = (double)_pixmap.width() / _pixmap_bk.width();
		for (int i = 0; i < rect_num; ++i)
		{
			_rects[i]->zoom(s);
		}
		break;
	}
	case Qt::Key_Q:
	{
		resetImg(true);
		double s = (double)_pixmap.width() / _pixmap_bk.width();
		for (int i = 0; i < rect_num; ++i)
		{
			_rects[i]->zoom(s);
		}
		break;
	}

	}

	if (rect_acitve_idx >= 0)
	{
		_rects[rect_acitve_idx]->keyPressEvent(event);
		emit rectMoved(_rects[rect_acitve_idx]->getRectUpLeft(), rect_acitve_idx);
	}
}


void MyImageViewRect::setItemPos(QPoint t, int idx)
{
	if (idx >= 0 && idx < rect_num)
	{
		_rects[idx]->move(t);
	}
}


void MyImageViewRect::setItemPosX(int x, int idx)
{
	if (idx >= 0 && idx < rect_num)
	{
		_rects[idx]->moveX(x);
	}
}


void MyImageViewRect::setItemPosY(int y, int idx)
{
	if (idx >= 0 && idx < rect_num)
	{
		_rects[idx]->moveY(y);
	}
}
 

void MyImageViewRect::setItemLeftEdge(int xL, int idx)
{
	if (idx >= 0 && idx < rect_num)
	{
		_rects[idx]->moveEdgeLeft(xL);
	}
}


void MyImageViewRect::setItemRightEdge(int xR, int idx)
{
	if (idx >= 0 && idx < rect_num)
	{
		_rects[idx]->moveEdgeRight(xR);
	}
}


void MyImageViewRect::setItemUpEdge(int yU, int idx)
{
	if (idx >= 0 && idx < rect_num)
	{
		_rects[idx]->moveEdgeUp(yU);
	}
}


void MyImageViewRect::setItemDownEdge(int yD, int idx)
{
	if (idx >= 0 && idx < rect_num)
	{
		_rects[idx]->moveEdgeDown(yD);
	}
}