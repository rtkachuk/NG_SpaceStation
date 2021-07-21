#include "inventorywindow.h"
#include "ui_inventorywindow.h"

InventoryWindow::InventoryWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::InventoryWindow)
{
	ui->setupUi(this);
}

InventoryWindow::~InventoryWindow()
{
	delete ui;
}
