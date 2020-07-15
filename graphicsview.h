#pragma once

#include <QWidget>
#include <QApplication>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QTransform>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>

#include <QWheelEvent>

class GraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	explicit GraphicsView(QWidget *parent = 0);

signals:
	void mouseReleased();
	void statusUpdate(QString text, QColor textColor);
	void zoomUpdate(QString text);

protected:
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

public slots:
	void setGrid();
	void zoomActual();
	void zoomSceneRect();
	void zoomGraphicsItems();
	void zoomSelectedItems();
	void zoomDelta(int delta);
	void zoomOut();
	void zoomIn();

private:
	void statusUpdate(QString _consoleStatus);
};
