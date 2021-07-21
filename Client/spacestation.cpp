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
	m_mapWorker->setScene(m_scene);
	m_mapWorker->drawMap();

	m_actionWindow = new ActionWindow();
	m_actionWindow->show();
}

SpaceStation::~SpaceStation()
{
	delete ui;
}

void SpaceStation::keyPressEvent(QKeyEvent *event)
{
	QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
	log("Catch: " + QString::number((int)keyEvent->key()));
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
