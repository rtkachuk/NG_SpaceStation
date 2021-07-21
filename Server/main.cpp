#include <QCoreApplication>

#include "server.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	Server *servak = new Server();

	int port = 4306;

	bool ok = servak->listen(QHostAddress::Any, port);

	if (ok) {
		qDebug() << "[CORE]: Server started at: " << servak->serverAddress().toString() << ", port: " << servak->serverPort();
	} else {
		qDebug() << "[CORE]: Server failed to start: " << servak->errorString();
	}

	return a.exec();
}
