#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ConnectDialog(QWidget *parent = nullptr);
	~ConnectDialog();

	QString getIp() { return m_ip; }
	QString getPort() { return m_port; }

private slots:
	void connectToHost();

private:

	QString m_ip;
	QString m_port;

	Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
