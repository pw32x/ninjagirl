#include "weapon_manager.h"

#include "SMSlib.h"

#include "engine/createinfo_types.h"
#include "engine/object_manager.h"

#include "client/generated/gameobjecttemplates/gameobject_templates.h"


u8 WeaponManager_currentWeaponType;

WeaponManager_FireFunction WeaponManager_FireWeapon;
WeaponManager_FireUpFunction WeaponManager_FireWeaponUp;

WeaponManager_FireFunction weaponFunctions[WEAPON_NUM_WEAPONS];
WeaponManager_FireUpFunction weaponUpFunctions[WEAPON_NUM_WEAPONS];

void WeaponManager_FireDefault(s16 x, s16 y, u8 flipped);
void WeaponManager_FireDefaultUp(s16 x, s16 y);

void WeaponManager_FireShotgun(s16 x, s16 y, u8 flipped);
void WeaponManager_FireShotgunUp(s16 x, s16 y);


void WeaponManager_InitGame(void)
{
	//SMS_debugPrintf("Init wepaon manager\n");

	weaponFunctions[WEAPON_DEFAULT] = WeaponManager_FireDefault;
	weaponFunctions[WEAPON_SHOTGUN] = WeaponManager_FireShotgun;

	weaponUpFunctions[WEAPON_DEFAULT] = WeaponManager_FireDefaultUp;
	weaponUpFunctions[WEAPON_SHOTGUN] = WeaponManager_FireShotgunUp;

	WeaponManager_SwitchWeapon(WEAPON_DEFAULT);
}

void WeaponManager_InitLevel(void)
{
	// load resources?
}

void WeaponManager_SwitchWeapon(u8 weaponType)
{
	//SMS_debugPrintf("Switch Weapon %d\n", weaponType);
	WeaponManager_currentWeaponType = weaponType;
	WeaponManager_FireWeapon = weaponFunctions[weaponType];
	WeaponManager_FireWeaponUp = weaponUpFunctions[weaponType];
}

void WeaponManager_FireDefault(s16 x, s16 y, u8 flipped)
{
	//SMS_debugPrintf("Default");
	CreateInfo createInfo = 
	{ 
		&bullet_template, 
		x,
		y
	};

	GameObject* bullet = ObjectManager_CreateObjectByCreateInfo(&createInfo);

	bullet->speedx = flipped ? -4 : 4;
	bullet->speedy = 0;

}


void WeaponManager_FireDefaultUp(s16 x, s16 y)
{
	//SMS_debugPrintf("Default");
	CreateInfo createInfo = 
	{ 
		&bullet_template, 
		x,
		y
	};

	GameObject* bullet = ObjectManager_CreateObjectByCreateInfo(&createInfo);

	bullet->speedx = 0;
	bullet->speedy = -4;

}

void WeaponManager_FireShotgun(s16 x, s16 y, u8 flipped)
{
	//SMS_debugPrintf("Shotgun");
	CreateInfo createInfo = 
	{ 
		&shotgun_template, 
		x,
		y
	};

	GameObject* shotgun = ObjectManager_CreateObjectByCreateInfo(&createInfo);

	shotgun->speedx = flipped ? -3 : 3;
	shotgun->speedy = 0;

	shotgun = ObjectManager_CreateObjectByCreateInfo(&createInfo);
	shotgun->speedx = flipped ? -3 : 3;
	shotgun->speedy = -1;

	shotgun = ObjectManager_CreateObjectByCreateInfo(&createInfo);
	shotgun->speedx = flipped ? -3 : 3;
	shotgun->speedy = 1;
}


void WeaponManager_FireShotgunUp(s16 x, s16 y)
{
	//SMS_debugPrintf("Shotgun");
	CreateInfo createInfo = 
	{ 
		&shotgun_template, 
		x,
		y
	};

	GameObject* shotgun = ObjectManager_CreateObjectByCreateInfo(&createInfo);

	shotgun->speedx = 0;
	shotgun->speedy = -3;

	shotgun = ObjectManager_CreateObjectByCreateInfo(&createInfo);
	shotgun->speedx = -1;
	shotgun->speedy = -3;

	shotgun = ObjectManager_CreateObjectByCreateInfo(&createInfo);
	shotgun->speedx = 1;
	shotgun->speedy = -3;
}
