#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{

}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit mouseReleased();
	}
	QGraphicsView::mouseReleaseEvent(event);
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

void GraphicsView::setGrid()
{
	
}

void GraphicsView::zoomActual()
{
	// physicalDpi is the number of pixels in an inch
	int xDpi = physicalDpiX();
	int yDpi = physicalDpiY();
	// Transforms
	QTransform hpglToPx, viewFlip;
	hpglToPx.scale(xDpi / 1016.0, yDpi / 1016.0);
	viewFlip.scale(1, -1);

	setTransform(hpglToPx * viewFlip);
	setGrid();

	emit statusUpdate("Scene scale set to 1:1", Qt::darkGreen);
	emit zoomUpdate("Actual size");
}

void GraphicsView::zoomSceneRect()
{
	fitInView(
		scene()->sceneRect(),
		Qt::KeepAspectRatio);
	setGrid();
	emit statusUpdate("Scene scale set to view all", Qt::darkGreen);
	emit zoomUpdate("Vinyl width");
}

void GraphicsView::zoomGraphicsItems()
{
	QRectF newrect;

	newrect.setX(0);
	newrect.setY(0);
	newrect.setWidth(0);
	newrect.setHeight(0);

	QList<QGraphicsItem*> itemList = items();
	// type() = 10 -> QGraphicsItemGroup

	for (int i = 0; i < itemList.length(); ++i)
	{
		QGraphicsItem * item = itemList.at(i);
		if (item->type() == 10) // item is a qgraphicsitemgroup
		{
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
		}
	}

	fitInView(newrect, Qt::KeepAspectRatio);
	setGrid();

	emit statusUpdate("Scene scale set to contain items", Qt::darkGreen);
	emit zoomUpdate("Show all items");
}

void GraphicsView::zoomSelectedItems()
{
	QRectF newrect;

	newrect.setX(0);
	newrect.setY(0);
	newrect.setWidth(0);
	newrect.setHeight(0);

	QList<QGraphicsItem*> itemList = items();
	// type() = 10 -> QGraphicsItemGroup

	for (int i = 0; i < itemList.length(); ++i)
	{
		QGraphicsItem * item = itemList.at(i);
		if (item->type() == 10 && item->isSelected()) // item is a qgraphicsitemgroup
		{
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
		}
	}

	fitInView(newrect, Qt::KeepAspectRatio);
	setGrid();

	emit statusUpdate("Scene scale set to contain items", Qt::darkGreen);
	emit zoomUpdate("Show all items");
}

void GraphicsView::zoomDelta(int delta)
{
	QTransform oldtransform = transform();
	QTransform scaleTransform;
	scaleTransform.scale((1.0 + (5.0 / delta)), (1.0 + (5.0 / delta)));
	setTransform(oldtransform * scaleTransform);
	setGrid();
	emit statusUpdate("Scene scale set to scroll wheel zoom.", Qt::darkGreen);
	emit zoomUpdate("Custom");
}

void GraphicsView::zoomOut()
{
	zoomDelta(-30);
}

void GraphicsView::zoomIn()
{
	zoomDelta(30);
}

void GraphicsView::statusUpdate(QString _consoleStatus)
{
	emit statusUpdate(_consoleStatus, Qt::black);
}
