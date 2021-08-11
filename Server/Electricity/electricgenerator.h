#ifndef ELECTRICGENERATOR_H
#define ELECTRICGENERATOR_H

#include <QObject>

class ElectricGenerator : public QObject
{
	Q_OBJECT
public:
	explicit ElectricGenerator(QObject *parent = nullptr);

signals:

};

#endif // ELECTRICGENERATOR_H
