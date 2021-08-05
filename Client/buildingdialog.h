#ifndef BUILDINGDIALOG_H
#define BUILDINGDIALOG_H

#include <QDialog>
#include <../recipesLoader/recipesloader.h>
#include <../sharedItemLoader/itemloader.h>

namespace Ui {
class BuildingDialog;
}

class BuildingDialog : public QDialog
{
	Q_OBJECT

public:
	explicit BuildingDialog(ItemLoader *loader, QWidget *parent = nullptr);
	QByteArray getItem();
	~BuildingDialog();

private:
	void log(QString message);
	Ui::BuildingDialog *ui;
	RecipesLoader *m_recipesLoader;
	ItemLoader *m_itemLoader;
};

#endif // BUILDINGDIALOG_H
