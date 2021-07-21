#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QTcpSocket>
#include <QObject>

class ConnectionManager : public QObject
{
	Q_OBJECT
public:
	explicit ConnectionManager();
	void connectToServer(QString ip, QString port);
	QByteArray loadData();

private:
	void log(QString msg);

private slots:
	void connectedToServer();
	void socketReady();

signals:
	void dataReady();
	void connected();

private:
	QTcpSocket *m_socket;

};

#endif // CONNECTIONMANAGER_H
