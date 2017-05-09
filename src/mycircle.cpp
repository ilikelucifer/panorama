#include "mycircle.h"
#include <QDebug>

myCircle::myCircle(QObject *parent) :
    QObject(parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);
    setFlag(ItemSendsGeometryChanges);
}

QVariant myCircle::itemChange(GraphicsItemChange change, const QVariant  &value )
{

  if (change == ItemPositionChange)
  {   
      emit itemMoved(value.toPointF());
  }
  return QGraphicsItem::itemChange(change, value);
}
// 鼠标点击事件
void myCircle::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
       emit leftMouseClicked();
}
// 鼠标点击事件
void myCircle:: keyPressEvent(QKeyEvent *ev)
{
    int key=ev->key();
    if (Qt::Key_W == key || Qt::Key_Up == key) { emit keyMoved(0); };
	if (Qt::Key_S == key || Qt::Key_Down == key) { emit keyMoved(1); };
	if (Qt::Key_A == key || Qt::Key_Left == key) { emit keyMoved(2); };
	if (Qt::Key_D == key || Qt::Key_Right == key) { emit keyMoved(3); };
}

// 鼠标滚轮事件
void myCircle::wheelEvent(QGraphicsSceneWheelEvent *event)
{
	int numAngle = event->delta() / 8;
	int numSteps = numAngle / 15;

	emit wheelScrolled(numSteps);
}


void myCircle::passiveMove(QPointF p)
{
	setPos(p.x(), p.y());
}