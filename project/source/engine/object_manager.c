#include "object_manager.h"
#include <string.h>
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/scroll_manager.h"
#include "engine/command_manager.h"
#include "engine/resource_manager.h"
#include "engine/object_utils.h"
#include "engine/draw_utils.h"

GameObject ObjectManager_player;
GameObject ObjectManager_Item;

#define NUM_PROJECTILE_SLOTS 3
#define NUM_ENEMY_PROJECTILE_SLOTS 3
#define NUM_ENEMY_SLOTS 8
#define NUM_EFFECT_SLOTS 8
#define NUM_EFFECT_SLOTS_MASK 0x7

GameObject ObjectManager_projectileSlots[NUM_PROJECTILE_SLOTS];
GameObject ObjectManager_enemyProjectileSlots[NUM_ENEMY_PROJECTILE_SLOTS];
GameObject ObjectManager_enemySlots[NUM_ENEMY_SLOTS];
GameObject ObjectManager_effectSlots[NUM_EFFECT_SLOTS];

GameObject* objectSlotRunner;

u8 ObjectManager_objectId = 0;

u8 ObjectManager_numEnemies = 0;

u8 ObjectManager_numEffects; // effects are treated as a circular list. older effects are overwritten.

GameObject* ObjectManager_activeProjectiles[NUM_PROJECTILE_SLOTS];
u8 ObjectManager_activeProjectilesCount;

//GameObject* ObjectManager_activeEnemies[NUM_ENEMY_SLOTS];
//u8 ObjectManager_activeEnemiesCount;

u8 ObjectManager_currentEnemyIndex;

