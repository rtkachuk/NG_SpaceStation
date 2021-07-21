#include "actionwindow.h"
#include "ui_actionwindow.h"

ActionWindow::ActionWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::ActionWindow)
{
	ui->setupUi(this);

	connect (ui->b_findMe, &QPushButton::clicked, this, &ActionWindow::actFindPlayer);
}

ActionWindow::~ActionWindow()
{
	delete ui;
}

void ActionWindow::actFindPlayer()
{
	emit askFindPlayer();
}
