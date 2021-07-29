#include "inventorymenu.h"
#include "ui_inventorymenu.h"

InventoryMenu::InventoryMenu(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::InventoryMenu)
{
	ui->setupUi(this);

	ui->text_description->setReadOnly(true);

	connect (ui->list_inventory, &QListWidget::itemClicked, this, &InventoryMenu::selectedItem);
	connect (ui->b_wear, &QPushButton::clicked, this, &InventoryMenu::wearItem);
	connect (ui->b_takeoff, &QPushButton::clicked, this, &InventoryMenu::takeOffItem);
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
		ui->list_inventory->addItem(tool.getName());
	}
}

void InventoryMenu::removeItem(QByteArray id)
{
	BaseItem tool;
	tool = m_itemLoader->getItemById(id);

	QByteArray item;

	if(tool.getId() != "-1")
	{
		item = tool.getName().toUtf8();
	}
	delete ui->list_inventory->findItems(item, Qt::MatchExactly)[0];

}

void InventoryMenu::clearWereable(QString name, QString text)
{
	if (ui->l_feet->text() == name) ui->l_feet->setText(text);
	if (ui->l_hands->text() == name) ui->l_hands->setText(text);
	if (ui->l_head->text() == name) ui->l_head->setText(text);
	if (ui->l_hold->text() == name) ui->l_hold->setText(text);
	if (ui->l_torso->text() == name) ui->l_torso->setText(text);
	if (ui->l_trousers->text() == name) ui->l_trousers->setText(text);
}

void InventoryMenu::selectedItem(QListWidgetItem(* item))
{
	ui->text_description->setText(m_itemLoader->getItemById(m_itemLoader->getIdByName(item->text())).getDescription());
}

void InventoryMenu::wearItem()
{
	QByteArray id = getSelectedItem();
	emit sendWearItem(id);
}

void InventoryMenu::takeOffItem()
{
	if (ui->list_inventory->currentItem() == nullptr) return;

	QString name = ui->list_inventory->currentItem()->text();
	QByteArray id = m_itemLoader->getIdByName(name);
	emit sendTakeOffItem(id);
}

void InventoryMenu::processTakingOffItem(QByteArray id)
{

	clearWereable(m_itemLoader->getItemById(id).getName(), "Nothing");
}

void InventoryMenu::processWearingItem(QByteArray id)
{
	BaseItem tool = m_itemLoader->getItemById(id);
	QString name = tool.getName();

	switch(tool.getWearableMode()) {
		case playerWearable::feet: ui->l_feet->setText(name); break;
		case playerWearable::gloves: ui->l_hands->setText(name); break;
		case playerWearable::head: ui->l_head->setText(name); break;
		case playerWearable::holdable: ui->l_hold->setText(name); break;
		case playerWearable::legs: ui->l_trousers->setText(name); break;
		case playerWearable::torso: ui->l_torso->setText(name); break;
		default: log ("Wrong wereable processed during wearing");
	}
}

void InventoryMenu::log(QString message)
{
	qDebug() << "[InventoryMenu]: " << message;
}
