#include "workplate.h"

#include "global.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QApplication>
#include <QDesktopWidget>
#include <QRect>

#define BTN_WIDTH	25
#define BTN_HEIGHT	25

#define ICON_WIDTH	25
#define ICON_HEIGHT	25

workplate::workplate(QWidget *parent)
    : QWidget(parent)
{
//	QDesktopWidget* pDesktopWidget = QApplication::desktop();
//	QRect deskRect = QApplication::desktop()->availableGeometry();
	QRect screenRect = QApplication::desktop()->screenGeometry();
	m_nWidth = screenRect.width();
	m_nHeight = screenRect.height();

	comCamera = new QComboBox(this);

	btnCapture = new QPushButton(this);
	btnCapture->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/capture.png)}");
	btnCapture->setFixedSize(BTN_WIDTH, BTN_HEIGHT);
	btnImport = new QPushButton(this);
	btnImport->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/import.png)}");
	btnImport->setFixedSize(BTN_WIDTH, BTN_HEIGHT);
	btnSettings = new QPushButton(this);
	btnSettings->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/setting.png)}");
	btnSettings->setFixedSize(BTN_WIDTH, BTN_HEIGHT);
	btnWarp = new QPushButton(this);
	btnWarp->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/warp.png)}");
	btnWarp->setFixedSize(BTN_WIDTH, BTN_HEIGHT);
	btnProcess = new QPushButton(this);
	btnProcess->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/process.png)}");
	btnProcess->setFixedSize(BTN_WIDTH, BTN_HEIGHT);
	btnSave = new QPushButton(this);
	btnSave->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/save.png)}");
	btnSave->setFixedSize(BTN_WIDTH, BTN_HEIGHT);
	btnExit = new QPushButton(this);
	btnExit->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/exit.png)}");
	btnExit->setFixedSize(BTN_WIDTH, BTN_HEIGHT);
	btnTools = new QPushButton(this);
	btnTools->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/icons/tools.png)}");
	btnTools->setFixedSize(BTN_WIDTH, BTN_HEIGHT);

	groupTool = new QGroupBox("Tool", this);
	btnFlipH = new QPushButton(groupTool);
	btnFlipH->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/icons/flip_horizontal.png)}");
	btnFlipH->setFixedSize(ICON_WIDTH, ICON_HEIGHT);
	btnFlipV = new QPushButton(groupTool);
	btnFlipV->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/icons/flip_vertical.png)}");
	btnFlipV->setFixedSize(ICON_WIDTH, ICON_HEIGHT);
	btnRotL = new QPushButton(groupTool);
	btnRotL->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/icons/rotate_left.png)}");
	btnRotL->setFixedSize(ICON_WIDTH, ICON_HEIGHT);
	btnRotR = new QPushButton(groupTool);
	btnRotR->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/icons/rotate_right.png)}");
	btnRotR->setFixedSize(ICON_WIDTH, ICON_HEIGHT);
	btnZoomActual = new QPushButton(groupTool);
	btnZoomActual->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/icons/zoom_actual.png)}");
	btnZoomActual->setFixedSize(ICON_WIDTH, ICON_HEIGHT);
	btnZoomFitAll = new QPushButton(groupTool);
	btnZoomFitAll->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/icons/zoom_fit_all.png)}");
	btnZoomFitAll->setFixedSize(ICON_WIDTH, ICON_HEIGHT);
	btnZoomFiltSelection = new QPushButton(groupTool);
	btnZoomFiltSelection->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/icons/zoom_fit_selection.png)}");
	btnZoomFiltSelection->setFixedSize(ICON_WIDTH, ICON_HEIGHT);
	btnZoomIn = new QPushButton(groupTool);
	btnZoomIn->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/icons/zoom_in.png)}");
	btnZoomIn->setFixedSize(ICON_WIDTH, ICON_HEIGHT);
	btnZoomOut = new QPushButton(groupTool);
	btnZoomOut->setStyleSheet(MainStyle_Button + "QPushButton{border-image:url(images/icons/zoom_out.png)}");
	btnZoomOut->setFixedSize(ICON_WIDTH, ICON_HEIGHT);

	QHBoxLayout* layoutTool = new QHBoxLayout;
	layoutTool->addStretch();
	layoutTool->addWidget(btnRotL);
	layoutTool->addStretch();
	layoutTool->addWidget(btnRotR);
	layoutTool->addStretch();
	layoutTool->addWidget(btnFlipH);
	layoutTool->addStretch();
	layoutTool->addWidget(btnFlipV);
	layoutTool->addStretch();
	layoutTool->addWidget(btnZoomActual);
	layoutTool->addStretch();
	layoutTool->addWidget(btnZoomFitAll);
	layoutTool->addStretch();
	layoutTool->addWidget(btnZoomFiltSelection);
	layoutTool->addStretch();
	layoutTool->addWidget(btnZoomIn);
	layoutTool->addStretch();
	layoutTool->addWidget(btnZoomOut);
	layoutTool->addStretch();
	groupTool->setLayout(layoutTool);
	groupTool->setVisible(false);

	QHBoxLayout* layoutBtn = new QHBoxLayout;
	layoutBtn->addWidget(comCamera);
	layoutBtn->addStretch();
	layoutBtn->addWidget(btnCapture);
	layoutBtn->addStretch();
	layoutBtn->addWidget(btnImport);
	layoutBtn->addStretch();
	layoutBtn->addWidget(btnSettings);
	layoutBtn->addStretch();
	layoutBtn->addWidget(btnWarp);
	layoutBtn->addStretch();
	layoutBtn->addWidget(btnProcess);
	layoutBtn->addStretch();
	layoutBtn->addWidget(btnTools);
	layoutBtn->addStretch();
	layoutBtn->addWidget(btnSave);
	layoutBtn->addStretch();
	layoutBtn->addWidget(btnExit);
	
	graphicsView = new GraphicsView(this);
	graphicsView->setStyleSheet("padding:2px;border:2px;");
	graphicsView->setScene(&graphicsScene);
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addLayout(layoutBtn);
	layout->addWidget(groupTool);
	layout->addWidget(graphicsView);
	setLayout(layout);

	connect(comCamera, SIGNAL(currentIndexChanged(int)), this, SLOT(on_ChoseCamera(int)));
	connect(btnCapture, SIGNAL(clicked()), this, SLOT(on_btnCapture()));
	connect(btnImport, SIGNAL(clicked()), this, SLOT(on_btnImport()));
	connect(btnSettings, SIGNAL(clicked()), this, SLOT(on_btnSettings()));
	connect(btnWarp, SIGNAL(clicked()), this, SLOT(on_btnWarp()));
	connect(btnProcess, SIGNAL(clicked()), this, SLOT(on_btnProcess()));
	connect(btnTools, SIGNAL(clicked()), this, SLOT(on_btnTools()));
	connect(btnSave, SIGNAL(clicked()), this, SLOT(on_btnSave()));
	connect(btnExit, SIGNAL(clicked()), this, SLOT(on_btnExit()));

	//connect(&graphicsScene, SIGNAL(changed(QList<QRectF>)), this, SLOT(sceneConstrainItems()));
	//connect(graphicsView, SIGNAL(zoomUpdate(QString)), this, SLOT(handle_zoomChanged(QString)));
	//connect(graphicsView, SIGNAL(statusUpdate(QString, QColor)), this, SLOT(handle_newConsoleText(QString, QColor)));
	//connect(graphicsView, SIGNAL(zoomUpdate(QString)), this, SLOT(setGrid()));
	//connect(&graphicsScene, SIGNAL(selectionChanged()), this, SLOT(handle_plotSceneSelectionChanged()));

	connect(btnZoomActual, SIGNAL(clicked()), graphicsView, SLOT(zoomActual()));
	connect(btnZoomFitAll, SIGNAL(clicked()), graphicsView, SLOT(zoomGraphicsItems()));
	connect(btnZoomFiltSelection, SIGNAL(clicked()), graphicsView, SLOT(zoomSelectedItems()));
	connect(btnZoomIn, SIGNAL(clicked()), graphicsView, SLOT(zoomIn()));
	connect(btnZoomOut, SIGNAL(clicked()), graphicsView, SLOT(zoomOut()));

	//	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
	setGeometry(QRect(m_nWidth / 10, m_nHeight / 10, m_nWidth * 2 / 3, m_nHeight * 2 / 3));
	//	showMaximized();
}

workplate::~workplate()
{

}


void workplate::on_ChoseCamera(int)
{

}

void workplate::on_btnCapture()
{

}

void workplate::on_btnImport()
{
	graphicsItem* item = new graphicsItem;
	graphicsScene.addItem(item);
}

void workplate::on_btnSettings()
{

}

void workplate::on_btnWarp()
{

}

void workplate::on_btnProcess()
{

}

void workplate::on_btnSave()
{

}

void workplate::on_btnExit()
{
	exit(0);
}

void workplate::on_btnTools()
{
	if (groupTool->isVisible())
	{
		groupTool->setVisible(false);
	}
	else
	{
		groupTool->setVisible(true);
	}
}

void workplate::on_FlipH()
{

}

void workplate::on_FlipV()
{

}

void workplate::on_RotR()
{

}

void workplate::on_RotL()
{

}

void workplate::on_ZoomActual()
{

}

void workplate::on_ZoomFitAll()
{

}

void workplate::on_ZoomFiltSelection()
{

}

void workplate::on_ZoomIn()
{

}

void workplate::on_ZoomOut()
{

}
