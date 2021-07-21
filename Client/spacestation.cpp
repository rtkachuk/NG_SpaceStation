#include "spacestation.h"
#include "ui_spacestation.h"

SpaceStation::SpaceStation(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::SpaceStation)
{
	ui->setupUi(this);

	m_mapWorker = new MapWorker();
	m_mapWorker->setCellSizePixels(30);

	m_mapWorker->mapInit();

	m_scene = new QGraphicsScene(0, 0, m_mapWorker->getMapSizeX(), m_mapWorker->getMapSizeY());
	ui->graphicsView->setScene(m_scene);
	ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
	m_mapWorker->setScene(m_scene);
	m_mapWorker->drawMap();

	m_actionWindow = new ActionWindow();
	m_actionWindow->show();

	initMenus();

	m_connectionManager = new ConnectionManager();
	m_networkingThread = new QThread();
	m_connectionManager->moveToThread(m_networkingThread);
	m_networkingThread->start();

	connect (m_actionWindow, &ActionWindow::askFindPlayer, this, &SpaceStation::actFindPlayer);
	connect (m_connectionManager, &ConnectionManager::connected, this, &SpaceStation::connectedToServer);
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

void SpaceStation::connectToServer()
{
	m_connectDialog = new ConnectDialog();
	m_connectDialog->exec();

	m_ip = m_connectDialog->getIp();
	m_port = m_connectDialog->getPort();
	delete m_connectDialog;

	log ("Get ip: " + m_ip);
	log ("Get port: " + m_port);

	m_connectionManager->connectToServer(m_ip, m_port);
}

void SpaceStation::connectedToServer()
{
	ui->statusbar->showMessage("Connected to " + m_ip);
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

	if (m_followPlayer->isChecked()) actFindPlayer();
}

void SpaceStation::initMenus()
{
	m_mFile = new QMenu("File");
	m_mSettings = new QMenu("Settings");

	m_actConnect = new QAction("Connect");
	m_quit = new QAction("Quit");
	m_followPlayer = new QAction("Follow player");
	m_followPlayer->setCheckable(true);

	m_mFile->addAction(m_actConnect);
	m_mFile->addAction(m_quit);
	m_mSettings->addAction(m_followPlayer);

	ui->menubar->addMenu(m_mFile);
	ui->menubar->addMenu(m_mSettings);
	ui->menubar->show();

	connect (m_actConnect, &QAction::triggered, this, &SpaceStation::connectToServer);
	connect (m_quit, &QAction::triggered, this, &SpaceStation::close);
	connect (m_quit, &QAction::triggered, m_actionWindow, &ActionWindow::close);
}

void SpaceStation::log(QString message)
{
	qDebug() << "[Core]: " << message;
}
