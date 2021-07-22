#include "actionwindow.h"
#include "ui_actionwindow.h"

ActionWindow::ActionWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::ActionWindow)
{
	ui->setupUi(this);

	connect (ui->b_findMe, &QPushButton::clicked, this, &ActionWindow::actFindPlayer);

	connect (ui->b_open, &QPushButton::clicked, this, &ActionWindow::actOpen);
	connect (ui->b_close, &QPushButton::clicked, this, &ActionWindow::actClose);
}

ActionWindow::~ActionWindow()
{
	delete ui;
}
