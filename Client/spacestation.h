#ifndef SPACESTATION_H
#define SPACESTATION_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QThread>
#include <QScrollBar>

#include "mapworker.h"
#include "actionwindow.h"
#include "connectdialog.h"
#include "connectionmanager.h"
#include "selectdirectiondialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpaceStation; }
QT_END_NAMESPACE

class SpaceStation : public QMainWindow
{
	Q_OBJECT

public:
	SpaceStation(QWidget *parent = nullptr);
	~SpaceStation();

private slots:
	void actFindPlayer();

	void connectToServer();
	void connectedToServer();
	void mapReceived();
	void setPlayerPosition(int x, int y);
	void chatMessage(QString message);
	void mapChanged(int x, int y, char object);

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	void initMenus();
	void initConnectionManager();
	void initGraphics();
	void log(QString message);

	QString m_ip;
	QString m_port;

	Ui::SpaceStation *ui;
	QGraphicsScene *m_scene;
	MapWorker *m_mapWorker;

	QMenu *m_mFile;
	QMenu *m_mSettings;

	QAction *m_actConnect;
	QAction *m_quit;
	QAction *m_followPlayer;

	ActionWindow *m_actionWindow;
	ConnectDialog *m_connectDialog;
	ConnectionManager *m_connectionManager;
	SelectDirectionDialog *m_selectDirectionDialog;

	QThread *m_networkingThread;
};
#endif // SPACESTATION_H
