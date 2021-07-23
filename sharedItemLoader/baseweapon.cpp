#include "baseweapon.h"

BaseWeapon::BaseWeapon()
{
	setType(itemType::weapon);
	m_mode = weaponMode::noweaponmode;
}

weaponMode BaseWeapon::detectWeaponMode(QString mode)
{
	if (mode == "melee") return weaponMode::melee;
	if (mode == "longRange") return weaponMode::longRange;
	return weaponMode::noweaponmode;
}
