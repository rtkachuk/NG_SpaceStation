#include "spacestation.h"
#include "ui_spacestation.h"

SpaceStation::SpaceStation(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::SpaceStation)
{
	ui->setupUi(this);

	m_actionWindow = new ActionWindow();
	m_actionWindow->show();

	ui->t_chat->setReadOnly(true);

	initGraphics();
	initMenus();
	initConnectionManager();

	connect (m_actionWindow, &ActionWindow::askFindPlayer, this, &SpaceStation::actFindPlayer);

	connect (m_connectionManager, &ConnectionManager::connected, this, &SpaceStation::connectedToServer);
	connect (m_connectionManager, &ConnectionManager::gotMap, this, &SpaceStation::mapReceived);
	connect (m_connectionManager, &ConnectionManager::playerPosition, this, &SpaceStation::setPlayerPosition);
	connect (m_connectionManager, &ConnectionManager::message, this, &SpaceStation::chatMessage);
	connect (m_connectionManager, &ConnectionManager::mapChanged, this, &SpaceStation::mapChanged);
	connect (m_connectionManager, &ConnectionManager::gotId, this, &SpaceStation::gotId);
	connect (m_connectionManager, &ConnectionManager::playerDisconnected, this, &SpaceStation::playerDisconnected);
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

	ui->graphicsView->centerOn(posX, posY);
}

void SpaceStation::actShowActionsMenu()
{
	m_actionWindow->show();
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

void SpaceStation::mapReceived()
{
	ui->statusbar->showMessage("Loading map...");
	m_mapWorker->mapInit(m_connectionManager->getMap());
	m_mapWorker->drawMap();
	m_connectionManager->askForId();
}

void SpaceStation::setPlayerPosition(QByteArray id, int x, int y)
{
	if (m_followPlayer->isChecked() && id == m_mapWorker->getPlayerId()) actFindPlayer();
	m_mapWorker->updatePlayerPosition(id, x, y);
	ui->graphicsView->viewport()->update();
}

void SpaceStation::chatMessage(QString message)
{
	ui->t_chat->setText(ui->t_chat->toPlainText() + "\n" + message);
}

void SpaceStation::mapChanged(int x, int y, char object)
{
	m_mapWorker->updateMap(x, y, object);
}

void SpaceStation::gotId(QByteArray id)
{
	m_mapWorker->setPlayerId(id);
	log ("Player ID: " + id);
}

void SpaceStation::playerDisconnected(QByteArray id)
{
	m_mapWorker->removePlayer(id);
}

void SpaceStation::movePlayer(playerMovement side)
{
	m_connectionManager->movePlayer(side);
}

void SpaceStation::actPlayerOpenClose(QString action)
{
	m_connectionManager->actionPlayer(action, m_selectDirectionDialog->exec());
}

void SpaceStation::keyPressEvent(QKeyEvent *event)
{	
	m_selectDirectionDialog = new SelectDirectionDialog();

	QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
	switch (keyEvent->key()) {
		case Qt::Key_W: movePlayer(moveUp); break;
		case Qt::Key_S: movePlayer(moveDown); break;
		case Qt::Key_A: movePlayer(moveLeft); break;
		case Qt::Key_D: movePlayer(moveRight); break;
		case Qt::Key_O: actPlayerOpenClose("OPEN"); break;
		case Qt::Key_C: actPlayerOpenClose("CLOSE"); break;
	}

	delete m_selectDirectionDialog;
}

void SpaceStation::initMenus()
{
	m_mFile = new QMenu("File");
	m_mSettings = new QMenu("Settings");
	m_mToolBars = new QMenu("Toolbars");

	m_actConnect = new QAction("Connect");
	m_quit = new QAction("Quit");

	m_followPlayer = new QAction("Follow player");
	m_followPlayer->setCheckable(true);

	m_showActionsMenu = new QAction("Actions menu");

	m_mFile->addAction(m_actConnect);
	m_mFile->addAction(m_quit);

	m_mSettings->addAction(m_followPlayer);

	m_mToolBars->addAction(m_showActionsMenu);

	ui->menubar->addMenu(m_mFile);
	ui->menubar->addMenu(m_mSettings);
	ui->menubar->addMenu(m_mToolBars);
	ui->menubar->show();

	connect (m_actConnect, &QAction::triggered, this, &SpaceStation::connectToServer);
	connect (m_quit, &QAction::triggered, this, &SpaceStation::close);
	connect (m_quit, &QAction::triggered, m_actionWindow, &ActionWindow::close);
	connect (m_showActionsMenu, &QAction::triggered, this, &SpaceStation::actShowActionsMenu);
}

void SpaceStation::initConnectionManager()
{
	m_connectionManager = new ConnectionManager();
	m_networkingThread = new QThread();
	m_connectionManager->moveToThread(m_networkingThread);
	m_networkingThread->start();
}

void SpaceStation::initGraphics()
{
	m_mapWorker = new MapWorker();
	m_mapWorker->setCellSizePixels(30);

	m_scene = new QGraphicsScene(0, 0, m_mapWorker->getMapSizeX(), m_mapWorker->getMapSizeY());
	ui->graphicsView->setScene(m_scene);
	ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
	ui->graphicsView->setRenderHints(QPainter::Antialiasing);
	ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	ui->graphicsView->setCacheMode(QGraphicsView::CacheNone);
	m_mapWorker->setScene(m_scene);
}

void SpaceStation::log(QString message)
{
	qDebug() << "[Core]: " << message;
}
