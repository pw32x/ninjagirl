#include "object_manager_create.h"
#include "object_manager.h"
#include "object_manager_slots.h"
#include "engine\object_utils.h"
#include "engine\draw_utils.h"
#include "engine\resource_manager.h"
#include "engine\command_manager.h"
#include "engine\base_defines.h"
#include <string.h>
#include "SMSlib.h"


u8 ObjectManager_objectId = 0;

#define MAX_NEW_OBJECTS 16
u8 ObjectManager_numNewObjects;
GameObject* ObjectManager_newObjects[MAX_NEW_OBJECTS];

#define OBJECTSTATE_PENDING 2

u8 ObjectManager_resetActiveEnemies;
u8 ObjectManager_resetActiveEffects;
u8 ObjectManager_resetActiveProjectiles;
u8 ObjectManager_resetActiveEnemyProjectiles;


//GameObject* ObjectManager_activeProjectiles[MAX_PROJECTILES];
//u8 ObjectManager_activeProjectilesCount;

//GameObject* ObjectManager_activeEnemies[MAX_ENEMIES];
//u8 ObjectManager_activeEnemiesCount;

//u8 ObjectManager_currentEnemyIndex;


void ObjectManager_InitCreate(void)
{
	ObjectManager_objectId = 0;

	//SMS_debugPrintf("createBeginFrame: num new enemies %d\n", ObjectManager_numNewObjects);
	ObjectManager_numNewObjects = 0;
	ObjectManager_resetActiveEnemies = FALSE;
	ObjectManager_resetActiveEffects = FALSE;
	ObjectManager_resetActiveProjectiles = FALSE;
	ObjectManager_resetActiveEnemyProjectiles = FALSE;
}

