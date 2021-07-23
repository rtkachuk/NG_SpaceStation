#ifndef BASEITEM_H
#define BASEITEM_H

#include <QByteArray>
#include <QString>

enum playerWearable {
	itemnomode,
	head,
	torso,
	legs,
	foot,
	holdable,
	gloves
};

enum itemType {
	notype,
	tool,
	weapon
};

class BaseItem
{
public:
	BaseItem();

	void setId(QByteArray id) { m_id = id; }
	QByteArray getId() { return m_id; }

	void setName(QString name) { m_name = name; }
	QString getName() { return m_name; }

	void setDescription(QString description) { m_description = description; }
	QString getDescription() { return m_description; }

	void setWearableMode(playerWearable mode) { m_mode = mode; }
	playerWearable getWearableMode() { return m_mode; }

	void setDamage(int damage) { m_damage = damage; }
	int getDamage() { return m_damage; }

	void setType(itemType type) { m_type = type; }
	itemType getType() { return m_type; }

	static playerWearable detectPlayerWearable(QString mode);

private:
	QByteArray m_id;
	QString m_name;
	QString m_description;
	playerWearable m_mode;
	itemType m_type;
	int m_damage;
};

#endif // BASEITEM_H
