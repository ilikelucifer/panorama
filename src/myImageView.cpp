#include "myImageView.h"

MyImageView::MyImageView(int circleNum, QWidget* parent) :
QGraphicsView(parent)
{
	setMouseTracking(false);
	setCursor(Qt::OpenHandCursor);

	setAlignment(Qt::AlignCenter);

	_scene = new QGraphicsScene();
	_scene->setBackgroundBrush(Qt::gray);

	this->setScene(_scene);

	_graph = new QGraphicsPixmapItem();

	_scene->addItem(_graph);

	circle_num = 0;

	circle_acitve_idx = -1;

	for (int i = 0; i < circleNum; ++i)
	{
		MyGraphicsEllipseItem *circle = new MyGraphicsEllipseItem();
		circle->setPen(QPen(QColor(rand() % 256, rand() % 256, rand() % 256), 1));
		_circles.push_back(circle);


		_scene->addItem(_circles[circle_num]);
		circle_num++;
	}
	
	oldx = 0; oldy = 0;

	itemMovable = true;
}


MyImageView::~MyImageView()
{
	
}


void MyImageView::setVisibility(bool v, int idx)
{
	if (idx>=0 && idx<circle_num)
	{
		_circles[idx]->setvisibility(v);
	}
}


void MyImageView::setVisibility(bool v)
{
	for (int i = 0; i < circle_num;++i)
	{
		_circles[i]->setvisibility(v);
	}
}


void MyImageView::setItemMovable(bool v, int idx)
{
	if (idx >= 0 && idx < circle_num)
	{
		_circles[idx]->setMovable(v);
	}
}


void MyImageView::setItemMovable(bool v)
{
	for (int i = 0; i < circle_num; ++i)
	{
		_circles[i]->setMovable(v);
	}
}



void MyImageView::resetImg(bool f)
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


void MyImageView::resetCircle(int idx)
{
	if (idx >= 0 && idx < circle_num)
	{
		//设置圆的位置
		double r = fmax(_pixmap_bk.width(), _pixmap_bk.height())*0.358;
		double x = _pixmap_bk.width()*0.5;
		double y = _pixmap_bk.height()*0.5;
		double s = (double)_pixmap.width() / _pixmap_bk.width();

// 		int x_rand = rand() % 100; int y_rand = rand() % 100;

// 		_circles[idx]->reset(x + x_rand, y + y_rand, r, s);

		_circles[idx]->reset(x, y, r, s);


		emit circleResized(_circles[idx]->getRadius(), idx);
		emit circleMoved(_circles[idx]->getCenterPos(), idx);
	}
}


void MyImageView::reset(bool f)
{
	resetImg(f);

	for (int i = 0; i < circle_num; ++i)
	{
		resetCircle(i);
	}
}


void MyImageView::setPixmap(QImage src)
{
	_pixmap_bk = QPixmap::fromImage(src);
	_pixmap = QPixmap::fromImage(src);

	reset(false);
}


void MyImageView::loadPixmap(QString src_path_name)
{
	_pixmap_bk.load(src_path_name);
	_pixmap.load(src_path_name);

	reset(false);
}


void MyImageView::addItem(QGraphicsItem *item)
{
	_scene->addItem(item);
}


void MyImageView::wheelEvent(QWheelEvent *event)
{		
	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{	
		circle_acitve_idx = -1;

		QPointF p = mapToScene(event->pos());
		QTransform transf;
		QGraphicsItem *gp = _scene->itemAt(p, transf);
		for (int i = 0; i < circle_num; ++i)
		{
			if (gp == _circles[i])
			{
				_circles[i]->wheelEvent(event);
				emit circleResized(_circles[i]->getRadius(), i);
				break;
			}
		}
	}	
	else
	{
		int distance = event->delta();
		int numDegrees = distance / 8;
		int numSteps = numDegrees / 15;

		double scale = powf(1.2, numSteps);
		
		_scene->setSceneRect(0, 0, _scene->width() * scale, _scene->height() * scale);//_scene 为 QGraphicsScene
		_pixmap = _pixmap_bk.scaled(QSize(_scene->width(), _scene->height()));
		_graph->setPixmap(_pixmap);

		double s = (double)_pixmap.width() / _pixmap_bk.width();

		for (int i = 0; i < circle_num; ++i)
		{
			_circles[i]->zoom(s);
		}		
	}
}


