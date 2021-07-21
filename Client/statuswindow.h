#ifndef STATUSWINDOW_H
#define STATUSWINDOW_H

#include <QMainWindow>

namespace Ui {
class StatusWindow;
}

class StatusWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit StatusWindow(QWidget *parent = nullptr);
	~StatusWindow();

private:
	Ui::StatusWindow *ui;
};

#endif // STATUSWINDOW_H
