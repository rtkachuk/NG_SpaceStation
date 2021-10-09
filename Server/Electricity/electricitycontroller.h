#ifndef ELECTRICITYCONTROLLER_H
#define ELECTRICITYCONTROLLER_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QFile>

#include "electricgenerator.h"
#include "electricnode.h"
#include "../utilities.h"

enum electricityObjectType {
    generator,
    node,
    none
};

class ElectricityController : public QObject
{
	Q_OBJECT
public:
	explicit ElectricityController(QObject *parent = nullptr);
	void addGenerator(position pos);
    void removeGenerator(position pos);
	void addNode(position pos);
    void removeNode(position pos);
    void addWire(position pos);
    void removeWire(position pos);
    QByteArray getNewPlayerInfo();
    electricityObjectType getObjectByCords(position pos);
	void clearCell(position pos);

    void switchGenerator(position pos);
    void switchNode(position pos);

    bool checkWireExist(position pos);

public slots:
	void processElectricityLines();

signals:
    void requiredElectricityUpdate();
    void updateGeneratorState(position pos, QByteArray state);
    void updateNodeState(position pos, QByteArray state);

private slots:
    void updatedGeneratorState(QByteArray state);
    void updatedNodeState(QByteArray state);

private:
    void turnOffEverythingBeforeRecalculating();
	void loadMap();
	void processMap(QByteArray *map);
	int inspectLine(position pos, position previous, bool powered);
	bool checkSideLine(position pos, position previous);
	bool checkLineExist(position pos);
    void updateNodesState(position pos, bool state);
	void log(QString msg);
	QMap<ElectricGenerator*, position> m_generators;
	QMap<position, ElectricNode*> m_nodes;
	QVector<QVector<char>> m_wireMap;

};

#endif // ELECTRICITYCONTROLLER_H