void MyImageView::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		if (QApplication::keyboardModifiers() == Qt::ControlModifier)
		{	
			circle_acitve_idx = -1;

			QPointF p = mapToScene(event->pos());
			QTransform transf;
			QGraphicsItem *gp = _scene->itemAt(p, transf);
			for (int i = 0; i < circle_num; ++i)
			{
				if (gp == _circles[i])
				{
					circle_acitve_idx = i;
					_circles[i]->mousePressEvent(event);
					break;
				}
			}					
		}
		else
		{
			setCursor(Qt::ClosedHandCursor);
			oldx = event->x();
			oldy = event->y();
		}
	}
	else
	{
		reset(false);
		double s = (double)_pixmap.width() / _pixmap_bk.width();
		for (int i = 0; i < circle_num; ++i)
		{
			_circles[i]->zoom(s);
		}
	}
	
}


void MyImageView::mouseMoveEvent(QMouseEvent *event)
{		
	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{	
// 		if (circle_acitve_idx >= 0)
		{
			circle_acitve_idx = 0; //仅适用于单个circle
			_circles[circle_acitve_idx]->mouseMoveEvent(event);
			emit circleMoved(_circles[circle_acitve_idx]->getCenterPos(), circle_acitve_idx);
		}
	}
	else
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
}


void MyImageView::mouseReleaseEvent(QMouseEvent *event)
{
	setCursor(Qt::OpenHandCursor);	
	for (int i = 0; i < circle_num; ++i)
	{
		_circles[i]->mouseReleaseEvent(event);
	}
}


void MyImageView::keyPressEvent(QKeyEvent *event)
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
		for (int i = 0; i < circle_num; ++i)
		{
			_circles[i]->zoom(s);
		}
		break;
	}
	case Qt::Key_Q:
	{
		resetImg(true);
		double s = (double)_pixmap.width() / _pixmap_bk.width();
		for (int i = 0; i < circle_num; ++i)
		{
			_circles[i]->zoom(s);
		}
		break;
	}

	}

	//回调激活的circle的键盘函数
// 	if (circle_acitve_idx >= 0)
	if (circle_num==1)//如果多于一个circle，键盘操作就需要制定那个circle，但是如果只有一个，就不需要指定，方便目前使用
	{
		circle_acitve_idx = 0; //仅适用于单个circle
		_circles[circle_acitve_idx]->keyPressEvent(event);
		emit circleMoved(_circles[circle_acitve_idx]->getCenterPos(), circle_acitve_idx);
	}
}


void MyImageView::setItemPos(QPointF t, int idx)
{
	if (idx >= 0 && idx < circle_num)
	{
		_circles[idx]->move(t);
		emit circleMoved(_circles[idx]->getCenterPos(), idx);
	}
}


void MyImageView::setItemPosX(double x, int idx)
{
	if (idx >= 0 && idx < circle_num)
	{
		_circles[idx]->moveX(x);
		emit circleMoved(_circles[idx]->getCenterPos(), idx);
	}
}


void MyImageView::setItemPosY(double y, int idx)
{
	if (idx >= 0 && idx < circle_num)
	{
		_circles[idx]->moveY(y);
		emit circleMoved(_circles[idx]->getCenterPos(), idx);
	}
}


void MyImageView::setItemSize(double r, int idx)
{
	if (idx >= 0 && idx < circle_num)
	{
		_circles[idx]->resize(r);
		emit circleResized(_circles[idx]->getRadius(), idx);
	}
}