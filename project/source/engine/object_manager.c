#include "object_manager.h"
#include <string.h>
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/scroll_manager.h"
#include "engine/spawn_manager.h"
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
#define NUM_ENEMY_SLOTS 4

GameObject ObjectManager_projectileSlots[NUM_PROJECTILE_SLOTS];
GameObject ObjectManager_enemySlots[NUM_ENEMY_SLOTS];

GameObject* ObjectManager_activeProjectiles[NUM_PROJECTILE_SLOTS];
u8 ObjectManager_activeProjectilesCount;

//GameObject* ObjectManager_activeEnemies[NUM_ENEMY_SLOTS];
//u8 ObjectManager_activeEnemiesCount;

u8 ObjectManager_currentEnemyIndex;

void ObjectManager_Init(void)
{
	memset(ObjectManager_projectileSlots, 0, sizeof(ObjectManager_projectileSlots));
	memset(ObjectManager_enemySlots, 0, sizeof(ObjectManager_enemySlots));

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


void ObjectManager_Update(void)
{
	SMS_setBackdropColor(COLOR_RED);

	ObjectManager_player.Update(&ObjectManager_player);
	ScrollManager_Update(&ObjectManager_player);
	SpawnManager_Update();

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

			if (ObjectManagerUtils_collidesWithProjectiles(enemy)) 
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

		GameObject* enemy = &ObjectManager_enemySlots[ObjectManager_currentEnemyIndex & 3];

		if (!enemy->alive)
			continue;

		if (ObjectManagerUtils_collidesWithProjectiles(enemy)) 
		{
			ObjectManager_DestroyObject(enemy);
		}

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

	ObjectManager_enemySlots[0].Draw(&ObjectManager_enemySlots[0]);
	ObjectManager_enemySlots[1].Draw(&ObjectManager_enemySlots[1]);
	ObjectManager_enemySlots[2].Draw(&ObjectManager_enemySlots[2]);
	ObjectManager_enemySlots[3].Draw(&ObjectManager_enemySlots[3]);
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

	while (counter--)
	{
		if (!objectSlotRunner->alive)
		{
			objectSlotRunner->alive = TRUE;
			//objectSlotRunner->objectId = (NUM_PROJECTILE_SLOTS - 1) - counter;
			return objectSlotRunner;
		}

		objectSlotRunner++;
	}

	return NULL;
}

void ObjectManager_DestroyObject(GameObject* gameObject)
{
	gameObject->Update = ObjectUtils_gameObjectDoNothing;
	gameObject->Draw = ObjectUtils_gameObjectDoNothing;
	gameObject->alive = FALSE;
}

BOOL ObjectManagerUtils_collidesWithProjectiles(GameObject* gameObject)
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
			ObjectManager_DestroyObject(gameObject);
			return TRUE;
		}

		objectSlotRunner++;
	}

	return FALSE;
}