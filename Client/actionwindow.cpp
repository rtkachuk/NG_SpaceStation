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
    connect(ui->b_push, &QPushButton::clicked, this, &ActionWindow::actPush);
	connect (ui->b_up, &QPushButton::clicked, this, &ActionWindow::actMoveUp);
	connect (ui->b_down, &QPushButton::clicked, this, &ActionWindow::actMoveDown);
	connect (ui->b_left, &QPushButton::clicked, this, &ActionWindow::actMoveLeft);
	connect (ui->b_right, &QPushButton::clicked, this, &ActionWindow::actMoveRight);
}

ActionWindow::~ActionWindow()
{
	delete ui;
}
