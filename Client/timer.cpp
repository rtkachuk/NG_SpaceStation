#include "timer.h"
#include "ui_timer.h"

Timer::Timer(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Timer)
{
	ui->setupUi(this);
}

Timer::~Timer()
{
	delete ui;
}

int Timer::getTime()
{
	return ui->sb_seconds->value();
}
