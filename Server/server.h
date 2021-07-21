#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class Server : public QTcpServer
{
	Q_OBJECT
public:
	Server();

private:
	void log(QString msg);

	QVector<QTcpSocket*> m_players;

private slots:
	void readyRead();
	void disconnected();

protected:
	void incomingConnection(qintptr handle);
};

#endif // SERVER_H
