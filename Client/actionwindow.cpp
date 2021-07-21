#include "actionwindow.h"
#include "ui_actionwindow.h"

ActionWindow::ActionWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::ActionWindow)
{
	ui->setupUi(this);
}

ActionWindow::~ActionWindow()
{
	delete ui;
}
