#ifndef WORKPLATE_H
#define WORKPLATE_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

#include <QGroupBox>

#include "graphicsview.h"
#include <QGraphicsScene>

#include <QMessageBox>

class workplate : public QWidget
{
    Q_OBJECT

public:
    workplate(QWidget *parent = 0);
    ~workplate();

private slots:
	void on_ChoseCamera(int);
	void on_btnCapture();
	void on_btnImport();
	void on_btnSettings();
	void on_btnWarp();
	void on_btnProcess();
	void on_btnTools();
	void on_btnSave();
	void on_btnExit();

private:
	QComboBox* comCamera;
	QPushButton* btnCapture;
	QPushButton* btnImport;
	QPushButton* btnSettings;
	QPushButton* btnWarp;
	QPushButton* btnProcess;
	QPushButton* btnSave;
	QPushButton* btnExit;

	GraphicsView* graphicsView;
	QGraphicsScene graphicsScene;

	QPushButton* btnTools;
	QGroupBox* groupTool;
	QPushButton* btnFlipH;
	QPushButton* btnFlipV;
	QPushButton* btnRotR;
	QPushButton* btnRotL;
	QPushButton* btnZoomAdjust;
	QPushButton* btnZoomIn;
	QPushButton* btnZoomOut;

	int m_nWidth;
	int m_nHeight;

	QMessageBox msgBox;
};

#endif // WORKPLATE_H
