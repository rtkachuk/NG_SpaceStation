#ifndef ELECTRICNODE_H
#define ELECTRICNODE_H

#include <QObject>

#include "../utilities.h"

class ElectricNode : public QObject
{
	Q_OBJECT
public:
	explicit ElectricNode(QObject *parent = nullptr);
	bool isPowered() { return m_powered; }
	void setPowered(bool powered) { m_powered = powered; }


signals:

private:
	position m_pos;
	bool m_powered;

};

#endif // ELECTRICNODE_H
