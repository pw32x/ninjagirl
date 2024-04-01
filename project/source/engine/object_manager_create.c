#include "object_manager_create.h"
#include "object_manager.h"
#include "object_manager_slots.h"
#include "engine\object_utils.h"
#include "engine\draw_utils.h"
#include "engine\resource_manager.h"
#include "engine\command_manager.h"
#include <string.h>
#include "SMSlib.h"


u8 ObjectManager_objectId = 0;
u8 ObjectManager_numEnemies = 0;
u8 ObjectManager_numEffects; // effects are treated as a circular list. older effects are overwritten.

//GameObject* ObjectManager_activeProjectiles[NUM_PROJECTILE_SLOTS];
//u8 ObjectManager_activeProjectilesCount;

//GameObject* ObjectManager_activeEnemies[NUM_ENEMY_SLOTS];
//u8 ObjectManager_activeEnemiesCount;

//u8 ObjectManager_currentEnemyIndex;

void ObjectManager_InitCreate(void)
{
	ObjectManager_objectId = 0;
	ObjectManager_numEnemies = 0;
	ObjectManager_numEffects = 0;
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

GameObject* FindFreeGameObject(u8 objectType)
{
	// 108/738/481.1

	GameObject* objectSlotRunner;

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
	// 4880/359969/117125.2
	// 3957/355303/115453.6
	// 3851/354986/115326.8
	// 3778/354780/115244.4

	const GameObjectTemplate* gameObjectTemplate = createInfo->gameObjectTemplate;
	u8 objectType = gameObjectTemplate->objectType;

	GameObject* gameObject = FindFreeGameObject(objectType);
	if (gameObject == NULL)
		return NULL;

	gameObject->objectId = ObjectManager_objectId++;

	memcpy(&gameObject->x, &createInfo->startX, 4);
	memcpy(&gameObject->health, &gameObjectTemplate->startHealth, sizeof(GameObjectTemplate));

	if (gameObjectTemplate->resourceInfo != NULL)
		ResourceManager_SetupResource(gameObject, gameObjectTemplate->resourceInfo);

	gameObjectTemplate->initFunction(gameObject, createInfo);

	return gameObject;
}

GameObject* ObjectManager_CreatePlayerProjectile(const CreateInfo* createInfo)
{
	// one bullet 3923/3923/3923.0 
	// max 402/3985/2946.0
	// one bullet 3849/3849/3849.0
	// max 402/3985/2946.0

	// one 3748/3748/3748.0
	// max 516/3960/3075.5

	// one 3016/3016/3016.0
	// max 532/3232/2397.5

	// 2938/2938/2938.0
	// max 532/3154/2062.5

	// 2825/2825/2825.0
	// 532/3041/2114.7

	const GameObjectTemplate* gameObjectTemplate = createInfo->gameObjectTemplate;

	GameObject* gameObject = ObjectManager_projectileSlots;

	if (!gameObject->alive)  goto create; gameObject++;
	if (!gameObject->alive)  goto create; gameObject++;
	if (!gameObject->alive)  goto create; 
	return NULL;

create:

	gameObject->alive = TRUE;
	gameObject->objectId = ObjectManager_objectId++;

	memcpy(&gameObject->x, &createInfo->startX, 4);
	memcpy(&gameObject->health, &gameObjectTemplate->startHealth, sizeof(GameObjectTemplate));

	if (gameObjectTemplate->resourceInfo != NULL)
		ResourceManager_SetupResource(gameObject, gameObjectTemplate->resourceInfo);

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
