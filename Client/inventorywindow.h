#ifndef INVENTORYWINDOW_H
#define INVENTORYWINDOW_H

#include <QMainWindow>

namespace Ui {
class InventoryWindow;
}

class InventoryWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit InventoryWindow(QWidget *parent = nullptr);
	~InventoryWindow();

private:
	Ui::InventoryWindow *ui;
};

#endif // INVENTORYWINDOW_H
