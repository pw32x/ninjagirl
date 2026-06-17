#ifndef WEAPON_MANAGER_INCLUDE_H
#define WEAPON_MANAGER_INCLUDE_H

#include "engine/base_types.h"

#define WEAPON_DEFAULT		0
#define WEAPON_SHOTGUN		1
#define WEAPON_NUM_WEAPONS	2

#define FIRE_UPWARDS	0
#define FIRE_DOWNWARDS	1
#define FIRE_LEFT		2
#define FIRE_RIGHT		3

void WeaponManager_InitGame(void);
void WeaponManager_SwitchWeapon(u8 weaponType);
void WeaponManager_Fire(s16 playerX, s16 playerY, u8 playerFlipped, u8 playerDucking, u8 fireDirection);


#endif