#include "statewindow.h"
#include "ui_statewindow.h"

StateWindow::StateWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StateWindow)
{
    ui->setupUi(this);
}

StateWindow::~StateWindow()
{
    delete ui;
}

void StateWindow::showHP(int number)
{
   ui->healthState->display(number);
}
