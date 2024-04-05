#include "object_manager.h"

#include "engine/object_manager_create.h"
#include "engine/object_manager_vdp.h"
#include "engine/object_manager_slots.h"
#include "engine/base_defines.h"
#include "engine/scroll_manager.h"
#include "engine/command_manager.h"
//#include "engine/resource_manager.h"
//#include "engine/object_utils.h"
//#include "engine/draw_utils.h"

#include <string.h>
#include "SMSlib.h"

GameObject* objectSlotRunner;

//GameObject* ObjectManager_activeProjectiles[NUM_PROJECTILE_SLOTS];
//u8 ObjectManager_activeProjectilesCount;


u8 ObjectManager_currentEnemyIndex;


BOOL ObjectManagerUtils_doProjectCollisionCheck(GameObject* gameObject);

void ObjectManager_Init(void)
{
	ObjectManager_InitCreate();
	ObjectManager_InitSlots();
}

void DrawEffectsAndEnemiesOrder1(void);
void DrawEffectsAndEnemiesOrder2(void);

u8 drawOrderToggle = FALSE;

void ObjectManager_Update(void)
{


	ObjectManager_numVdpDrawItems = 0;

	//SMS_setBackdropColor(COLOR_RED);

	ObjectManager_player.Update(&ObjectManager_player);
	
	ScrollManager_Update(&ObjectManager_player);

	ObjectManager_projectileSlots[0].Update(&ObjectManager_projectileSlots[0]);
	ObjectManager_projectileSlots[1].Update(&ObjectManager_projectileSlots[1]);
	ObjectManager_projectileSlots[2].Update(&ObjectManager_projectileSlots[2]);

	/*
	ObjectManager_enemyProjectileSlots[0].Update(&ObjectManager_enemyProjectileSlots[0]);
	ObjectManager_enemyProjectileSlots[1].Update(&ObjectManager_enemyProjectileSlots[1]);
	ObjectManager_enemyProjectileSlots[2].Update(&ObjectManager_enemyProjectileSlots[2]);
	*/

	// add new objects and enemies only after we've done the collision checks for the currently 
	// active ones.
	CommandManager_commandRunnerObject.Update(&CommandManager_commandRunnerObject);

	//SMS_setBackdropColor(COLOR_ORANGE);

	switch (ObjectManager_numActiveEnemies)
	{
	case 8: ObjectManager_activeEnemySlots[7]->Update(ObjectManager_activeEnemySlots[7]);
	case 7: ObjectManager_activeEnemySlots[6]->Update(ObjectManager_activeEnemySlots[6]);
	case 6: ObjectManager_activeEnemySlots[5]->Update(ObjectManager_activeEnemySlots[5]);
	case 5: ObjectManager_activeEnemySlots[4]->Update(ObjectManager_activeEnemySlots[4]);
	case 4: ObjectManager_activeEnemySlots[3]->Update(ObjectManager_activeEnemySlots[3]);
	case 3: ObjectManager_activeEnemySlots[2]->Update(ObjectManager_activeEnemySlots[2]);
	case 2: ObjectManager_activeEnemySlots[1]->Update(ObjectManager_activeEnemySlots[1]);
	case 1: ObjectManager_activeEnemySlots[0]->Update(ObjectManager_activeEnemySlots[0]);
	}

	ObjectManager_processEnemyDeletes();


	// perform collisions against projectiles
	switch (ObjectManager_numActiveEnemies)
	{
	case 8: ObjectManagerUtils_doProjectCollisionCheck(ObjectManager_activeEnemySlots[7]);
	case 7: ObjectManagerUtils_doProjectCollisionCheck(ObjectManager_activeEnemySlots[6]);
	case 6: ObjectManagerUtils_doProjectCollisionCheck(ObjectManager_activeEnemySlots[5]);
	case 5: ObjectManagerUtils_doProjectCollisionCheck(ObjectManager_activeEnemySlots[4]);
	case 4: ObjectManagerUtils_doProjectCollisionCheck(ObjectManager_activeEnemySlots[3]);
	case 3: ObjectManagerUtils_doProjectCollisionCheck(ObjectManager_activeEnemySlots[2]);
	case 2: ObjectManagerUtils_doProjectCollisionCheck(ObjectManager_activeEnemySlots[1]);
	case 1: ObjectManagerUtils_doProjectCollisionCheck(ObjectManager_activeEnemySlots[0]);
	}

	switch (ObjectManager_numActiveEffects)
	{
	case 8: ObjectManager_activeEffectSlots[7]->Update(ObjectManager_activeEffectSlots[7]);
	case 7: ObjectManager_activeEffectSlots[6]->Update(ObjectManager_activeEffectSlots[6]);
	case 6: ObjectManager_activeEffectSlots[5]->Update(ObjectManager_activeEffectSlots[5]);
	case 5: ObjectManager_activeEffectSlots[4]->Update(ObjectManager_activeEffectSlots[4]);
	case 4: ObjectManager_activeEffectSlots[3]->Update(ObjectManager_activeEffectSlots[3]);
	case 3: ObjectManager_activeEffectSlots[2]->Update(ObjectManager_activeEffectSlots[2]);
	case 2: ObjectManager_activeEffectSlots[1]->Update(ObjectManager_activeEffectSlots[1]);
	case 1: ObjectManager_activeEffectSlots[0]->Update(ObjectManager_activeEffectSlots[0]);
	}

	ObjectManager_processEffectDeletes();

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

	if (drawOrderToggle)
	{
		DrawEffectsAndEnemiesOrder1();
	}
	else
	{
		DrawEffectsAndEnemiesOrder2();
	}

	ObjectManager_Item.Draw(&ObjectManager_Item);

	//drawOrderToggle = !drawOrderToggle;

	// 9856
	// 7249 without function
	// 2607

	ObjectManager_processNewObjects();
}

