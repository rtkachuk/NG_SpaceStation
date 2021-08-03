#ifndef BASEITEM_H
#define BASEITEM_H

#include <QByteArray>
#include <QString>

enum playerWearable {
	itemnomode,
	head,
	torso,
	legs,
	feet,
	holdable,
	gloves
};

enum itemType {
	notype,
	tool,
	weapon,
	furniture,
	material
};

enum toolMode {
	toolnomode,
	screwing,
	hammering,
	cutting,
	heating,
	welding,
	wrenching
};

enum weaponMode {
	noweaponmode,
	melee,
	longRange
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

	void setWearableMode(playerWearable mode) { m_wMode = mode; }
	playerWearable getWearableMode() { return m_wMode; }

	void setDamage(int damage) { m_damage = damage; }
	int getDamage() { return m_damage; }

	void setType(itemType type) { m_type = type; }
	itemType getType() { return m_type; }

	void setPixmap(QString path) { m_pixmap = path; }
	QString getPixmap() { return m_pixmap; }

	static playerWearable detectPlayerWearable(QString mode);

	void setToolMode (toolMode mode) { m_tMode = mode; }
	toolMode getToolMode() { return m_tMode; }

	static toolMode detectToolMode(QString mode);

	void setWeaponMode(weaponMode mode) { m_weapMode = mode; }
	weaponMode getWeaponMode() { return m_weapMode; }

	static weaponMode detectWeaponMode(QString mode);

private:
	QByteArray m_id;
	QString m_name;
	QString m_description;
	QString m_pixmap;
	playerWearable m_wMode;
	toolMode m_tMode;
	weaponMode m_weapMode;
	itemType m_type;
	int m_damage;
};

#endif // BASEITEM_H
