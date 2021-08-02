#ifndef HEALTHCONTROL_H
#define HEALTHCONTROL_H

#include <QObject>
#include <QMap>
#include <QTcpSocket>
#include <QDebug>

class HealthControl
{
public:
    HealthControl();
	void setPlayerHealth(QTcpSocket *player, int value){ m_healthPlayer[player] = value; }
	void deleteHealth(QTcpSocket *player){ m_healthPlayer.remove(player); }
	void makeDamage(QTcpSocket *player,int damage);
	int getHealth(QTcpSocket *player) { return m_healthPlayer[player]; }
private:
    QMap<QTcpSocket*,int> m_healthPlayer;
};

#endif // HEALTHCONTROL_H
