#ifndef TIMER_H
#define TIMER_H

#include <QDialog>

namespace Ui {
class Timer;
}

class Timer : public QDialog
{
	Q_OBJECT

public:
	explicit Timer(QWidget *parent = nullptr);
	~Timer();
	int getTime();

private:
	Ui::Timer *ui;
};

#endif // TIMER_H
