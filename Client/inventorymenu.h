#ifndef INVENTORYMENU_H
#define INVENTORYMENU_H

#include <QMainWindow>
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

private:
    Ui::InventoryMenu *ui;
	ItemLoader* m_itemLoader;
};

#endif // INVENTORYMENU_H
