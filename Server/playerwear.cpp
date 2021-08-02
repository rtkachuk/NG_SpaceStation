#include "playerwear.h"

PlayerWear::PlayerWear()
{
	m_wears[playerWearable::head] = "";
	m_wears[playerWearable::torso] = "";
	m_wears[playerWearable::gloves] = "";
	m_wears[playerWearable::legs] = "";
	m_wears[playerWearable::feet] = "";
	m_wears[playerWearable::holdable] = "";
}

PlayerWear::PlayerWear(ItemLoader *loader)
{
	m_loader = loader;
	PlayerWear();
}

void PlayerWear::log(QString msg)
{
	qDebug() << "[PlayerWear]: " << msg;
}