void DrawEffectsAndEnemiesOrder1(void)
{
	GameObject** runner = ObjectManager_activeEnemySlots;

	switch (ObjectManager_numActiveEnemies)
	{
	case 8: (*runner)->Draw(*runner); runner++;
	case 7: (*runner)->Draw(*runner); runner++;
	case 6: (*runner)->Draw(*runner); runner++;
	case 5: (*runner)->Draw(*runner); runner++;
	case 4: (*runner)->Draw(*runner); runner++;
	case 3: (*runner)->Draw(*runner); runner++;
	case 2: (*runner)->Draw(*runner); runner++;
	case 1: (*runner)->Draw(*runner); runner++;
	}

	switch (ObjectManager_numActiveEffects)
	{
	case 8: ObjectManager_activeEffectSlots[7]->Draw(ObjectManager_activeEffectSlots[7]);
	case 7: ObjectManager_activeEffectSlots[6]->Draw(ObjectManager_activeEffectSlots[6]);
	case 6: ObjectManager_activeEffectSlots[5]->Draw(ObjectManager_activeEffectSlots[5]);
	case 5: ObjectManager_activeEffectSlots[4]->Draw(ObjectManager_activeEffectSlots[4]);
	case 4: ObjectManager_activeEffectSlots[3]->Draw(ObjectManager_activeEffectSlots[3]);
	case 3: ObjectManager_activeEffectSlots[2]->Draw(ObjectManager_activeEffectSlots[2]);
	case 2: ObjectManager_activeEffectSlots[1]->Draw(ObjectManager_activeEffectSlots[1]);
	case 1: ObjectManager_activeEffectSlots[0]->Draw(ObjectManager_activeEffectSlots[0]);
	}
}

void DrawEffectsAndEnemiesOrder2(void)
{
	GameObject** runner = ObjectManager_activeEffectSlots;

	switch (ObjectManager_numActiveEffects)
	{
	case 8: (*runner)->Draw(*runner); runner++;
	case 7: (*runner)->Draw(*runner); runner++;
	case 6: (*runner)->Draw(*runner); runner++;
	case 5: (*runner)->Draw(*runner); runner++;
	case 4: (*runner)->Draw(*runner); runner++;
	case 3: (*runner)->Draw(*runner); runner++;
	case 2: (*runner)->Draw(*runner); runner++;
	case 1: (*runner)->Draw(*runner); runner++;
	}

	switch (ObjectManager_numActiveEnemies)
	{
	case 8: ObjectManager_activeEnemySlots[7]->Draw(ObjectManager_activeEnemySlots[7]);
	case 7: ObjectManager_activeEnemySlots[6]->Draw(ObjectManager_activeEnemySlots[6]);
	case 6: ObjectManager_activeEnemySlots[5]->Draw(ObjectManager_activeEnemySlots[5]);
	case 5: ObjectManager_activeEnemySlots[4]->Draw(ObjectManager_activeEnemySlots[4]);
	case 4: ObjectManager_activeEnemySlots[3]->Draw(ObjectManager_activeEnemySlots[3]);
	case 3: ObjectManager_activeEnemySlots[2]->Draw(ObjectManager_activeEnemySlots[2]);
	case 2: ObjectManager_activeEnemySlots[1]->Draw(ObjectManager_activeEnemySlots[1]);
	case 1: ObjectManager_activeEnemySlots[0]->Draw(ObjectManager_activeEnemySlots[0]);
	}
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