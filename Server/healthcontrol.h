#ifndef HEALTHCONTROL_H
#define HEALTHCONTROL_H

#include <QObject>
#include<QMap>
#include<QTcpSocket>

class HealthControl
{
public:
    HealthControl();
    void createPlayerHealth(QTcpSocket *player){m_healthPlayer[player]=100;}
    void deleteHealth(QTcpSocket *player){m_healthPlayer[player]=0;}
    void setDamage(QTcpSocket *player,int damage);
    int getHealth(QTcpSocket *player){return m_healthPlayer[player];}
private:
    QMap<QTcpSocket*,int> m_healthPlayer;
};

#endif // HEALTHCONTROL_H
