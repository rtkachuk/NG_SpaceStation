#ifndef SPACESTATION_H
#define SPACESTATION_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QThread>
#include <QScrollBar>
#include <QMetaMethod>

#include "mapworker.h"
#include "actionwindow.h"
#include "connectdialog.h"
#include "connectionmanager.h"
#include "selectdirectiondialog.h"
#include "inventorymenu.h"
#include "../sharedItemLoader/itemloader.h"
#include "statewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpaceStation; }
QT_END_NAMESPACE

class SpaceStation : public QMainWindow
{
	Q_OBJECT

public:
	SpaceStation(QWidget *parent = nullptr);
	~SpaceStation();

public slots:
    void hpShow(int HP);

private slots:
	void actFindPlayer();

	void actShowActionsMenu();
    void actShowInventoryMenu();
    void actShowHPMenu();

	void connectToServer();
	void connectedToServer();

	void mapReceived();
	void setPlayerPosition(QByteArray id, int x, int y);
	void chatMessage(QString message);
	void mapChanged(int x, int y, char object);
	void gotId(QByteArray id);
	void playerDisconnected(QByteArray id);

	void movePlayer(playerMovement side);
	void processPlayerAction(QString action);

	void processItem(QByteArray id);
	QByteArray getDropItemCommand();

	void gotInitPlayerPosition(position pos);

	void sendMessage();

	void placeItem(ItemInfo item);
	void removeItem(ItemInfo item);

	void wearItem(QByteArray id);
	void takeOffItem(QByteArray id);

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	void initMenus();
	void initConnectionManager();
	void initGraphics();
	int askDirection();
	void log(QString message);

	QString m_ip;
	QString m_port;
	QString m_name;

	Ui::SpaceStation *ui;
	QGraphicsScene *m_scene;
	MapWorker *m_mapWorker;

	QMenu *m_mFile;
	QMenu *m_mSettings;
	QMenu *m_mToolBars;

	QAction *m_actConnect;
	QAction *m_quit;
	QAction *m_followPlayer;
	QAction *m_showActionsMenu;
    QAction *m_showInventoryMenu;
    QAction *m_showHPMenu;

	ActionWindow *m_actionWindow;
	ConnectDialog *m_connectDialog;
	ConnectionManager *m_connectionManager;
	SelectDirectionDialog *m_selectDirectionDialog;
    InventoryMenu *m_inventory;
	ItemLoader *m_itemLoader;
    StateWindow *m_stateWindow;

	QThread *m_networkingThread;
};
#endif // SPACESTATION_H