#define NUM_VDP_DRAW_ITEMS 4
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

	ObjectManager_objectId = 0;

	memset(ObjectManager_projectileSlots, 0, sizeof(ObjectManager_projectileSlots));
	memset(ObjectManager_enemyProjectileSlots, 0, sizeof(ObjectManager_enemyProjectileSlots));
	memset(ObjectManager_enemySlots, 0, sizeof(ObjectManager_enemySlots));
	memset(ObjectManager_effectSlots, 0,sizeof(ObjectManager_effectSlots));

	ObjectManager_numEnemies = 0;
	ObjectManager_numEffects = 0;

	// setup objects
	objectSlotRunner = ObjectManager_projectileSlots;
	u8 counter = NUM_PROJECTILE_SLOTS;

	while (counter--)
	{
		ObjectManager_DestroyObject(objectSlotRunner);
		objectSlotRunner++;
	}



	objectSlotRunner = ObjectManager_enemyProjectileSlots;
	counter = NUM_ENEMY_PROJECTILE_SLOTS;

	while (counter--)
	{
		ObjectManager_DestroyObject(objectSlotRunner);
		objectSlotRunner++;
	}



	objectSlotRunner = ObjectManager_enemySlots;
	counter = NUM_ENEMY_SLOTS;
	while (counter--)
	{
		objectSlotRunner->alive = FALSE;
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

	ObjectManager_DestroyObject(&ObjectManager_Item);
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

	/*ObjectManager_projectileSlots[0].Update(&ObjectManager_projectileSlots[0]);
	ObjectManager_projectileSlots[1].Update(&ObjectManager_projectileSlots[1]);
	ObjectManager_projectileSlots[2].Update(&ObjectManager_projectileSlots[2]);

	ObjectManager_enemyProjectileSlots[0].Update(&ObjectManager_enemyProjectileSlots[0]);
	ObjectManager_enemyProjectileSlots[1].Update(&ObjectManager_enemyProjectileSlots[1]);
	ObjectManager_enemyProjectileSlots[2].Update(&ObjectManager_enemyProjectileSlots[2]);

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
	*/


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

	/*
	ObjectManager_projectileSlots[0].Draw(&ObjectManager_projectileSlots[0]);
	ObjectManager_projectileSlots[1].Draw(&ObjectManager_projectileSlots[1]);
	ObjectManager_projectileSlots[2].Draw(&ObjectManager_projectileSlots[2]);

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

GameObject* ObjectManager_CreateObject(u8 objectType)
{
	GameObject* objectSlotRunner = ObjectManager_enemySlots;
	u8 counter = NUM_ENEMY_SLOTS;

	if (objectType == OBJECTTYPE_ENEMY)
	{
		if (ObjectManager_numEnemies == NUM_ENEMY_SLOTS)
			return NULL;

		GameObject* newObject = &ObjectManager_enemySlots[ObjectManager_numEnemies];
		newObject->alive = TRUE;
		ObjectManager_numEnemies++;
		return newObject;
	}
	else if (objectType == OBJECTTYPE_PROJECTILE)
	{
		objectSlotRunner = ObjectManager_projectileSlots;
		counter = NUM_PROJECTILE_SLOTS;	
	}
	else if (objectType == OBJECTTYPE_EFFECT)
	{
		// treat effects as a circular list. we overwrite the older effects without waiting
		// if they're done.
		objectSlotRunner = ObjectManager_effectSlots + (ObjectManager_numEffects & NUM_EFFECT_SLOTS_MASK);
		ObjectManager_numEffects++;
		return objectSlotRunner;
	}
	else if (objectType == OBJECTTYPE_ENEMY_PROJECTILE)
	{
		objectSlotRunner = ObjectManager_enemyProjectileSlots;
		counter = NUM_ENEMY_PROJECTILE_SLOTS;
	}
	else if (objectType == OBJECTTYPE_ITEM)
	{
		ObjectManager_Item.alive = TRUE;
		return &ObjectManager_Item;
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


void ApplyGameObjectTemplate(GameObject* object, 
							 const GameObjectTemplate* gameObjectTemplate)
{
	object->objectType = gameObjectTemplate->objectType;
	object->health = gameObjectTemplate->startHealth;
	object->damage = gameObjectTemplate->damage;

	object->rectLeft = gameObjectTemplate->rectLeft;
	object->rectTop = gameObjectTemplate->rectTop;
	object->rectRight = gameObjectTemplate->rectRight;
	object->rectBottom = gameObjectTemplate->rectBottom;

	if (gameObjectTemplate->resourceInfo != NULL)
		ResourceManager_SetupResource(object, gameObjectTemplate->resourceInfo);
}

/*
GameObject* ObjectManager_CreateObjectByTemplate(const GameObjectTemplate* gameObjectTemplate)
{
u8 objectType = gameObjectTemplate->objectType;

GameObject* objectSlotRunner = ObjectManager_enemySlots;
u8 counter = NUM_ENEMY_SLOTS;

if (objectType == OBJECTTYPE_PROJECTILE)
{
objectSlotRunner = ObjectManager_projectileSlots;
counter = NUM_PROJECTILE_SLOTS;	
}
else if (objectType == OBJECTTYPE_EFFECT)
{
// treat effects as a circular list. we overwrite the older effects without waiting
// if they're done.
objectSlotRunner = ObjectManager_effectSlots + (ObjectManager_numEffects & NUM_EFFECT_SLOTS_MASK);
ObjectManager_numEffects++;
ApplyGameObjectTemplate(objectSlotRunner, gameObjectTemplate);
return objectSlotRunner;
}
else if (objectType == OBJECTTYPE_ENEMY_PROJECTILE)
{
objectSlotRunner = ObjectManager_enemyProjectileSlots;
counter = NUM_ENEMY_PROJECTILE_SLOTS;
}
else if (objectType == OBJECTTYPE_ITEM)
{
ObjectManager_Item.alive = TRUE;
return &ObjectManager_Item;
}

while (counter--)
{
if (!objectSlotRunner->alive)
{
objectSlotRunner->alive = TRUE;

ApplyGameObjectTemplate(objectSlotRunner, gameObjectTemplate);
return objectSlotRunner;
}

objectSlotRunner++;
}

return NULL;
}
*/
GameObject* FindFreeGameObject(u8 objectType)
{
	if (objectType == OBJECTTYPE_PLAYER)
	{
		return &ObjectManager_player;
	}
	else if (objectType == 	OBJECTTYPE_COMMANDRUNNER)
	{
		return &CommandManager_commandRunnerObject;
	}

	objectSlotRunner = ObjectManager_enemySlots;
	u8 counter = NUM_ENEMY_SLOTS;


	if (objectType == OBJECTTYPE_ENEMY)
	{
		if (ObjectManager_numEnemies == NUM_ENEMY_SLOTS)
			return NULL;

		GameObject* newObject = &ObjectManager_enemySlots[ObjectManager_numEnemies];
		newObject->alive = TRUE;
		ObjectManager_numEnemies++;
		return newObject;
	}
	else if (objectType == OBJECTTYPE_PROJECTILE)
	{
		objectSlotRunner = ObjectManager_projectileSlots;
		counter = NUM_PROJECTILE_SLOTS;	
	}
	else if (objectType == OBJECTTYPE_EFFECT)
	{
		// treat effects as a circular list. we overwrite the older effects without waiting
		// if they're done.
		objectSlotRunner = ObjectManager_effectSlots + (ObjectManager_numEffects & NUM_EFFECT_SLOTS_MASK);
		ObjectManager_numEffects++;
		return objectSlotRunner;
	}
	else if (objectType == OBJECTTYPE_ENEMY_PROJECTILE)
	{
		objectSlotRunner = ObjectManager_enemyProjectileSlots;
		counter = NUM_ENEMY_PROJECTILE_SLOTS;
	}
	else if (objectType == OBJECTTYPE_ITEM)
	{
		ObjectManager_Item.alive = TRUE;
		return &ObjectManager_Item;
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

GameObject* ObjectManager_CreateObjectByCreateInfo(const CreateInfo* createInfo)
{
	const GameObjectTemplate* gameObjectTemplate = createInfo->gameObjectTemplate;
	u8 objectType = gameObjectTemplate->objectType;

	GameObject* gameObject = FindFreeGameObject(objectType);
	if (gameObject == NULL)
		return NULL;

	gameObject->objectId = ObjectManager_objectId++;
	gameObject->x = createInfo->startX;
	gameObject->y = createInfo->startY;
	gameObject->resourceInfo = createInfo->gameObjectTemplate->resourceInfo;
	gameObject->extraResources = createInfo->gameObjectTemplate->extraResources;

	ApplyGameObjectTemplate(gameObject, gameObjectTemplate);

	gameObjectTemplate->initFunction(gameObject, createInfo);

	return gameObject;
}

void ObjectManager_DestroyObject(GameObject* gameObject)
{
	if (gameObject->objectType == OBJECTTYPE_ENEMY)
	{
		// if there's only one, just decrement the count
		// else if the object is at the end, do, just decrement the count
		// else, copy the last into the destroyed object.

		u8 objectIndex = gameObject - ObjectManager_enemySlots;

		if (ObjectManager_numEnemies > 1 && objectIndex < ObjectManager_numEnemies - 1)
		{
			GameObject* lastObject = &ObjectManager_enemySlots[ObjectManager_numEnemies - 1];

			memcpy(gameObject, lastObject, sizeof(GameObject));
		}

		ObjectManager_numEnemies--;
	}
	else
	{
		gameObject->Update = ObjectUtils_gameObjectDoNothing;
		gameObject->Draw = DrawUtils_drawNothing;
		gameObject->alive = FALSE;
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



void ObjectManager_QueueVDPDraw(GameObject* gameObject, ObjectFunctionType vdpDrawFunction)
{
	if (ObjectManager_numVdpDrawItems == NUM_VDP_DRAW_ITEMS)
		while (1) {}

	ObjectManager_vdpDrawGameObjects[ObjectManager_numVdpDrawItems] = gameObject;
	ObjectManager_vdpDrawFunctions[ObjectManager_numVdpDrawItems] = vdpDrawFunction;

	ObjectManager_numVdpDrawItems++;
}

void ObjectManager_VDPDraw(void)
{
	//SMS_setBackdropColor(COLOR_RED);

	switch (ObjectManager_numVdpDrawItems)
	{
	case 4: ObjectManager_vdpDrawFunctions[3](ObjectManager_vdpDrawGameObjects[3]);
	case 3: ObjectManager_vdpDrawFunctions[2](ObjectManager_vdpDrawGameObjects[2]);
	case 2: ObjectManager_vdpDrawFunctions[1](ObjectManager_vdpDrawGameObjects[1]);
	case 1: ObjectManager_vdpDrawFunctions[0](ObjectManager_vdpDrawGameObjects[0]);
	}

	//SMS_setBackdropColor(COLOR_BLACK);
}