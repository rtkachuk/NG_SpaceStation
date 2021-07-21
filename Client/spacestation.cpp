#include "spacestation.h"
#include "ui_spacestation.h"

SpaceStation::SpaceStation(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::SpaceStation)
{
	ui->setupUi(this);

	int wSize = 1000;
	int hSize = 1000;

	m_mapWorker = new MapWorker();
	m_mapWorker->setCellsRows(hSize);
	m_mapWorker->setCellsColumns(wSize);
	m_mapWorker->setCellSizePixels(30);

	m_mapWorker->mapInit();

	m_scene = new QGraphicsScene(0, 0, wSize, hSize);
	ui->graphicsView->setScene(m_scene);
	ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
	m_mapWorker->setScene(m_scene);
	m_mapWorker->drawMap();

	m_actionWindow = new ActionWindow();
	m_actionWindow->show();

	connect (m_actionWindow, &ActionWindow::askFindPlayer, this, &SpaceStation::actFindPlayer);
}

SpaceStation::~SpaceStation()
{
	delete ui;
}

void SpaceStation::actFindPlayer()
{
	int pixelSize = m_mapWorker->getCellSizePixels();
	int posX = m_mapWorker->getPlayerPosX() * pixelSize;
	int posY = m_mapWorker->getPlayerPosY() * pixelSize;

	log ("Moving view to: " + QString::number(posX) + ":::" + QString::number(posY));
	ui->graphicsView->centerOn(posX, posY);
}

void SpaceStation::keyPressEvent(QKeyEvent *event)
{
	QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
	switch (keyEvent->key()) {
		case Qt::Key_W: m_mapWorker->updatePlayerPosition(up); break;
		case Qt::Key_S: m_mapWorker->updatePlayerPosition(down); break;
		case Qt::Key_A: m_mapWorker->updatePlayerPosition(left); break;
		case Qt::Key_D: m_mapWorker->updatePlayerPosition(right); break;
	}
}

void SpaceStation::log(QString message)
{
	qDebug() << "[Core]: " << message;
}
