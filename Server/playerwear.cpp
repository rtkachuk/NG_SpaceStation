#include "playerwear.h"

PlayerWear::PlayerWear()
{

}

PlayerWear::PlayerWear(ItemLoader *loader)
{
	m_loader = loader;
}

QByteArray PlayerWear::wearDressing(QByteArray id, playerWearable place)
{
	QByteArray responce = "WEAR:" + id + ":";
	switch (place) {
		case playerWearable::head: m_head = id; responce += "HEAD"; break;
		case playerWearable::feet: m_feet = id; responce += "FEET"; break;
		case playerWearable::gloves: m_hands = id; responce += "HANDS"; break;
		case playerWearable::legs: m_legs = id; responce += "LEGS"; break;
		case playerWearable::torso: m_torso = id; responce += "TORSO"; break;
		default: log ("Wrong clothing place provided: "); responce = "";
	}

	return responce;
}

QByteArray PlayerWear::unwear(playerWearable place)
{
	QByteArray responce = "TAKEOFF:";
	switch (place) {
		case playerWearable::head: m_head = ""; responce += "HEAD"; break;
		case playerWearable::feet: m_feet = ""; responce += "FEET"; break;
		case playerWearable::gloves: m_hands = ""; responce += "HANDS"; break;
		case playerWearable::legs: m_legs = ""; responce += "LEGS"; break;
		case playerWearable::torso: m_torso = ""; responce += "TORSO"; break;
		default: log ("Wrong clothing place provided: "); responce = "";
	}

	return responce;
}

void PlayerWear::log(QString msg)
{
	qDebug() << "[PlayerWear]: " << msg;
}
