#include "weapon_manager.h"

#include "base_defines.h"
#include "SMSlib.h"

#include "engine/createinfo_types.h"
#include "engine/object_manager_create.h"

#include "client/generated/gameobjecttemplates/gameobject_templates.h"

s8 fireVerticalXOffset[] = { P2V(5), P2V(-5) }; // right, left
s8 fireDuckingYOffset[] = { P2V(-4), P2V(3) }; // not ducking, ducking

#define DEFAULT_BULLET_SPEED P2V(4)

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

	//SMS_debugPrintf("player: %d %d\n", playerX, playerY);	

	weaponPlayerFlipped = playerFlipped;
	weaponPlayerDucking = playerDucking;

	WeaponManager_weaponFireFunctionsArray[fireDirection]();
}



void WeaponManager_FireDefaultUp(void)
{
	CreateInfoEx createInfo = 
	{ 
		&bullet_template, 
		weaponPlayerX + fireVerticalXOffset[weaponPlayerFlipped],
		weaponPlayerY - P2V(19),
		0,
		-DEFAULT_BULLET_SPEED
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);
}

void WeaponManager_FireDefaultDown(void)
{
	CreateInfoEx createInfo = 
	{ 
		&bullet_template, 
		weaponPlayerX + fireVerticalXOffset[weaponPlayerFlipped],
		weaponPlayerY + P2V(12),
		0,
		DEFAULT_BULLET_SPEED
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);
}



void WeaponManager_FireDefaultLeft(void)
{
	CreateInfoEx createInfo = 
	{ 
		&bullet_template, 
		weaponPlayerX - P2V(13),
		weaponPlayerY + fireDuckingYOffset[weaponPlayerDucking],
		-DEFAULT_BULLET_SPEED,
		0
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);
}

void WeaponManager_FireDefaultRight(void)
{
	CreateInfoEx createInfo = 
	{ 
		&bullet_template, 
		weaponPlayerX + P2V(13),
		weaponPlayerY + fireDuckingYOffset[weaponPlayerDucking],
		DEFAULT_BULLET_SPEED,
		0
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);
}



void WeaponManager_FireShotgunUp(void)
{
	CreateInfoEx createInfo = 
	{ 
		&shotgun_bullet_template, 
		weaponPlayerX + fireVerticalXOffset[weaponPlayerFlipped],
		weaponPlayerY - P2V(19),
		0,
		-DEFAULT_BULLET_SPEED
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);

	createInfo.startX -= P2V(4);
	createInfo.speedX = P2V(-1);
	ObjectManager_CreatePlayerProjectile(&createInfo);


	createInfo.startX += P2V(8);
	createInfo.speedX = P2V(1);
	ObjectManager_CreatePlayerProjectile(&createInfo);
}

void WeaponManager_FireShotgunDown(void)
{
	CreateInfoEx createInfo = 
	{ 
		&shotgun_bullet_template, 
		weaponPlayerX + fireVerticalXOffset[weaponPlayerFlipped],
		weaponPlayerY + P2V(12),
		0,
		DEFAULT_BULLET_SPEED
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);

	createInfo.startX -= P2V(4);
	createInfo.speedX = P2V(-1);
	ObjectManager_CreatePlayerProjectile(&createInfo);

	createInfo.startX += P2V(8);
	createInfo.speedX = P2V(1);
	ObjectManager_CreatePlayerProjectile(&createInfo);
}



void WeaponManager_FireShotgunLeft(void)
{
	CreateInfoEx createInfo = 
	{ 
		&shotgun_bullet_template, 
		weaponPlayerX - P2V(13),
		weaponPlayerY + fireDuckingYOffset[weaponPlayerDucking],
		-DEFAULT_BULLET_SPEED,
		0
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);

	createInfo.startY -= P2V(4);
	createInfo.speedY = P2V(-1);
	ObjectManager_CreatePlayerProjectile(&createInfo);

	createInfo.startY += P2V(8);
	createInfo.speedY = P2V(1);
	ObjectManager_CreatePlayerProjectile(&createInfo);
}

void WeaponManager_FireShotgunRight(void)
{
	CreateInfoEx createInfo = 
	{ 
		&shotgun_bullet_template, 
		weaponPlayerX + P2V(13),
		weaponPlayerY + fireDuckingYOffset[weaponPlayerDucking],
		DEFAULT_BULLET_SPEED,
		0
	};

	ObjectManager_CreatePlayerProjectile(&createInfo);

	createInfo.startY -= P2V(4);
	createInfo.speedY = P2V(-1);
	ObjectManager_CreatePlayerProjectile(&createInfo);
	
	createInfo.startY += P2V(8);
	createInfo.speedY = P2V(1);
	ObjectManager_CreatePlayerProjectile(&createInfo);
}
