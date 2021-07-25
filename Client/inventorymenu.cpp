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

QByteArray InventoryMenu::getSelectedItem()
{
	if (ui->list_inventory->currentItem() != nullptr)
		return ui->list_inventory->currentItem()->text().toUtf8();
	else
		return "";
}

void InventoryMenu::addItem(QByteArray item)
{
	ui->list_inventory->addItem(item);
}

void InventoryMenu::removeItem(QByteArray item)
{
	delete ui->list_inventory->findItems(item, Qt::MatchExactly)[0];
}
