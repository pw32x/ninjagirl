#include "object_manager.h"
#include <string.h>
#include "SMSlib.h"

#include "engine/object_manager_create.h"
#include "engine/object_manager_vdp.h"
#include "engine/object_manager_slots.h"
#include "engine/base_defines.h"
#include "engine/scroll_manager.h"
#include "engine/command_manager.h"
//#include "engine/resource_manager.h"
//#include "engine/object_utils.h"
//#include "engine/draw_utils.h"

GameObject* objectSlotRunner;

//GameObject* ObjectManager_activeProjectiles[NUM_PROJECTILE_SLOTS];
//u8 ObjectManager_activeProjectilesCount;


//u8 ObjectManager_currentEnemyIndex;


BOOL ObjectManagerUtils_doProjectCollisionCheck(GameObject* gameObject);

void ObjectManager_Init(void)
{
	ObjectManager_InitCreate();
	ObjectManager_InitSlots();
}

u8 drawOrderToggle = FALSE;

void ObjectManager_Update(void)
{
	ObjectManager_numVdpDrawItems = 0;

	//SMS_setBackdropColor(COLOR_RED);

	ObjectManager_player.Update(&ObjectManager_player);
	
	ScrollManager_Update(&ObjectManager_player);


	//ObjectManagerUtils_updatePlayerScreenRect();



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

	/*
	ObjectManager_enemyProjectileSlots[0].Update(&ObjectManager_enemyProjectileSlots[0]);
	ObjectManager_enemyProjectileSlots[1].Update(&ObjectManager_enemyProjectileSlots[1]);
	ObjectManager_enemyProjectileSlots[2].Update(&ObjectManager_enemyProjectileSlots[2]);
	*/
	switch (ObjectManager_numEnemies)
	{
	case 8: ObjectManagerUtils_doProjectCollisionCheck(&ObjectManager_enemySlots[7]);
	case 7: ObjectManagerUtils_doProjectCollisionCheck(&ObjectManager_enemySlots[6]);
	case 6: ObjectManagerUtils_doProjectCollisionCheck(&ObjectManager_enemySlots[5]);
	case 5: ObjectManagerUtils_doProjectCollisionCheck(&ObjectManager_enemySlots[4]);
	case 4: ObjectManagerUtils_doProjectCollisionCheck(&ObjectManager_enemySlots[3]);
	case 3: ObjectManagerUtils_doProjectCollisionCheck(&ObjectManager_enemySlots[2]);
	case 2: ObjectManagerUtils_doProjectCollisionCheck(&ObjectManager_enemySlots[1]);
	case 1: ObjectManagerUtils_doProjectCollisionCheck(&ObjectManager_enemySlots[0]);
	}



	/*
	// perform collisions against projectiles
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
	*/

	// add new objects and enemies only after we've done the collision checks for the currently 
	// active ones.
	CommandManager_commandRunnerObject.Update(&CommandManager_commandRunnerObject);

	//SMS_setBackdropColor(COLOR_ORANGE);

	switch (ObjectManager_numEnemies)
	{
	case 8: ObjectManager_enemySlots[7].Update(&ObjectManager_enemySlots[7]);
	case 7: ObjectManager_enemySlots[6].Update(&ObjectManager_enemySlots[6]);
	case 6: ObjectManager_enemySlots[5].Update(&ObjectManager_enemySlots[5]);
	case 5: ObjectManager_enemySlots[4].Update(&ObjectManager_enemySlots[4]);
	case 4: ObjectManager_enemySlots[3].Update(&ObjectManager_enemySlots[3]);
	case 3: ObjectManager_enemySlots[2].Update(&ObjectManager_enemySlots[2]);
	case 2: ObjectManager_enemySlots[1].Update(&ObjectManager_enemySlots[1]);
	case 1: ObjectManager_enemySlots[0].Update(&ObjectManager_enemySlots[0]);
	}

	switch (ObjectManager_numEffects)
	{
	case 8: ObjectManager_effectSlots[7].Update(&ObjectManager_effectSlots[7]);
	case 7: ObjectManager_effectSlots[6].Update(&ObjectManager_effectSlots[6]);
	case 6: ObjectManager_effectSlots[5].Update(&ObjectManager_effectSlots[5]);
	case 5: ObjectManager_effectSlots[4].Update(&ObjectManager_effectSlots[4]);
	case 4: ObjectManager_effectSlots[3].Update(&ObjectManager_effectSlots[3]);
	case 3: ObjectManager_effectSlots[2].Update(&ObjectManager_effectSlots[2]);
	case 2: ObjectManager_effectSlots[1].Update(&ObjectManager_effectSlots[1]);
	case 1: ObjectManager_effectSlots[0].Update(&ObjectManager_effectSlots[0]);
	}

	/*
	ObjectManager_Item.Update(&ObjectManager_Item);
	*/

	ObjectManager_player.screenx = ObjectManager_player.x - ScrollManager_horizontalScroll;
	ObjectManager_player.screeny = ObjectManager_player.y;

	/*
	if (ObjectManager_Item.alive)
	{
	s16 left = ObjectManager_player.screenx + ObjectManager_player.rectLeft;
	s16 top = ObjectManager_player.screeny + ObjectManager_player.rectTop;
	s16 right = ObjectManager_player.screenx + ObjectManager_player.rectRight;
	s16 bottom = ObjectManager_player.screeny + ObjectManager_player.rectBottom;

	if (left < ObjectManager_Item.screenx + ObjectManager_Item.rectRight &&
	right > ObjectManager_Item.screenx + ObjectManager_Item.rectLeft &&
	top < ObjectManager_Item.screeny + ObjectManager_Item.rectBottom &&
	bottom > ObjectManager_Item.screeny + ObjectManager_Item.rectTop)
	{
	ObjectManager_Item.HandleCollision(&ObjectManager_Item, &ObjectManager_player);
	}
	}
	*/



	//SMS_setBackdropColor(COLOR_YELLOW);
	SMS_initSprites();

	//DrawUtils_spritesDrawn = 0;

	ObjectManager_player.Draw(&ObjectManager_player);

	//SMS_setBackdropColor(COLOR_GRAY);

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
/*
	ObjectManager_enemyProjectileSlots[0].Draw(&ObjectManager_enemyProjectileSlots[0]);
	ObjectManager_enemyProjectileSlots[1].Draw(&ObjectManager_enemyProjectileSlots[1]);
	ObjectManager_enemyProjectileSlots[2].Draw(&ObjectManager_enemyProjectileSlots[2]);
	*/


	//SMS_setBackdropColor(COLOR_PINK);

	if (drawOrderToggle & 1)
	{
		objectSlotRunner = ObjectManager_enemySlots;
		switch (ObjectManager_numEnemies)
		{
		case 8: objectSlotRunner->Draw(objectSlotRunner++);
		case 7: objectSlotRunner->Draw(objectSlotRunner++);
		case 6: objectSlotRunner->Draw(objectSlotRunner++);
		case 5: objectSlotRunner->Draw(objectSlotRunner++);
		case 4: objectSlotRunner->Draw(objectSlotRunner++);
		case 3: objectSlotRunner->Draw(objectSlotRunner++);
		case 2: objectSlotRunner->Draw(objectSlotRunner++);
		case 1: objectSlotRunner->Draw(objectSlotRunner++);
		}

		objectSlotRunner =ObjectManager_effectSlots;
		switch (ObjectManager_numEffects)
		{
		case 8: objectSlotRunner->Draw(objectSlotRunner++);
		case 7: objectSlotRunner->Draw(objectSlotRunner++);
		case 6: objectSlotRunner->Draw(objectSlotRunner++);
		case 5: objectSlotRunner->Draw(objectSlotRunner++);
		case 4: objectSlotRunner->Draw(objectSlotRunner++);
		case 3: objectSlotRunner->Draw(objectSlotRunner++);
		case 2: objectSlotRunner->Draw(objectSlotRunner++);
		case 1: objectSlotRunner->Draw(objectSlotRunner++);
		}
	}
	else
	{
		switch (ObjectManager_numEffects)
		{
		case 8: ObjectManager_effectSlots[7].Draw(&ObjectManager_effectSlots[7]); 
		case 7: ObjectManager_effectSlots[6].Draw(&ObjectManager_effectSlots[6]); 
		case 6: ObjectManager_effectSlots[5].Draw(&ObjectManager_effectSlots[5]); 
		case 5: ObjectManager_effectSlots[4].Draw(&ObjectManager_effectSlots[4]); 
		case 4: ObjectManager_effectSlots[3].Draw(&ObjectManager_effectSlots[3]); 
		case 3: ObjectManager_effectSlots[2].Draw(&ObjectManager_effectSlots[2]); 
		case 2: ObjectManager_effectSlots[1].Draw(&ObjectManager_effectSlots[1]); 
		case 1: ObjectManager_effectSlots[0].Draw(&ObjectManager_effectSlots[0]); 
		}

		switch (ObjectManager_numEnemies)
		{
		case 8: ObjectManager_enemySlots[7].Draw(&ObjectManager_enemySlots[7]);
		case 7: ObjectManager_enemySlots[6].Draw(&ObjectManager_enemySlots[6]);
		case 6: ObjectManager_enemySlots[5].Draw(&ObjectManager_enemySlots[5]);
		case 5: ObjectManager_enemySlots[4].Draw(&ObjectManager_enemySlots[4]);
		case 4: ObjectManager_enemySlots[3].Draw(&ObjectManager_enemySlots[3]);
		case 3: ObjectManager_enemySlots[2].Draw(&ObjectManager_enemySlots[2]);
		case 2: ObjectManager_enemySlots[1].Draw(&ObjectManager_enemySlots[1]);
		case 1: ObjectManager_enemySlots[0].Draw(&ObjectManager_enemySlots[0]);
		}
	}

	ObjectManager_Item.Draw(&ObjectManager_Item);

	drawOrderToggle++;
}

BOOL ObjectManagerUtils_doProjectCollisionCheck(GameObject* gameObject)
{
	objectSlotRunner = ObjectManager_projectileSlots;
	u8 counter = NUM_PROJECTILE_SLOTS;

	s16 left = gameObject->screenx + gameObject->rectLeft;
	s16 top = gameObject->screeny + gameObject->rectTop;
	s16 right = gameObject->screenx + gameObject->rectRight;
	s16 bottom = gameObject->screeny + gameObject->rectBottom;

	while (counter--)
	{
		if (objectSlotRunner->alive &&
			left < objectSlotRunner->screenx + objectSlotRunner->rectRight &&
			right > objectSlotRunner->screenx + objectSlotRunner->rectLeft &&
			top < objectSlotRunner->screeny + objectSlotRunner->rectBottom &&
			bottom > objectSlotRunner->screeny + objectSlotRunner->rectTop
			)
		{
			objectSlotRunner->HandleCollision(objectSlotRunner, gameObject);
			return TRUE;
		}

		objectSlotRunner++;
	}

	return FALSE;
}