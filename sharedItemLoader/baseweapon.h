#ifndef BASEWEAPON_H
#define BASEWEAPON_H

#include "baseitem.h"

enum weaponMode {
	noweaponmode,
	melee,
	longRange
};

class BaseWeapon : public BaseItem
{
public:
	BaseWeapon();

	void setWeaponMode(weaponMode mode) { m_mode = mode; }
	weaponMode getWeaponMode() { return m_mode; }

	static weaponMode detectWeaponMode(QString mode);

private:
	weaponMode m_mode;
};

#endif // BASEWEAPON_H
