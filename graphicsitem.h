#pragma once


#include <QGraphicsItem>

#include <QPainter>
//#include <QRectF>

class graphicsItem : public QGraphicsItem
{
public:
	graphicsItem();

	QRectF boundingRect() const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
