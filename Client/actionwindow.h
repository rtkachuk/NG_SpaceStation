#ifndef ACTIONWINDOW_H
#define ACTIONWINDOW_H

#include <QMainWindow>
#include "enums.h"

namespace Ui {
class ActionWindow;
}

class ActionWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit ActionWindow(QWidget *parent = nullptr);
	~ActionWindow();

signals:
	void askFindPlayer();
    void getRequestPush(QString data);
    void getRequestKick(QString data);
    void getRequestPull(QString data);
	void openSomething(QString data);
	void closeSomething(QString data);
	void movePlayer(playerMovement mov);

private slots:
	void actFindPlayer() { emit askFindPlayer(); }
	void actOpen() { emit openSomething("OPEN"); }
	void actClose() { emit closeSomething("CLOSE"); }
    void actPush() { emit  getRequestPush("PUSH"); }
    void actKick() { emit  getRequestKick("KICK"); }
    void actPull() { emit  getRequestPull("PULL"); }
	void actMoveUp() { emit movePlayer(playerMovement::moveUp); }
	void actMoveDown() { emit movePlayer(playerMovement::moveDown); }
	void actMoveLeft() { emit movePlayer(playerMovement::moveLeft); }
	void actMoveRight() { emit movePlayer(playerMovement::moveRight); }

private:
	Ui::ActionWindow *ui;
};

#endif // ACTIONWINDOW_H
