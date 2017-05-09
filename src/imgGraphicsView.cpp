#include "imgGraphicsView.h"

ImgGraphicsView::ImgGraphicsView(QWidget* parent):
QGraphicsView(parent)
{
	oldx = 0; oldy = 0;
	setMouseTracking(false);
	setCursor(Qt::OpenHandCursor);

	setAlignment(Qt::AlignCenter);

	_scene = new QGraphicsScene();
	_scene->setBackgroundBrush(Qt::gray);

	this->setScene(_scene);

	_graph = new QGraphicsPixmapItem();

	_scene->addItem(_graph);

	oldx = 0; oldy = 0;

	accPos = QPointF(0, 0);
	accTransPos = QPointF(0, 0);
	accAng = 0;
}


QPointF ImgGraphicsView::getAccPos()
{
	return accPos;
}


double ImgGraphicsView::getAccAngle()
{
	return accAng;
}


QPointF ImgGraphicsView::getAccTransPos()
{
	return accTransPos;
}

void ImgGraphicsView::resetPos()
{
	accPos = QPointF(0, 0);
	emit mouseMoved(accPos);
}


void ImgGraphicsView::resetAng()
{
	accAng = 0;
	emit mouseRotate(accAng);
}


void ImgGraphicsView::resetTransPos()
{
	accTransPos = QPointF(0, 0);
	emit mouseTransMoved(accTransPos);
}

void ImgGraphicsView::setPixmap(QImage src)
{
	_pixmap_bk = QPixmap::fromImage(src);
	_pixmap = QPixmap::fromImage(src);

	resetImg(false);
}


void ImgGraphicsView::loadPixmap(QString src_path_name)
{
	_pixmap_bk.load(src_path_name);
	_pixmap.load(src_path_name);

	resetImg(false);
}


void ImgGraphicsView::resetImg(bool f)
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







// 	float width = this->width();
// 	float height = this->height();
// 
// 	float scale_w = width / _pixmap_bk.width();
// 	float scale_h = height / _pixmap_bk.height();
// 
// 	if (scale_w < scale_h)
// 	{
// 		_scene->setSceneRect(0, 0, this->width() - 4, int(_pixmap_bk.height()*(this->width() - 4) / _pixmap_bk.width()));
// 		_pixmap = _pixmap_bk.scaled(QSize(_scene->width(), _scene->height()));
// 
// 	}
// 	else
// 	{
// 		_scene->setSceneRect(0, 0, int(_pixmap_bk.width()*(this->height() - 4) / _pixmap_bk.height()), this->height() - 4);
// 		_pixmap = _pixmap_bk.scaled(QSize(_scene->width(), _scene->height()));
// 
// 	}
// 
// 	_graph->setPixmap(_pixmap);


}


void ImgGraphicsView::wheelEvent(QWheelEvent *event)
{
	int distance = event->delta();
	int numDegrees = distance / 120;

	if (QApplication::keyboardModifiers() == Qt::ShiftModifier)
	{
		accAng += numDegrees;
	}
	else
	{
		accAng += numDegrees*0.05;
	}

	emit mouseRotate(accAng);
	
}


void ImgGraphicsView::mousePressEvent(QMouseEvent *event)
{
	setCursor(Qt::ClosedHandCursor);
	if (event->buttons() == Qt::LeftButton)
	{
		oldx = event->x();
		oldy = event->y();
	}
	else
	{
		accTransPos = QPointF(0, 0);
		emit mouseTransMoved(accTransPos);
	}
	
}


void ImgGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
	setCursor(Qt::ClosedHandCursor);

	int x = event->x();
	int y = event->y();

	if (event->buttons() == Qt::LeftButton) //发出平移量信号
	{
		int delta_x = oldx - x;
		int delta_y = oldy - y;

		double scale = (double)_pixmap.width() / _pixmap_bk.width();

		if (QApplication::keyboardModifiers() == Qt::ControlModifier)
		{
			accTransPos -= QPointF(delta_x / scale, delta_y / scale);//和移动校正中心是反向的
			emit mouseTransMoved(accTransPos);
		}
		else
		{
			accPos += QPointF(delta_x / scale, delta_y / scale);
			emit mouseMoved(accPos);
		}
	}

	oldx = x;
	oldy = y;
}


void ImgGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
	setCursor(Qt::OpenHandCursor);
}


void ImgGraphicsView::keyPressEvent(QKeyEvent *event)
{
	double step = 1;

	switch (event->key())
	{
	case Qt::Key_W:
	case Qt::Key_Up:
	{
		accPos.setY(accPos.y() + step);
		emit mouseMoved(accPos);
		break;
	}
	case Qt::Key_S:
	case Qt::Key_Down:
	{
		accPos.setY(accPos.y() - step);
		emit mouseMoved(accPos);
		break;
	}
	case Qt::Key_A:
	case Qt::Key_Left:
	{
		accPos.setX(accPos.x() + step);
		emit mouseMoved(accPos);
		break;
	}
	case Qt::Key_D:
	case Qt::Key_Right:
	{
		accPos.setX(accPos.x() - step);
		emit mouseMoved(accPos);
		break;
	}	
	case Qt::Key_R:
	{
		resetImg(false);
		break;
	}
	case Qt::Key_Q:
	{
		resetImg(true);
		break;
	}

	}
}


void ImgGraphicsView::on_AccAngle_changed(double a)
{
	accAng = a;
	emit mouseRotate(accAng);
}


void ImgGraphicsView::on_AccPos_changed(QPointF p)
{
	accPos = p;
	emit mouseMoved(accPos);
}

void ImgGraphicsView::on_AccPosX_changed(double x)
{
	accPos.setX(x);
	emit mouseMoved(accPos);
}

void ImgGraphicsView::on_AccPosY_changed(double y)
{
	accPos.setY(y);
	emit mouseMoved(accPos);
}

void ImgGraphicsView::on_AccTransPosX_changed(double x)
{
	accTransPos.setX(x);
	emit mouseTransMoved(accTransPos);
}

void ImgGraphicsView::on_AccTransPosY_changed(double y)
{
	accTransPos.setY(y);
	emit mouseTransMoved(accTransPos);
}