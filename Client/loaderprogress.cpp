#include "loaderprogress.h"
#include "ui_loaderprogress.h"

LoaderProgress::LoaderProgress(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LoaderProgress)
{
	ui->setupUi(this);
}

void LoaderProgress::setValue(int value)
{
	ui->progressBar->setValue(value * m_step);
	ui->progressLabel->setText(QString::number(value) + "/" + QString::number(m_maximum));
}

LoaderProgress::~LoaderProgress()
{
	delete ui;
}
