#pragma once

#include <QWidget>
#include <QApplication>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QTransform>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>

#include <QMouseEvent>
#include <QWheelEvent>

class GraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	explicit GraphicsView(QWidget *parent = 0);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

public slots:
	void viewFlipH();
	void viewFlipV();
	void viewRotL();
	void viewRotR();

	void zoomAdjust();
	void zoomDelta(int delta);
	void zoomOut();
	void zoomIn();

private:
	void statusUpdate(QString _consoleStatus);
	void rotateSelectedItems(qreal rotation);
	void scaleSelectedItems(qreal x, qreal y);

private:
	QPoint m_pOrigin;
};
