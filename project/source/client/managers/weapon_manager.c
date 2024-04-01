#include "weapon_manager.h"

#include "SMSlib.h"

#include "engine/createinfo_types.h"
#include "engine/object_manager_create.h"

#include "client/generated/gameobjecttemplates/gameobject_templates.h"


u8 WeaponManager_currentWeaponType;

WeaponManager_FireFunction WeaponManager_FireWeapon;
WeaponManager_FireFunction WeaponManager_FireWeaponVertical;

WeaponManager_FireFunction weaponFunctions[WEAPON_NUM_WEAPONS];
WeaponManager_FireFunction weaponVerticalFunctions[WEAPON_NUM_WEAPONS];

void WeaponManager_FireDefault(s16 x, s16 y, u8 flipped);
void WeaponManager_FireDefaultVertical(s16 x, s16 y, u8 flipped);

void WeaponManager_FireShotgun(s16 x, s16 y, u8 flipped);
void WeaponManager_FireShotgunVertical(s16 x, s16 y, u8 flipped);


void WeaponManager_InitGame(void)
{
	//SMS_debugPrintf("Init wepaon manager\n");

	weaponFunctions[WEAPON_DEFAULT] = WeaponManager_FireDefault;
	weaponFunctions[WEAPON_SHOTGUN] = WeaponManager_FireShotgun;

	weaponVerticalFunctions[WEAPON_DEFAULT] = WeaponManager_FireDefaultVertical;
	weaponVerticalFunctions[WEAPON_SHOTGUN] = WeaponManager_FireShotgunVertical;

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
	WeaponManager_FireWeaponVertical = weaponVerticalFunctions[weaponType];
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


void WeaponManager_FireDefaultVertical(s16 x, s16 y, u8 flipped)
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
	bullet->speedy = flipped ? 4 : -4;

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

	shotgun->speedx = flipped ? -4 : 4;
	shotgun->speedy = 0;

	createInfo.startY -= 4;
	shotgun = ObjectManager_CreateObjectByCreateInfo(&createInfo);
	shotgun->speedx = flipped ? -4 : 4;
	shotgun->speedy = -1;

	createInfo.startY += 8;
	shotgun = ObjectManager_CreateObjectByCreateInfo(&createInfo);
	shotgun->speedx = flipped ? -4 : 4;
	shotgun->speedy = 1;
}


void WeaponManager_FireShotgunVertical(s16 x, s16 y, u8 flipped)
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
	shotgun->speedy = flipped ? 4 : -4;

	createInfo.startX -= 4;
	shotgun = ObjectManager_CreateObjectByCreateInfo(&createInfo);
	shotgun->speedx = -1;
	shotgun->speedy = flipped ? 4 : -4;

	createInfo.startX += 8;
	shotgun = ObjectManager_CreateObjectByCreateInfo(&createInfo);
	shotgun->speedx = 1;
	shotgun->speedy = flipped ? 4 : -4;
}

