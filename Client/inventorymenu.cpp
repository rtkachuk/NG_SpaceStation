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
    BaseTool tool;
    BaseWeapon weapon;
    tool = m_itemLoader->getToolById(item);
    weapon = m_itemLoader->getWeaponById(item);
    if(tool.getId() != "-1")
    {
        log("Item to be picked: " + tool.getName());
        ui->list_inventory->addItem(tool.getName());
    }
    if(weapon.getId() != "-1")
    {
        log("Item to be picked: " + weapon.getName());
        ui->list_inventory->addItem(weapon.getName());
    }
}

void InventoryMenu::removeItem(QByteArray id)
{
    BaseTool tool;
    BaseWeapon weapon;
    tool = m_itemLoader->getToolById(id);
    weapon = m_itemLoader->getWeaponById(id);

    QByteArray item;

    log("Tool id: " + tool.getId());
    if(tool.getId() != "-1")
    {
        item = tool.getName().toUtf8();
        log("Item to be dropped: " + item);
    }
    log("Weapon id: " + weapon.getId());
    if(weapon.getId() != "-1")
    {
        item = weapon.getName().toUtf8();
        log("Item to be dropped: " + item);
    }
   delete ui->list_inventory->findItems(item, Qt::MatchExactly)[0];

}

void InventoryMenu::log(QString message)
{
    qDebug() << "[InventoryMenu]: " << message;
}
