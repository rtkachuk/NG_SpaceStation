#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ConnectDialog)
{
	ui->setupUi(this);

	ui->l_ip->setText("127.0.0.1");
	ui->l_port->setText("4306");

	connect (ui->b_connect, &QPushButton::clicked, this, &ConnectDialog::connectToHost);
	connect (ui->b_cancel, &QPushButton::clicked, this, &ConnectDialog::reject);
}

ConnectDialog::~ConnectDialog()
{
	delete ui;
}

void ConnectDialog::connectToHost()
{
	if (ui->l_ip->text().isEmpty() || ui->l_port->text().isEmpty()) {
		QMessageBox::critical(this, "Something wrong", "Please, fill ip and port lines");
		return;
	}

	m_ip = ui->l_ip->text();
	m_port = ui->l_port->text();

	accept();
}
