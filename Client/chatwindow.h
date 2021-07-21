#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit ChatWindow(QWidget *parent = nullptr);
	~ChatWindow();

private:
	Ui::ChatWindow *ui;
};

#endif // CHATWINDOW_H