GameObject* ObjectManager_CreateObject(u8 objectType)
{
	//MSG("ObjectManager_CreateObject\n");

	GameObject* objectSlotRunner = ObjectManager_enemySlots;
	u8 counter = MAX_ENEMIES;

	/*
	if (objectType == OBJECTTYPE_ENEMY)
	{
		if (ObjectManager_numEnemies == MAX_ENEMIES)
			return NULL;

		GameObject* newObject = &ObjectManager_enemySlots[ObjectManager_numEnemies];
		newObject->alive = TRUE;
		ObjectManager_numEnemies++;
		return newObject;
	}
	else
		if (objectType == OBJECTTYPE_PROJECTILE)
	{
		objectSlotRunner = ObjectManager_projectiles;
		counter = MAX_PROJECTILES;	
	}
	else if (objectType == OBJECTTYPE_EFFECT)
	{
		// treat effects as a circular list. we overwrite the older effects without waiting
		// if they're done.
		objectSlotRunner = ObjectManager_effects + (ObjectManager_numEffects & MAX_EFFECTS_MASK);
		ObjectManager_numEffects++;
		return objectSlotRunner;
	}

	else 
		if (objectType == OBJECTTYPE_ENEMY_PROJECTILE)
	{
		objectSlotRunner = ObjectManager_enemyProjectiles;
		counter = MAX_ENEMY_PROJECTILES;
	}
	else 
	*/if (objectType == OBJECTTYPE_ITEM)
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

void ObjectManager_processEnemyDeletes(void)
{
	// 3 enemies, destroy 1 119/1177/120.5
	// 2 enemies, destroy 1 119/935/121.3
	// 1 enemy, destroy 1   119/693/120.1

	if (!ObjectManager_resetActiveEnemies)
		return;

	//SMS_debugPrintf("rebuilding active enemy list\n");

	GameObject** activeEnemiesRunner = ObjectManager_activeEnemySlots;
	GameObject** activeEnemiesRunnerEnd = ObjectManager_activeEnemySlots + ObjectManager_numActiveEnemies;

	// iteration 1
	// activeEnemiesRunner		->	[alive]
	//								[dead]
	// activeEnemiesRunnerEnd	->	[blah]
	//
	// iteration 2
	//								[alive]
	// activeEnemiesRunner		->	[dead]
	// activeEnemiesRunnerEnd	->	[blah]
	//
	// copy + back up activeEnemiesRunnerEnd
	//								[alive]
	// activeEnemiesRunner/End	->	[blah]
	//								[blah]
	// iteration 3
	//								[alive]
	// activeEnemiesRunnerEnd	->	[blah]
	// activeEnemiesRunner		->	[blah]
	//
	// Done

	// every time we encounter a dead object, copy the pointer to the
	// last active object to it. Also back up the activeEnemiesRunnerEnd by one.
	// When activeEnemiesRunner activeEnemiesRunnerEnd cross, then we're done.
	do
	{
		if (!(*activeEnemiesRunner)->alive)
		{
			activeEnemiesRunnerEnd--;
			(*activeEnemiesRunner) = (*activeEnemiesRunnerEnd);
		}

		activeEnemiesRunner++;
	} while (activeEnemiesRunner < activeEnemiesRunnerEnd);

	ObjectManager_numActiveEnemies = activeEnemiesRunnerEnd - ObjectManager_activeEnemySlots;
	ObjectManager_resetActiveEnemies = FALSE;
	//SMS_debugPrintf("ObjectManager_numActiveEnemies: %d\n", ObjectManager_numActiveEnemies);
}

void ObjectManager_refreshActiveEffects(void)
{
	if (!ObjectManager_resetActiveEffects)
		return;

	GameObject** activeEffectsRunner = ObjectManager_currentActiveEffects;
	GameObject** activeEffectsRunnerEnd = ObjectManager_currentActiveEffects + ObjectManager_numActiveEffects;

	GameObject** ObjectManager_pendingEffectsRunner = ObjectManager_pendingEffects + ObjectManager_numPendingEffects;

	// Copy the alive objects to the pending list. Then swap
	// the pointer to the current and pending lists.

	while (activeEffectsRunner != activeEffectsRunnerEnd)
	{
		if ((*activeEffectsRunner)->alive)
		{
			*ObjectManager_pendingEffectsRunner = *activeEffectsRunner;
			ObjectManager_pendingEffectsRunner++;
		}

		activeEffectsRunner++;
	};

	ObjectManager_numActiveEffects = ObjectManager_pendingEffectsRunner - ObjectManager_pendingEffects;

	ObjectManager_resetActiveEffects = FALSE;
	ObjectManager_numPendingEffects = 0;

	if (ObjectManager_currentActiveEffects == ObjectManager_activeEffectsA)
	{
		ObjectManager_currentActiveEffects = ObjectManager_activeEffectsB;
		ObjectManager_pendingEffects = ObjectManager_activeEffectsA;
	}
	else
	{
		ObjectManager_currentActiveEffects = ObjectManager_activeEffectsA;
		ObjectManager_pendingEffects = ObjectManager_activeEffectsB;
	}
}

void ObjectManager_refreshActiveProjectiles(void)
{
	if (!ObjectManager_resetActiveProjectiles)
		return;

	GameObject** activeProjectilesRunner = ObjectManager_currentActiveProjectiles;
	GameObject** activeProjectilesRunnerEnd = ObjectManager_currentActiveProjectiles + ObjectManager_numActiveProjectiles;

	GameObject** ObjectManager_pendingProjectilesRunner = ObjectManager_pendingProjectiles + ObjectManager_numPendingProjectiles;

	// Copy the alive objects to the pending list. Then swap
	// the pointer to the current and pending lists.

	while (activeProjectilesRunner != activeProjectilesRunnerEnd)
	{
		if ((*activeProjectilesRunner)->alive)
		{
			*ObjectManager_pendingProjectilesRunner = *activeProjectilesRunner;
			ObjectManager_pendingProjectilesRunner++;
		}

		activeProjectilesRunner++;
	};

	ObjectManager_numActiveProjectiles = ObjectManager_pendingProjectilesRunner - ObjectManager_pendingProjectiles;

	ObjectManager_resetActiveProjectiles = FALSE;
	ObjectManager_numPendingProjectiles = 0;

	if (ObjectManager_currentActiveProjectiles == ObjectManager_activeProjectilesA)
	{
		ObjectManager_currentActiveProjectiles = ObjectManager_activeProjectilesB;
		ObjectManager_pendingProjectiles = ObjectManager_activeProjectilesA;
	}
	else
	{
		ObjectManager_currentActiveProjectiles = ObjectManager_activeProjectilesA;
		ObjectManager_pendingProjectiles = ObjectManager_activeProjectilesB;
	}

	//SMS_debugPrintf("ObjectManager_numActiveProjectiles: %d\n", ObjectManager_numActiveProjectiles);
	//SMS_setBackdropColor(COLOR_DARK_GREEN);
}


void ObjectManager_refreshActiveEnemyProjectiles(void)
{
	if (!ObjectManager_resetActiveEnemyProjectiles)
		return;

	GameObject** activeEnemyProjectilesRunner = ObjectManager_currentActiveEnemyProjectiles;
	GameObject** activeEnemyProjectilesRunnerEnd = ObjectManager_currentActiveEnemyProjectiles + ObjectManager_numActiveEnemyProjectiles;

	GameObject** ObjectManager_pendingEnemyProjectilesRunner = ObjectManager_pendingEnemyProjectiles + ObjectManager_numPendingEnemyProjectiles;

	// Copy the alive objects to the pending list. Then swap
	// the pointer to the current and pending lists.

	while (activeEnemyProjectilesRunner != activeEnemyProjectilesRunnerEnd)
	{
		if ((*activeEnemyProjectilesRunner)->alive)
		{
			*ObjectManager_pendingEnemyProjectilesRunner = *activeEnemyProjectilesRunner;
			ObjectManager_pendingEnemyProjectilesRunner++;
		}

		activeEnemyProjectilesRunner++;
	};

	ObjectManager_numActiveEnemyProjectiles = ObjectManager_pendingEnemyProjectilesRunner - ObjectManager_pendingEnemyProjectiles;

	ObjectManager_resetActiveEnemyProjectiles = FALSE;
	ObjectManager_numPendingEnemyProjectiles = 0;

	if (ObjectManager_currentActiveEnemyProjectiles == ObjectManager_activeEnemyProjectilesA)
	{
		ObjectManager_currentActiveEnemyProjectiles = ObjectManager_activeEnemyProjectilesB;
		ObjectManager_pendingEnemyProjectiles = ObjectManager_activeEnemyProjectilesA;
	}
	else
	{
		ObjectManager_currentActiveEnemyProjectiles = ObjectManager_activeEnemyProjectilesA;
		ObjectManager_pendingEnemyProjectiles = ObjectManager_activeEnemyProjectilesB;
	}

	//SMS_debugPrintf("ObjectManager_numActiveProjectiles: %d\n", ObjectManager_numActiveProjectiles);
	//SMS_setBackdropColor(COLOR_DARK_GREEN);
}

void ObjectManager_processNewObjects(void)
{
	

	// 185/1493/186.4 three objects
	// 106/1492/109.2 three objects
	// 106/1477/109.4 three objects
	// 106/1435/108.3 three objects
	// 17/1047/19.6 three objects

	if (!ObjectManager_numNewObjects)
		return;

	//MSG("ObjectManager_processNewObjects\n");

	while (ObjectManager_numNewObjects)
	{
		//SMS_debugPrintf("Added new object to active list\n");
		ObjectManager_numNewObjects--;
		GameObject* object = ObjectManager_newObjects[ObjectManager_numNewObjects];
		object->alive = TRUE;

		switch (object->objectType)
		{
		case OBJECTTYPE_ENEMY:
			//SMS_debugPrintf("appended new enemy\n");
			ObjectManager_activeEnemySlots[ObjectManager_numActiveEnemies] = object;
			ObjectManager_numActiveEnemies++;
			break;
		}
	}
}


GameObject* FindFreeGameObject(u8 objectType)
{
	MSG("FindFreeGameObject\n");
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


	//u8 counter;


	if (objectType == OBJECTTYPE_ENEMY)
	{
		//SMS_debugPrintf("Trying to add new enemy\n");

		if (ObjectManager_numActiveEnemies == MAX_ENEMIES)
			return NULL;

		//SMS_debugPrintf("Added new enemy\n");

		objectSlotRunner = ObjectManager_enemySlots;
		while (objectSlotRunner->alive)
			objectSlotRunner++;

		objectSlotRunner->alive = OBJECTSTATE_PENDING;

		ObjectManager_newObjects[ObjectManager_numNewObjects] = objectSlotRunner;
		ObjectManager_numNewObjects++;

		//SMS_debugPrintf("num new enemies %d\n", ObjectManager_numNewObjects);

		return objectSlotRunner;
	}
	/*
	else if (objectType == OBJECTTYPE_PROJECTILE)
	{
		objectSlotRunner = ObjectManager_projectiles;
		counter = MAX_PROJECTILES;	
	}
	else if (objectType == OBJECTTYPE_EFFECT)
	{
		// treat effects as a circular list. we overwrite the older effects without waiting
		// if they're done.
		objectSlotRunner = ObjectManager_effects + (ObjectManager_numEffects & MAX_EFFECTS_MASK);
		ObjectManager_numEffects++;
		return objectSlotRunner;
	}

	else if (objectType == OBJECTTYPE_ENEMY_PROJECTILE)
	{
		objectSlotRunner = ObjectManager_enemyProjectiles;
		counter = MAX_ENEMY_PROJECTILES;
	}
	*/
	else if (objectType == OBJECTTYPE_ITEM)
	{
		ObjectManager_Item.alive = TRUE;
		return &ObjectManager_Item;
	}

	/*
	while (counter--)
	{
		if (!objectSlotRunner->alive)
		{
			objectSlotRunner->alive = TRUE;
			return objectSlotRunner;
		}

		objectSlotRunner++;
	}
	*/
	return NULL;
}

GameObject* ObjectManager_CreateObjectByCreateInfo(const CreateInfo* createInfo)
{
	//MSG("ObjectManager_CreateObjectByCreateInfo\n");
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

GameObject* ObjectManager_CreateEffect(const EffectCreateInfo* effectCreateInfo)
{
	// Be careful not create more objects than active slots.
	if (ObjectManager_numActiveEffects == MAX_EFFECTS ||
		ObjectManager_numPendingEffects == MAX_EFFECTS)
	{
		return NULL;
	}

	GameObject* gameObject = ObjectManager_effects;
	while (gameObject->alive)
		gameObject++;

	gameObject->alive = TRUE;

	ObjectManager_pendingEffects[ObjectManager_numPendingEffects] = gameObject;
	ObjectManager_numPendingEffects++;

	const GameObjectTemplate* gameObjectTemplate = effectCreateInfo->gameObjectTemplate;

	memcpy(&gameObject->x, &effectCreateInfo->startX, 4);
	memcpy(&gameObject->health, &gameObjectTemplate->startHealth, sizeof(GameObjectTemplate));

	ResourceManager_SetupResource(gameObject, gameObjectTemplate->resourceInfo);

	gameObjectTemplate->initFunction(gameObject, effectCreateInfo);

	ObjectManager_resetActiveEffects = TRUE;

	//SMS_setBackdropColor(COLOR_DARK_GREEN);

	return gameObject;
}

GameObject* ObjectManager_CreatePlayerProjectile(const CreateInfo* createInfo)
{
	// Be careful not create more objects than active slots.
	if (ObjectManager_numActiveProjectiles == MAX_PROJECTILES ||
		ObjectManager_numPendingProjectiles == MAX_PROJECTILES)
	{
		return NULL;
	}

	GameObject* gameObject = ObjectManager_projectiles;
	while (gameObject->alive)
		gameObject++;

	gameObject->alive = TRUE;

	ObjectManager_pendingProjectiles[ObjectManager_numPendingProjectiles] = gameObject;
	ObjectManager_numPendingProjectiles++;

	const GameObjectTemplate* gameObjectTemplate = createInfo->gameObjectTemplate;

	memcpy(&gameObject->x, &createInfo->startX, 4);
	memcpy(&gameObject->health, &gameObjectTemplate->startHealth, sizeof(GameObjectTemplate));

	ResourceManager_SetupResource(gameObject, gameObjectTemplate->resourceInfo);

	gameObjectTemplate->initFunction(gameObject, createInfo);

	ObjectManager_resetActiveProjectiles = TRUE;

	//SMS_setBackdropColor(COLOR_DARK_GREEN);

	return gameObject;
}


GameObject* ObjectManager_CreateEnemyProjectile(const CreateInfo* createInfo)
{
	// Be careful not create more objects than active slots.
	if (ObjectManager_numActiveEnemyProjectiles == MAX_ENEMY_PROJECTILES ||
		ObjectManager_numPendingEnemyProjectiles == MAX_ENEMY_PROJECTILES)
	{
		return NULL;
	}

	GameObject* gameObject = ObjectManager_enemyProjectiles;
	while (gameObject->alive)
		gameObject++;

	gameObject->alive = TRUE;

	ObjectManager_pendingEnemyProjectiles[ObjectManager_numPendingEnemyProjectiles] = gameObject;
	ObjectManager_numPendingEnemyProjectiles++;

	const GameObjectTemplate* gameObjectTemplate = createInfo->gameObjectTemplate;

	memcpy(&gameObject->x, &createInfo->startX, 4);
	memcpy(&gameObject->health, &gameObjectTemplate->startHealth, sizeof(GameObjectTemplate));

	ResourceManager_SetupResource(gameObject, gameObjectTemplate->resourceInfo);

	gameObjectTemplate->initFunction(gameObject, createInfo);

	ObjectManager_resetActiveEnemyProjectiles = TRUE;

	//SMS_setBackdropColor(COLOR_DARK_GREEN);

	return gameObject;
}

void ObjectManager_DestroyObject(GameObject* gameObject)
{
	//MSG("ObjectManager_DestroyObject\n");

	gameObject->alive = FALSE;
	gameObject->Update = ObjectUtils_gameObjectDoNothing;
	gameObject->Draw = DrawUtils_drawNothing;

	switch (gameObject->objectType)
	{
	case OBJECTTYPE_ENEMY: ObjectManager_resetActiveEnemies = TRUE; break;
	case OBJECTTYPE_EFFECT: ObjectManager_resetActiveEffects = TRUE; break;
	case OBJECTTYPE_PROJECTILE: ObjectManager_resetActiveProjectiles = TRUE; break;
	case OBJECTTYPE_ENEMY_PROJECTILE: ObjectManager_resetActiveEnemyProjectiles = TRUE; break;
	}
}
