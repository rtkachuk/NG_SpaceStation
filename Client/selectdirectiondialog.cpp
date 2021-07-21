#include "selectdirectiondialog.h"
#include "ui_selectdirectiondialog.h"

SelectDirectionDialog::SelectDirectionDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SelectDirectionDialog)
{
	ui->setupUi(this);
}

SelectDirectionDialog::~SelectDirectionDialog()
{
	delete ui;
}

void SelectDirectionDialog::keyPressEvent(QKeyEvent *event)
{
	QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
	switch (keyEvent->key()) {
		case Qt::Key_W: done(1); break;
		case Qt::Key_S: done(2); break;
		case Qt::Key_A: done(3); break;
		case Qt::Key_D: done(4); break;
	}
}
