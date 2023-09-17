#include "object_manager.h"
#include <string.h>
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/scroll_manager.h"
#include "engine/command_manager.h"
#include "engine/object_utils.h"
#include "engine/draw_utils.h"

GameObject ObjectManager_player;

//s16 ObjectManager_objectLeft;
//s16 ObjectManager_objectTop;
//s16 ObjectManager_objectRight;
//s16 ObjectManager_objectBottom;

//s16 ObjectManager_playerLeft;
//s16 ObjectManager_playerTop;
//s16 ObjectManager_playerRight;
//s16 ObjectManager_playerBottom;


#define NUM_PROJECTILE_SLOTS 3
#define NUM_ENEMY_SLOTS 8
#define NUM_EFFECT_SLOTS 8

GameObject ObjectManager_projectileSlots[NUM_PROJECTILE_SLOTS];
GameObject ObjectManager_enemySlots[NUM_ENEMY_SLOTS];
GameObject ObjectManager_effectSlots[NUM_EFFECT_SLOTS];


GameObject* ObjectManager_activeProjectiles[NUM_PROJECTILE_SLOTS];
u8 ObjectManager_activeProjectilesCount;

//GameObject* ObjectManager_activeEnemies[NUM_ENEMY_SLOTS];
//u8 ObjectManager_activeEnemiesCount;

u8 ObjectManager_currentEnemyIndex;

#define NUM_VDP_DRAW_ITEMS 8
GameObject* ObjectManager_vdpDrawGameObjects[NUM_VDP_DRAW_ITEMS];
ObjectFunctionType ObjectManager_vdpDrawFunctions[NUM_VDP_DRAW_ITEMS];
u8 ObjectManager_numVdpDrawItems;

BOOL ObjectManagerUtils_doProjectCollisionCheck(GameObject* gameObject);

//u8 ObjectManager_enemyIndex;
//u8 ObjectManager_enemyCounter;
//u8 ObjectManager_oldEnemyCounter;
//
//u8 ObjectManager_oldProjectileDrawCounter;

void ObjectManager_Init(void)
{
	//ObjectManager_enemyIndex = 0;
	//ObjectManager_oldProjectileDrawCounter = 0;

	memset(ObjectManager_projectileSlots, 0, sizeof(ObjectManager_projectileSlots));
	memset(ObjectManager_enemySlots, 0, sizeof(ObjectManager_enemySlots));
	memset(ObjectManager_effectSlots, 0,sizeof(ObjectManager_effectSlots));

	// setup objects
	GameObject* objectSlotRunner = ObjectManager_projectileSlots;
	u8 counter = NUM_PROJECTILE_SLOTS;

	while (counter--)
	{
		ObjectManager_DestroyObject(objectSlotRunner);
		objectSlotRunner++;
	}

	objectSlotRunner = ObjectManager_enemySlots;
	counter = NUM_ENEMY_SLOTS;

	while (counter--)
	{
		ObjectManager_DestroyObject(objectSlotRunner);
		objectSlotRunner++;
	}

	ObjectManager_currentEnemyIndex = 0;

	objectSlotRunner = ObjectManager_effectSlots;
	counter = NUM_EFFECT_SLOTS;

	while (counter--)
	{
		ObjectManager_DestroyObject(objectSlotRunner);
		objectSlotRunner++;
	}
}

//void ObjectManagerUtils_updatePlayerScreenRect(void)
//{
//	ObjectManager_playerLeft = ObjectManager_player.x - ScrollManager_horizontalScroll;
//	ObjectManager_playerTop = ObjectManager_player.y;
//	ObjectManager_playerRight = ObjectManager_playerLeft + ObjectManager_player.pixelWidth;
//	ObjectManager_playerBottom = ObjectManager_playerTop + ObjectManager_player.pixelHeight;
//}
//

