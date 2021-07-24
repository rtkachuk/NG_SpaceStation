#ifndef INVENTORYMENU_H
#define INVENTORYMENU_H

#include <QMainWindow>

namespace Ui {
class InventoryMenu;
}

class InventoryMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit InventoryMenu(QWidget *parent = nullptr);
    ~InventoryMenu();

private:
    Ui::InventoryMenu *ui;
};

#endif // INVENTORYMENU_H
