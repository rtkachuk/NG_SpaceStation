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

private slots:
	void actFindPlayer();

private:
	Ui::ActionWindow *ui;
};

#endif // ACTIONWINDOW_H
