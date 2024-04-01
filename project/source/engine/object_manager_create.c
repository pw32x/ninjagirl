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

GameObject* FindFreeGameObject(u8 objectType)
{
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
