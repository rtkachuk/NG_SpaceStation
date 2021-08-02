#include "healthcontrol.h"


HealthControl::HealthControl()
{

}

int HealthControl::makeDamage(QTcpSocket *player, int damage)
{
  m_healthPlayer[player]-=damage;
  return getHealth(player);
}
