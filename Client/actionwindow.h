#ifndef ACTIONWINDOW_H
#define ACTIONWINDOW_H

#include <QMainWindow>

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

	void openSomething();
	void closeSomething();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

private slots:
	void actFindPlayer() { emit askFindPlayer(); }
	void actOpen() { emit openSomething(); }
	void actClose() { emit closeSomething(); }

	void actMoveUp() { emit moveUp(); }
	void actMoveDown() { emit moveDown(); }
	void actMoveLeft() { emit moveLeft(); }
	void actMoveRight() { emit moveRight(); }

private:
	Ui::ActionWindow *ui;
};

#endif // ACTIONWINDOW_H
