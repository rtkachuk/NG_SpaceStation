#include "inventorymenu.h"
#include "ui_inventorymenu.h"

InventoryMenu::InventoryMenu(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::InventoryMenu)
{
	ui->setupUi(this);

	ui->text_description->setReadOnly(true);

	connect (ui->list_inventory, &QListWidget::itemClicked, this, &InventoryMenu::selectedItem);
}

InventoryMenu::~InventoryMenu()
{
	delete ui;
}

QByteArray InventoryMenu::getSelectedItem()
{
	if (ui->list_inventory->currentItem() != nullptr)
		return m_itemLoader->getIdByName(ui->list_inventory->currentItem()->text().toUtf8());
	else
		return "";
}

void InventoryMenu::addItem(QByteArray item)
{
	BaseItem tool;
	tool = m_itemLoader->getItemById(item);
	if(tool.getId() != "-1")
	{
		log("Item to be picked: " + tool.getName());
		ui->list_inventory->addItem(tool.getName());
	}
}

void InventoryMenu::removeItem(QByteArray id)
{
	BaseItem tool;
	tool = m_itemLoader->getItemById(id);

	QByteArray item;

	log("Item id: " + tool.getId());
	if(tool.getId() != "-1")
	{
		item = tool.getName().toUtf8();
		log("Item to be dropped: " + item);
	}
	delete ui->list_inventory->findItems(item, Qt::MatchExactly)[0];

}

void InventoryMenu::selectedItem(QListWidgetItem(* item))
{
	ui->text_description->setText(m_itemLoader->getItemById(m_itemLoader->getIdByName(item->text())).getDescription());
}

void InventoryMenu::log(QString message)
{
	qDebug() << "[InventoryMenu]: " << message;
}
