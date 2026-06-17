#include "weapon_manager.h"

#include "base_defines.h"
#include "SMSlib.h"

#include "engine/createinfo_types.h"
#include "engine/object_manager_create.h"

#include "client/generated/gameobjecttemplates/gameobject_templates.h"

s8 fireVerticalXOffset[] = { 5, -5 }; // right, left
s8 fireDuckingYOffset[] = { -4, 3 }; // not ducking, ducking

#define DEFAULT_BULLET_SPEED 4

typedef void (*WeaponManager_FireFunction)(void);

s16 weaponPlayerX;
s16 weaponPlayerY;
u8 weaponPlayerFlipped;
u8 weaponPlayerDucking;

void WeaponManager_FireDefaultUp(void);
void WeaponManager_FireDefaultDown(void);
void WeaponManager_FireDefaultLeft(void);
void WeaponManager_FireDefaultRight(void);

WeaponManager_FireFunction WeaponManager_FireDefaultWeapons[] =
{
	WeaponManager_FireDefaultUp,
	WeaponManager_FireDefaultDown,
	WeaponManager_FireDefaultLeft,
	WeaponManager_FireDefaultRight
};

void WeaponManager_FireShotgunUp(void);
void WeaponManager_FireShotgunDown(void);
void WeaponManager_FireShotgunLeft(void);
void WeaponManager_FireShotgunRight(void);

WeaponManager_FireFunction WeaponManager_FireShotgunWeapons[] =
{
	WeaponManager_FireShotgunUp,
	WeaponManager_FireShotgunDown,
	WeaponManager_FireShotgunLeft,
	WeaponManager_FireShotgunRight
};

WeaponManager_FireFunction* weaponFireFunctions[WEAPON_NUM_WEAPONS] = 
{
	WeaponManager_FireDefaultWeapons,
	WeaponManager_FireShotgunWeapons,
};

u8 WeaponManager_currentWeaponType;
WeaponManager_FireFunction* WeaponManager_weaponFireFunctionsArray;

void WeaponManager_InitGame(void)
{
	//SMS_debugPrintf("Init wepaon manager\n");

	WeaponManager_SwitchWeapon(WEAPON_SHOTGUN);
}

void WeaponManager_InitLevel(void)
{
	// load resources?
}

void WeaponManager_SwitchWeapon(u8 weaponType)
{
	//SMS_debugPrintf("Switch Weapon %d\n", weaponType);
	WeaponManager_currentWeaponType = weaponType;
	WeaponManager_weaponFireFunctionsArray = weaponFireFunctions[WeaponManager_currentWeaponType];
}

void WeaponManager_Fire(s16 playerX, 
						s16 playerY, 
						u8 playerFlipped, 
						u8 playerDucking,
						u8 fireDirection)
{
	weaponPlayerX = playerX;
	weaponPlayerY = playerY;
	weaponPlayerFlipped = playerFlipped;
	weaponPlayerDucking = playerDucking;

	WeaponManager_weaponFireFunctionsArray[fireDirection]();
}



void WeaponManager_FireDefaultUp(void)
{
	CreateInfo createInfo = 
	{ 
		&bullet_template, 
		weaponPlayerX + fireVerticalXOffset[weaponPlayerFlipped],
		weaponPlayerY - 19,
		0,
		-DEFAULT_BULLET_SPEED
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);
}

void WeaponManager_FireDefaultDown(void)
{
	CreateInfo createInfo = 
	{ 
		&bullet_template, 
		weaponPlayerX + fireVerticalXOffset[weaponPlayerFlipped],
		weaponPlayerY + 12,
		0,
		DEFAULT_BULLET_SPEED
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);
}



void WeaponManager_FireDefaultLeft(void)
{
	CreateInfo createInfo = 
	{ 
		&bullet_template, 
		weaponPlayerX - 13,
		weaponPlayerY + fireDuckingYOffset[weaponPlayerDucking],
		-DEFAULT_BULLET_SPEED,
		0
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);
}

void WeaponManager_FireDefaultRight(void)
{
	CreateInfo createInfo = 
	{ 
		&bullet_template, 
		weaponPlayerX + 13,
		weaponPlayerY + fireDuckingYOffset[weaponPlayerDucking],
		DEFAULT_BULLET_SPEED,
		0
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);
}



