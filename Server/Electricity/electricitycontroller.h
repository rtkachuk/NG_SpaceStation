#ifndef ELECTRICITYCONTROLLER_H
#define ELECTRICITYCONTROLLER_H

#include <QObject>

#include "electricgenerator.h"

class ElectricityController : public QObject
{
	Q_OBJECT
public:
	explicit ElectricityController(QObject *parent = nullptr);

signals:

};

#endif // ELECTRICITYCONTROLLER_H
