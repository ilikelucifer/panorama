#ifndef MYCIRCLE_H
#define MYCIRCLE_H

#include <QObject>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>

class myCircle: public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT

public:

	explicit myCircle(QObject *parent = 0);

	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	virtual void keyPressEvent(QKeyEvent *ev);
	void wheelEvent(QGraphicsSceneWheelEvent *event);


private slots:
	void passiveMove(QPointF p);


signals:

	void itemMoved(QPointF p);
	void leftMouseClicked();
	void keyMoved(int direction);
	void wheelScrolled(int num);
};

#endif // MYCIRCLE_H
