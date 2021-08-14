#include "electricnode.h"

ElectricNode::ElectricNode(QObject *parent) : QObject(parent)
{
	m_powered = false;
    m_opened = false;
}

void ElectricNode::setPowered(bool powered)
{
    m_powered = powered;
    if (m_opened) {
        if (m_powered)
            emit stateChanged("POWERED");
        else
            emit stateChanged("HALT");
    }
}

void ElectricNode::setOpened(bool opened)
{
    m_opened = opened;
    if (m_opened)
        if (m_powered)
            emit stateChanged("POWERED");
        else
            emit stateChanged("HALT");
    else
        emit stateChanged("CLOSED");
}
