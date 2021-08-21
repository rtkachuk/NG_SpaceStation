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
    void setPowered(bool powered);
    bool isOpened() { return m_opened; }
    void setOpened(bool opened);

signals:
    void stateChanged(QByteArray state);
private:
	bool m_powered;
    bool m_opened;
};

#endif // ELECTRICNODE_H
