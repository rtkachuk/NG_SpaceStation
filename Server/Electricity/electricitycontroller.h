#ifndef ELECTRICITYCONTROLLER_H
#define ELECTRICITYCONTROLLER_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QFile>

#include "electricgenerator.h"
#include "electricnode.h"
#include "../utilities.h"

class ElectricityController : public QObject
{
	Q_OBJECT
public:
	explicit ElectricityController(QObject *parent = nullptr);
	void addGenerator(position pos);
	void addNode(position pos);

public slots:
	void processElectricityLines();

signals:

private:
	void loadMap();
	void processMap(QByteArray *map);
	int inspectLine(position pos, position previous, bool powered);
	bool checkSideLine(position pos, position previous);
	bool checkLineExist(position pos);
	void updateNodeState(position pos, bool state);
	void log(QString msg);
	QMap<ElectricGenerator*, position> m_generators;
	QMap<position, ElectricNode*> m_nodes;
	QVector<QVector<char>> m_wireMap;

};

#endif // ELECTRICITYCONTROLLER_H
