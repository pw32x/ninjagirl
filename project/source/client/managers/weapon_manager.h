#ifndef WEAPON_MANAGER_INCLUDE_H
#define WEAPON_MANAGER_INCLUDE_H

#include "engine/base_types.h"

#define WEAPON_DEFAULT		0
#define WEAPON_SHOTGUN		1
#define WEAPON_NUM_WEAPONS	2


typedef void (*WeaponManager_FireFunction)(s16 x, s16 y, u8 flipped);

void WeaponManager_SwitchWeapon(u8 weaponType);
extern WeaponManager_FireFunction WeaponManager_FireWeapon;
extern WeaponManager_FireFunction WeaponManager_FireWeaponVertical;

#endif