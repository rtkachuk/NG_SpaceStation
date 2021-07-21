#include "spacestation.h"

#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QPixmap loading(":/misc/loading.png");
	QSplashScreen splash(loading);
	splash.show();
	a.processEvents();
	splash.showMessage("Загрузка карты");
	SpaceStation w;
	w.show();
	splash.finish(&w);
	return a.exec();
}
