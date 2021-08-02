#include "healthcontrol.h"


HealthControl::HealthControl()
{

}

void HealthControl::makeDamage(QTcpSocket *player, int damage)
{
	setPlayerHealth(player, getHealth(player) - damage);
}
