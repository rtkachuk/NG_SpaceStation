#ifndef INVENTORYMENU_H
#define INVENTORYMENU_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "../sharedItemLoader/itemloader.h"

namespace Ui {
class InventoryMenu;
}

class InventoryMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit InventoryMenu(QWidget *parent = nullptr);
    ~InventoryMenu();

	QByteArray getSelectedItem();
	void addItem(QByteArray item);
	void removeItem(QByteArray item);

	void setItemLoader(ItemLoader *loader) { m_itemLoader = loader; }

public slots:
	void processTakingOffItem(QByteArray id);
	void processWearingItem(QByteArray id);

signals:
	void sendWearItem(QByteArray data);
	void sendTakeOffItem(QByteArray data);

private:
	void clearWereable(QString name, QString text);
	void redrawInventory();

private slots:
	void selectedItem(int row, int column);
	void wearItem();
	void takeOffItem();

private:

    Ui::InventoryMenu *ui;
	ItemLoader* m_itemLoader;

	const int rows =5;
	const int columns = 9;

	QList<QString> m_items;

    void log(QString message);
};

#endif // INVENTORYMENU_H