void WeaponManager_FireShotgunUp(void)
{
	CreateInfo createInfo = 
	{ 
		&shotgun_bullet_template, 
		weaponPlayerX + fireVerticalXOffset[weaponPlayerFlipped],
		weaponPlayerY - 19,
		0,
		-DEFAULT_BULLET_SPEED
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);

	createInfo.startX -= 4;
	createInfo.speedX = -1;
	ObjectManager_CreatePlayerProjectile(&createInfo);


	createInfo.startX += 8;
	createInfo.speedX = 1;
	ObjectManager_CreatePlayerProjectile(&createInfo);
}

void WeaponManager_FireShotgunDown(void)
{
	CreateInfo createInfo = 
	{ 
		&shotgun_bullet_template, 
		weaponPlayerX + fireVerticalXOffset[weaponPlayerFlipped],
		weaponPlayerY + 12,
		0,
		DEFAULT_BULLET_SPEED
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);

	createInfo.startX -= 4;
	createInfo.speedX = -1;
	ObjectManager_CreatePlayerProjectile(&createInfo);

	createInfo.startX += 8;
	createInfo.speedX = 1;
	ObjectManager_CreatePlayerProjectile(&createInfo);
}



void WeaponManager_FireShotgunLeft(void)
{
	CreateInfo createInfo = 
	{ 
		&shotgun_bullet_template, 
		weaponPlayerX - 13,
		weaponPlayerY + fireDuckingYOffset[weaponPlayerDucking],
		-DEFAULT_BULLET_SPEED,
		0
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);

	createInfo.startY -= 4;
	createInfo.speedY = -1;
	ObjectManager_CreatePlayerProjectile(&createInfo);

	createInfo.startY += 8;
	createInfo.speedY = 1;
	ObjectManager_CreatePlayerProjectile(&createInfo);
}

void WeaponManager_FireShotgunRight(void)
{
	CreateInfo createInfo = 
	{ 
		&shotgun_bullet_template, 
		weaponPlayerX + 13,
		weaponPlayerY + fireDuckingYOffset[weaponPlayerDucking],
		DEFAULT_BULLET_SPEED,
		0
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);

	createInfo.startY -= 4;
	createInfo.speedY = -1;
	ObjectManager_CreatePlayerProjectile(&createInfo);
	
	createInfo.startY += 8;
	createInfo.speedY = 1;
	ObjectManager_CreatePlayerProjectile(&createInfo);
}

/*
void WeaponManager_FireShotgun(s16 x, s16 y, u8 flipped)
{
	//SMS_debugPrintf("Shotgun");
	CreateInfo createInfo = 
	{ 
		&shotgun_bullet_template, 
		x,
		y
	};

	GameObject* shotgun = ObjectManager_CreatePlayerProjectile(&createInfo);

	shotgun->speedX = flipped ? -4 : 4;
	shotgun->speedY = 0;

	createInfo.startY -= 4;
	shotgun = ObjectManager_CreatePlayerProjectile(&createInfo);
	shotgun->speedX = flipped ? -4 : 4;
	shotgun->speedY = -1;

	createInfo.startY += 8;
	shotgun = ObjectManager_CreatePlayerProjectile(&createInfo);
	shotgun->speedX = flipped ? -4 : 4;
	shotgun->speedY = 1;
}


void WeaponManager_FireShotgunVertical(s16 x, s16 y, u8 flipped)
{
	//SMS_debugPrintf("Shotgun");
	CreateInfo createInfo = 
	{ 
		&shotgun_bullet_template, 
		x,
		y
	};

	GameObject* shotgun = ObjectManager_CreatePlayerProjectile(&createInfo);

	shotgun->speedX = 0;
	shotgun->speedY = flipped ? 4 : -4;

	createInfo.startX -= 4;
	shotgun = ObjectManager_CreatePlayerProjectile(&createInfo);
	shotgun->speedX = -1;
	shotgun->speedY = flipped ? 4 : -4;

	createInfo.startX += 8;
	shotgun = ObjectManager_CreatePlayerProjectile(&createInfo);
	shotgun->speedX = 1;
	shotgun->speedY = flipped ? 4 : -4;
}

*/