#include "inventorymenu.h"
#include "ui_inventorymenu.h"

InventoryMenu::InventoryMenu(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::InventoryMenu)
{
	ui->setupUi(this);

	ui->text_description->setReadOnly(true);

	// Init the inventory

	ui->table_inventory->setRowCount(rows);
	ui->table_inventory->setColumnCount(columns);
	ui->table_inventory->horizontalHeader()->hide();
	ui->table_inventory->verticalHeader()->hide();
	ui->table_inventory->horizontalHeader()->setDefaultSectionSize(40);
	ui->table_inventory->verticalHeader()->setDefaultSectionSize(40);
	ui->table_inventory->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
	ui->table_inventory->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
	ui->table_inventory->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->table_inventory->setIconSize(QSize(40,40));

	//ui->table_inventory->horizontalHeader()->setSectionResizeMode(10, QHeaderView::Fixed);

	connect (ui->table_inventory, &QTableWidget::cellClicked, this, &InventoryMenu::selectedItem);
	connect (ui->b_wear, &QPushButton::clicked, this, &InventoryMenu::wearItem);
	connect (ui->b_takeoff, &QPushButton::clicked, this, &InventoryMenu::takeOffItem);
}

InventoryMenu::~InventoryMenu()
{
	delete ui;
}

QByteArray InventoryMenu::getSelectedItem()
{
	if (ui->table_inventory->currentItem() != nullptr) {
		int column = ui->table_inventory->currentItem()->column();
		int row = ui->table_inventory->currentItem()->row();
		int index = row*column + column;
		if (m_items.size()-1 >= index)
			return m_itemLoader->getIdByName(m_items[index].toUtf8());
	}
	return "";
}

void InventoryMenu::addItem(QByteArray item)
{
	BaseItem tool;
	tool = m_itemLoader->getItemById(item);
	if(tool.getId() != "-1") {
		m_items.append(tool.getName());
		redrawInventory();
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
	} else
		return;

	m_items.removeOne(item);
	redrawInventory();
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

void InventoryMenu::redrawInventory()
{
	ui->table_inventory->clear();
	int currentItem = 0;
	for (QString buffer : m_items) {
		int row = currentItem/columns;
		int column = currentItem - row;
		if (column < 0) column = 0;

		ui->table_inventory->setItem(row, column, new QTableWidgetItem(QIcon(":" + m_itemLoader->getItemById(m_itemLoader->getIdByName(buffer)).getPixmap()), buffer));
		currentItem++;
	}
}

void InventoryMenu::selectedItem(int row, int column)
{
	ui->text_description->clear();
	int index = row*columns + column;
	qDebug() << row << ":::" << column;
	qDebug() << index;
	if (m_items.size()-1 < index) return;
	QString name = m_items[index];
	ui->text_description->setText(m_itemLoader->getItemById(m_itemLoader->getIdByName(name)).getDescription());
}

void InventoryMenu::wearItem()
{
	QByteArray id = getSelectedItem();
	emit sendWearItem(id);
}

void InventoryMenu::takeOffItem()
{
	if (ui->table_inventory->currentItem() == nullptr) return;

	QString name = ui->table_inventory->currentItem()->text();
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
