#include "graphicsview.h"

#include <QDebug>

GraphicsView::GraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{

}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{

}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{

	QPoint point = event->pos();
	QRectF rect = this->sceneRect();

	this->setSceneRect(-point.x(), -point.y(), rect.width(), rect.height());
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{

}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		int delta = event->delta();
		zoomDelta(delta);
	}
	else
	{
		event->ignore();
	}
	QGraphicsView::wheelEvent(event);
}

void GraphicsView::viewFlipH()
{
	scaleSelectedItems(-1, 1);
}

void GraphicsView::viewFlipV()
{
	scaleSelectedItems(1, -1);
}

void GraphicsView::viewRotL()
{
	rotateSelectedItems(-90);
}

void GraphicsView::viewRotR()
{
	rotateSelectedItems(90);
}

void GraphicsView::zoomAdjust()
{
	QRectF newrect;

	newrect.setX(0);
	newrect.setY(0);
	newrect.setWidth(0);
	newrect.setHeight(0);

	QList<QGraphicsItem*> itemList = items();
	if (itemList.size() <= 0)
	{
		return;
	}

	QGraphicsItem * item = itemList.at(0);
	QRectF compRect = item->boundingRect();
	QPointF compPoint = item->pos();

	if ((compPoint.x() + compRect.width()) > newrect.width())
	{
		newrect.setWidth(compPoint.x() + compRect.width());
	}
	if ((compPoint.y() + compRect.height()) > newrect.height())
	{
		newrect.setHeight(compPoint.y() + compRect.height());
	}

	fitInView(newrect, Qt::KeepAspectRatio);
}

void GraphicsView::zoomDelta(int delta)
{
	QTransform oldtransform = transform();
	QTransform scaleTransform;
	scaleTransform.scale((1.0 + (5.0 / delta)), (1.0 + (5.0 / delta)));
	setTransform(oldtransform * scaleTransform);
}

void GraphicsView::zoomOut()
{
	zoomDelta(-30);
}

void GraphicsView::zoomIn()
{
	zoomDelta(30);
}

void GraphicsView::rotateSelectedItems(qreal rotation)
{
	QList<QGraphicsItem*> itemList = items();
	if (itemList.size() <= 0)
	{
		return;
	}
	qreal translateWidth, translateheight, xOffset, yOffset;

	QGraphicsItem * item = itemList.at(0);

	xOffset = item->boundingRect().x();
	yOffset = item->boundingRect().y();
	translateWidth = item->boundingRect().width();
	translateheight = item->boundingRect().height();
	item->setTransformOriginPoint((translateWidth / 2.0) + xOffset, (translateheight / 2.0) + yOffset);
	item->setRotation(item->rotation() + rotation);
}

void GraphicsView::scaleSelectedItems(qreal x, qreal y)
{
	QList<QGraphicsItem*> itemList = items();
	if (itemList.size() <= 0)
	{
		return;
	}

	QTransform transform;
	qreal translateWidth, translateheight;

	QGraphicsItem * item = itemList.at(0);
	translateWidth = item->boundingRect().width();
	translateheight = item->boundingRect().height();
	transform.translate(translateWidth / 2.0, translateheight / 2.0);
	transform.scale(x, y);
	transform.translate(-translateWidth / 2.0, -translateheight / 2.0);
	item->setTransform(item->transform() * transform);
}