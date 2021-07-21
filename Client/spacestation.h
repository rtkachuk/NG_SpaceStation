#ifndef SPACESTATION_H
#define SPACESTATION_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>

#include "mapworker.h"
#include "actionwindow.h"

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

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	void initMenus();
	void log(QString message);

	Ui::SpaceStation *ui;
	QGraphicsScene *m_scene;
	MapWorker *m_mapWorker;

	QMenu *m_mFile;
	QMenu *m_mSettings;

	QAction *m_quit;
	QAction *m_followPlayer;

	ActionWindow *m_actionWindow;
};
#endif // SPACESTATION_H