//void ObjectManagerUtils_updateObjectScreenRect(GameObject* gameObject)
//{
//	ObjectManager_objectLeft = gameObject->x - ScrollManager_horizontalScroll;
//	ObjectManager_objectTop = gameObject->y;
//	ObjectManager_objectRight = ObjectManager_objectLeft + gameObject->pixelWidth;
//	ObjectManager_objectBottom = ObjectManager_objectTop + gameObject->pixelHeight;
//}

u8 projectileFlicker = 0;

void ObjectManager_Update(void)
{
	ObjectManager_numVdpDrawItems = 0;

	SMS_setBackdropColor(COLOR_RED);

	ObjectManager_player.Update(&ObjectManager_player);
	ScrollManager_Update(&ObjectManager_player);
	CommandManager_Update();

	//ObjectManagerUtils_updatePlayerScreenRect();

	SMS_setBackdropColor(COLOR_ORANGE);

	// update objects

	/*
	GameObject* objectSlotRunner = ObjectManager_projectileSlots;
	u8 counter = NUM_PROJECTILE_SLOTS;

	ObjectManager_activeProjectilesCount = 0;

	while (counter--)
	{
		if (objectSlotRunner->alive)
		{
			objectSlotRunner->Update(objectSlotRunner);

			if (objectSlotRunner->alive)
			{
				ObjectManager_activeProjectiles[ObjectManager_activeProjectilesCount] = objectSlotRunner;
				ObjectManager_activeProjectilesCount++;
			}
		}
		objectSlotRunner++;
	}
	*/

	ObjectManager_projectileSlots[0].Update(&ObjectManager_projectileSlots[0]);
	ObjectManager_projectileSlots[1].Update(&ObjectManager_projectileSlots[1]);
	ObjectManager_projectileSlots[2].Update(&ObjectManager_projectileSlots[2]);

	SMS_setBackdropColor(COLOR_DARK_BLUE);

	/*
	if (ObjectManager_activeProjectilesCount && ObjectManager_activeEnemiesCount)
	{
		counter = NUM_ENEMY_SLOTS;

		while (counter--)
		{
			++ObjectManager_currentEnemyIndex;

			GameObject* enemy = ObjectManager_activeEnemies[ObjectManager_currentEnemyIndex & 3];

			if (!enemy->alive)
				continue;

			if (ObjectManagerUtils_doProjectCollisionCheck(enemy)) 
			{
				ObjectManager_DestroyObject(enemy);
			}

			break;
		}
	}
	*/

	u8 counter = NUM_ENEMY_SLOTS;

	while (counter--)
	{
		++ObjectManager_currentEnemyIndex;

		GameObject* enemy = &ObjectManager_enemySlots[ObjectManager_currentEnemyIndex & 7];

		if (!enemy->alive)
			continue;

		ObjectManagerUtils_doProjectCollisionCheck(enemy);

		break;
	}



	SMS_setBackdropColor(COLOR_ORANGE);

	//objectSlotRunner = ObjectManager_enemySlots;
	//counter = NUM_ENEMY_SLOTS;

	/*
	ObjectManager_activeEnemiesCount = 0;

	while (counter--)
	{
		if (objectSlotRunner->alive)
		{
			objectSlotRunner->Update(objectSlotRunner);

			if (objectSlotRunner->alive)
			{
				ObjectManager_activeEnemies[ObjectManager_activeEnemiesCount] = objectSlotRunner;
				ObjectManager_activeEnemiesCount++;
			}
		}
		objectSlotRunner++;
	}
	*/

	ObjectManager_enemySlots[0].Update(&ObjectManager_enemySlots[0]);
	ObjectManager_enemySlots[1].Update(&ObjectManager_enemySlots[1]);
	ObjectManager_enemySlots[2].Update(&ObjectManager_enemySlots[2]);
	ObjectManager_enemySlots[3].Update(&ObjectManager_enemySlots[3]);
	ObjectManager_enemySlots[4].Update(&ObjectManager_enemySlots[4]);
	ObjectManager_enemySlots[5].Update(&ObjectManager_enemySlots[5]);
	ObjectManager_enemySlots[6].Update(&ObjectManager_enemySlots[6]);
	ObjectManager_enemySlots[7].Update(&ObjectManager_enemySlots[7]);


	

	ObjectManager_effectSlots[0].Update(&ObjectManager_effectSlots[0]);
	ObjectManager_effectSlots[1].Update(&ObjectManager_effectSlots[1]);
	ObjectManager_effectSlots[2].Update(&ObjectManager_effectSlots[2]);
	ObjectManager_effectSlots[3].Update(&ObjectManager_effectSlots[3]);
	ObjectManager_effectSlots[4].Update(&ObjectManager_effectSlots[4]);
	ObjectManager_effectSlots[5].Update(&ObjectManager_effectSlots[5]);
	ObjectManager_effectSlots[6].Update(&ObjectManager_effectSlots[6]);
	ObjectManager_effectSlots[7].Update(&ObjectManager_effectSlots[7]);

	SMS_setBackdropColor(COLOR_YELLOW);
	SMS_initSprites();

	DrawUtils_spritesDrawn = 0;

	ObjectManager_player.Draw(&ObjectManager_player);

	SMS_setBackdropColor(COLOR_GRAY);

	/*
	GameObject** activeObjectRunner = ObjectManager_activeProjectiles;
	counter = ObjectManager_activeProjectilesCount;
	while (counter--)
	{
		(*activeObjectRunner)->Draw(*activeObjectRunner);
		activeObjectRunner++;
	}
	*/

	ObjectManager_projectileSlots[0].Draw(&ObjectManager_projectileSlots[0]);
	ObjectManager_projectileSlots[1].Draw(&ObjectManager_projectileSlots[1]);
	ObjectManager_projectileSlots[2].Draw(&ObjectManager_projectileSlots[2]);

	SMS_setBackdropColor(COLOR_PINK);
	/*
	activeObjectRunner = ObjectManager_activeEnemies;
	counter = ObjectManager_activeEnemiesCount;
	while (counter--)
	{
		(*activeObjectRunner)->Draw(*activeObjectRunner);
		activeObjectRunner++;
	}
	*/

	ObjectManager_effectSlots[0].Draw(&ObjectManager_effectSlots[0]);
	ObjectManager_effectSlots[1].Draw(&ObjectManager_effectSlots[1]);
	ObjectManager_effectSlots[2].Draw(&ObjectManager_effectSlots[2]);
	ObjectManager_effectSlots[3].Draw(&ObjectManager_effectSlots[3]);
	ObjectManager_effectSlots[4].Draw(&ObjectManager_effectSlots[4]);
	ObjectManager_effectSlots[5].Draw(&ObjectManager_effectSlots[5]);
	ObjectManager_effectSlots[6].Draw(&ObjectManager_effectSlots[6]);
	ObjectManager_effectSlots[7].Draw(&ObjectManager_effectSlots[7]);

	/*

	//ObjectManager_enemyCounter = NUM_ENEMY_SLOTS - 1;
	//while (ObjectManager_enemyCounter--)
	//{
	//	GameObject* object = &ObjectManager_enemySlots[counter];
	//	object->Draw(object);
	//}

	if (drawCounter && ObjectManager_oldProjectileDrawCounter)
	{
		ObjectManager_enemyCounter = ObjectManager_oldEnemyCounter;
	}

	ObjectManager_oldProjectileDrawCounter = drawCounter;

	if (drawCounter > 1)
	{
		ObjectManager_enemyCounter = (++ObjectManager_enemyCounter) & 7; // increase and wrap
	}
	else
	{
		ObjectManager_oldEnemyCounter = ObjectManager_enemyCounter;
		ObjectManager_enemyCounter = NUM_ENEMY_SLOTS;
	}
	*/

	ObjectManager_enemySlots[0].Draw(&ObjectManager_enemySlots[0]);
	ObjectManager_enemySlots[1].Draw(&ObjectManager_enemySlots[1]);
	ObjectManager_enemySlots[2].Draw(&ObjectManager_enemySlots[2]);
	ObjectManager_enemySlots[3].Draw(&ObjectManager_enemySlots[3]);
	ObjectManager_enemySlots[4].Draw(&ObjectManager_enemySlots[4]);
	ObjectManager_enemySlots[5].Draw(&ObjectManager_enemySlots[5]);
	ObjectManager_enemySlots[6].Draw(&ObjectManager_enemySlots[6]);
	ObjectManager_enemySlots[7].Draw(&ObjectManager_enemySlots[7]);
}

