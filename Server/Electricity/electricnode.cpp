#include "electricnode.h"

ElectricNode::ElectricNode(QObject *parent) : QObject(parent)
{
	m_powered = false;
}
