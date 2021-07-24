#include "inventorymenu.h"
#include "ui_inventorymenu.h"

InventoryMenu::InventoryMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InventoryMenu)
{
    ui->setupUi(this);
}

InventoryMenu::~InventoryMenu()
{
    delete ui;
}