GameObject* ObjectManager_GetAvailableSlot(u8 objectType)
{
	GameObject* objectSlotRunner = ObjectManager_enemySlots;
	u8 counter = NUM_ENEMY_SLOTS;

	if (objectType == OBJECTTYPE_PROJECTILE)
	{
		objectSlotRunner = ObjectManager_projectileSlots;
		counter = NUM_PROJECTILE_SLOTS;	
	}
	else if (objectType == OBJECTTYPE_EFFECT)
	{
		objectSlotRunner = ObjectManager_effectSlots;
		counter = NUM_EFFECT_SLOTS;
	}

	while (counter--)
	{
		if (!objectSlotRunner->alive)
		{
			objectSlotRunner->alive = TRUE;
			return objectSlotRunner;
		}

		objectSlotRunner++;
	}

	return NULL;
}

void ObjectManager_DestroyObject(GameObject* gameObject)
{
	gameObject->Update = ObjectUtils_gameObjectDoNothing;
	gameObject->Draw = ObjectUtils_drawNothing;
	gameObject->alive = FALSE;
}

BOOL ObjectManagerUtils_doProjectCollisionCheck(GameObject* gameObject)
{
	GameObject* objectSlotRunner = ObjectManager_projectileSlots;
	u8 counter = NUM_PROJECTILE_SLOTS;

	s16 left = gameObject->x + gameObject->rectLeft;
	s16 top = gameObject->y + gameObject->rectTop;
	s16 right = gameObject->x + gameObject->rectRight;
	s16 bottom = gameObject->y + gameObject->rectBottom;

	while (counter--)
	{
		if (objectSlotRunner->alive &&
			left < objectSlotRunner->x + objectSlotRunner->rectRight &&
			right > objectSlotRunner->x + objectSlotRunner->rectLeft &&
			top < objectSlotRunner->y + objectSlotRunner->rectBottom &&
			bottom > objectSlotRunner->y + objectSlotRunner->rectTop
			)
		{
			objectSlotRunner->HandleCollision(objectSlotRunner, gameObject);
			return TRUE;
		}

		objectSlotRunner++;
	}

	return FALSE;
}



void ObjectManager_QueueVDPDraw(GameObject* gameObject, ObjectFunctionType vdpDrawFunction)
{
	ObjectManager_vdpDrawGameObjects[ObjectManager_numVdpDrawItems] = gameObject;
	ObjectManager_vdpDrawFunctions[ObjectManager_numVdpDrawItems] = vdpDrawFunction;

	ObjectManager_numVdpDrawItems++;
}

void ObjectManager_VDPDraw(void)
{
	if (!ObjectManager_numVdpDrawItems)
		return;

	GameObject** gameObjectsRunner = ObjectManager_vdpDrawGameObjects;
	ObjectFunctionType* vdpDrawFunctionsRunner = ObjectManager_vdpDrawFunctions;

	while (ObjectManager_numVdpDrawItems--)
	{
		(*vdpDrawFunctionsRunner)(*gameObjectsRunner);

		gameObjectsRunner++;
		vdpDrawFunctionsRunner++;
	}
}