#include "buildingdialog.h"
#include "ui_buildingdialog.h"

BuildingDialog::BuildingDialog(ItemLoader *loader, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::BuildingDialog)
{
	ui->setupUi(this);
	m_recipesLoader = new RecipesLoader();
	m_itemLoader = loader;
	QList<QByteArray> recipes = m_recipesLoader->getAvaiableRecipes();

	for (QByteArray item : recipes) {
		QString name = m_itemLoader->getItemById(item).getName();
		name == "<NONAME>" ? ui->l_builds->addItem(item) : ui->l_builds->addItem(name);
	}
	ui->l_builds->setCurrentRow(0);
}

QByteArray BuildingDialog::getItem()
{
	QString text = ui->l_builds->currentItem()->text();
	QByteArray id = m_itemLoader->getIdByName(text);
	log (text);
	log (id);
	if (id == "") return text.toUtf8(); else return id;
}

BuildingDialog::~BuildingDialog()
{
	delete ui;
}

void BuildingDialog::log(QString message)
{
	qDebug() << "[BuildingDialog]: " << message;
}
