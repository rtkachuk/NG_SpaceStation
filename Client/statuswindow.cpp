#include "statuswindow.h"
#include "ui_statuswindow.h"

StatusWindow::StatusWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::StatusWindow)
{
	ui->setupUi(this);
}

StatusWindow::~StatusWindow()
{
	delete ui;
}
