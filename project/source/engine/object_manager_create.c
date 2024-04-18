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


//GameObject* ObjectManager_activeProjectiles[NUM_PROJECTILE_SLOTS];
//u8 ObjectManager_activeProjectilesCount;

//GameObject* ObjectManager_activeEnemies[NUM_ENEMY_SLOTS];
//u8 ObjectManager_activeEnemiesCount;

//u8 ObjectManager_currentEnemyIndex;


void ObjectManager_InitCreate(void)
{
	ObjectManager_objectId = 0;

	ObjectManager_numActiveEnemies = 0;
	ObjectManager_numActiveEffects = 0;
	ObjectManager_numActiveProjectiles = 0;
	ObjectManager_numActiveEnemyProjectiles = 0;

	//SMS_debugPrintf("createBeginFrame: num new enemies %d\n", ObjectManager_numNewObjects);
	ObjectManager_numNewObjects = 0;
	ObjectManager_resetActiveEnemies = FALSE;
	ObjectManager_resetActiveEffects = FALSE;
	ObjectManager_resetActiveProjectiles = FALSE;
	ObjectManager_resetActiveEnemyProjectiles = FALSE;
}

GameObject* ObjectManager_CreateObject(u8 objectType)
{
	GameObject* objectSlotRunner = ObjectManager_enemySlots;
	u8 counter = NUM_ENEMY_SLOTS;

	/*
	if (objectType == OBJECTTYPE_ENEMY)
	{
		if (ObjectManager_numEnemies == NUM_ENEMY_SLOTS)
			return NULL;

		GameObject* newObject = &ObjectManager_enemySlots[ObjectManager_numEnemies];
		newObject->alive = TRUE;
		ObjectManager_numEnemies++;
		return newObject;
	}
	else
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
		return objectSlotRunner;
	}

	else 
		if (objectType == OBJECTTYPE_ENEMY_PROJECTILE)
	{
		objectSlotRunner = ObjectManager_enemyProjectileSlots;
		counter = NUM_ENEMY_PROJECTILE_SLOTS;
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

void ObjectManager_processEffectDeletes(void)
{
	// 108/2301/109.7
	// 117/1211/133.6
	// 119/703/120.5
	// 119/693/138.5

	if (!ObjectManager_resetActiveEffects)
		return;

	//SMS_setBackdropColor(COLOR_RED);
	//SMS_debugPrintf("rebuilding active effect list\n");

	GameObject** activeEffectsRunner = ObjectManager_activeEffectSlots;
	GameObject** activeEffectsRunnerEnd = ObjectManager_activeEffectSlots + ObjectManager_numActiveEffects;

	//SMS_debugPrintf("ObjectManager_numActiveEffects: %d\n", activeEffectsRunnerEnd - activeEffectsRunner);

	// iteration 1
	// activeEffectsRunner		->	[alive]
	//								[dead]
	// activeEffectsRunnerEnd	->	[blah]
	//
	// iteration 2
	//								[alive]
	// activeEffectsRunner		->	[dead]
	// activeEffectsRunnerEnd	->	[blah]
	//
	// copy + back up activeEffectsRunnerEnd
	//								[alive]
	// activeEffectsRunner/End	->	[blah]
	//								[blah]
	// iteration 3
	//								[alive]
	// activeEffectsRunnerEnd	->	[blah]
	// activeEffectsRunner		->	[blah]
	//
	// Done

	// every time we encounter a dead object, copy the pointer to the
	// last active object to it. Also back up the activeEffectsRunnerEnd by one.
	// When activeEffectsRunner activeEffectsRunnerEnd cross, then we're done.
	do
	{
		if (!(*activeEffectsRunner)->alive)
		{
			activeEffectsRunnerEnd--;
			(*activeEffectsRunner) = (*activeEffectsRunnerEnd);
		}

		activeEffectsRunner++;
	} while (activeEffectsRunner < activeEffectsRunnerEnd);

	ObjectManager_numActiveEffects = activeEffectsRunnerEnd - ObjectManager_activeEffectSlots;
	ObjectManager_resetActiveEffects = FALSE;

	//SMS_debugPrintf("ObjectManager_numActiveEffects: %d\n", ObjectManager_numActiveEffects);
	//SMS_setBackdropColor(COLOR_DARK_GREEN);
}

void ObjectManager_processProjectileDeletes(void)
{
	// 119/693/119.9 one bullet 
	// 119/935/120.7 three bullets 
	if (!ObjectManager_resetActiveProjectiles)
		return;

	//SMS_setBackdropColor(COLOR_RED);
	//SMS_debugPrintf("rebuilding active particle list\n");

	GameObject** activeProjectilesRunner = ObjectManager_activeProjectileSlots;
	GameObject** activeProjectilesRunnerEnd = ObjectManager_activeProjectileSlots + ObjectManager_numActiveProjectiles;

	//SMS_debugPrintf("ObjectManager_numActiveProjectiles: %d\n", ObjectManager_numActiveProjectiles);

	// iteration 1
	// activeProjectilesRunner		->	[alive]
	//									[dead]
	// activeProjectilesRunnerEnd	->	[blah]
	//
	// iteration 2
	//									[alive]
	// activeProjectilesRunner		->	[dead]
	// activeProjectilesRunnerEnd	->	[blah]
	//
	// copy + back up activeProjectilesRunnerEnd
	//									[alive]
	// activeProjectilesRunner/End	->	[blah]
	//									[blah]
	// iteration 3
	//									[alive]
	// activeProjectilesRunnerEnd	->	[blah]
	// activeProjectilesRunner		->	[blah]
	//
	// Done

	// every time we encounter a dead object, copy the pointer to the
	// last active object to it. Also back up the activeProjectilesRunnerEnd by one.
	// When activeProjectilesRunner activeProjectilesRunnerEnd cross, then we're done.
	do
	{
		if (!(*activeProjectilesRunner)->alive)
		{
			activeProjectilesRunnerEnd--;
			(*activeProjectilesRunner) = (*activeProjectilesRunnerEnd);
		}

		activeProjectilesRunner++;
	} while (activeProjectilesRunner < activeProjectilesRunnerEnd);

	ObjectManager_numActiveProjectiles = activeProjectilesRunnerEnd - ObjectManager_activeProjectileSlots;
	ObjectManager_resetActiveProjectiles = FALSE;

	//SMS_debugPrintf("ObjectManager_numActiveProjectiles: %d\n", ObjectManager_numActiveProjectiles);
	//SMS_setBackdropColor(COLOR_DARK_GREEN);
}


void ObjectManager_processEnemyProjectileDeletes(void)
{

	if (!ObjectManager_resetActiveEnemyProjectiles)
		return;

	//SMS_setBackdropColor(COLOR_RED);
	//SMS_debugPrintf("rebuilding active enemy projectile list\n");

	GameObject** activeEnemyProjectilesRunner = ObjectManager_activeEnemyProjectileSlots;
	GameObject** activeEnemyProjectilesRunnerEnd = ObjectManager_activeEnemyProjectileSlots + ObjectManager_numActiveEnemyProjectiles;

	//SMS_debugPrintf("ObjectManager_numActiveEnemyProjectiles: %d\n", ObjectManager_numActiveEnemyProjectiles);

	// iteration 1
	// activeEnemyProjectilesRunner		->	[alive]
	//									[dead]
	// activeEnemyProjectilesRunnerEnd	->	[blah]
	//
	// iteration 2
	//									[alive]
	// activeEnemyProjectilesRunner		->	[dead]
	// activeEnemyProjectilesRunnerEnd	->	[blah]
	//
	// copy + back up activeEnemyProjectilesRunnerEnd
	//									[alive]
	// activeEnemyProjectilesRunner/End	->	[blah]
	//									[blah]
	// iteration 3
	//									[alive]
	// activeEnemyProjectilesRunnerEnd	->	[blah]
	// activeEnemyProjectilesRunner		->	[blah]
	//
	// Done

	// every time we encounter a dead object, copy the pointer to the
	// last active object to it. Also back up the activeEnemyProjectilesRunnerEnd by one.
	// When activeEnemyProjectilesRunner activeEnemyProjectilesRunnerEnd cross, then we're done.
	do
	{
		if (!(*activeEnemyProjectilesRunner)->alive)
		{
			activeEnemyProjectilesRunnerEnd--;
			(*activeEnemyProjectilesRunner) = (*activeEnemyProjectilesRunnerEnd);
		}

		activeEnemyProjectilesRunner++;
	} while (activeEnemyProjectilesRunner < activeEnemyProjectilesRunnerEnd);

	ObjectManager_numActiveEnemyProjectiles = activeEnemyProjectilesRunnerEnd - ObjectManager_activeEnemyProjectileSlots;
	ObjectManager_resetActiveEnemyProjectiles = FALSE;

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

	while (ObjectManager_numNewObjects)
	{
		//SMS_debugPrintf("Added new object to active list\n");
		ObjectManager_numNewObjects--;
		GameObject* object = ObjectManager_newObjects[ObjectManager_numNewObjects];
		object->alive = TRUE;

		switch (object->objectType)
		{
		case OBJECTTYPE_PROJECTILE:
			//SMS_debugPrintf("appended new projectile\n");
			ObjectManager_activeProjectileSlots[ObjectManager_numActiveProjectiles] = object;
			ObjectManager_numActiveProjectiles++;
			break;
		case OBJECTTYPE_ENEMY:
			//SMS_debugPrintf("appended new enemy\n");
			ObjectManager_activeEnemySlots[ObjectManager_numActiveEnemies] = object;
			ObjectManager_numActiveEnemies++;
			break;
		case OBJECTTYPE_EFFECT:
			//SMS_debugPrintf("appended new effect\n");
			ObjectManager_activeEffectSlots[ObjectManager_numActiveEffects] = object;
			ObjectManager_numActiveEffects++;
			break;
		case OBJECTTYPE_ENEMY_PROJECTILE:
			//SMS_debugPrintf("appended new enemy projectile\n");
			ObjectManager_activeEnemyProjectileSlots[ObjectManager_numActiveEnemyProjectiles] = object;
			ObjectManager_numActiveEnemyProjectiles++;
			break;
		}
	}
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


	//u8 counter;


	if (objectType == OBJECTTYPE_ENEMY)
	{
		//SMS_debugPrintf("Trying to add new enemy\n");

		if (ObjectManager_numActiveEnemies == NUM_ENEMY_SLOTS)
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
	// 3354/3354/3354.0
	// 2199/2333/2251.1
	// 2090/2224/2116.8

	//SMS_setBackdropColor(COLOR_BLUE);

	if (ObjectManager_numActiveEffects == NUM_EFFECT_SLOTS)
		return NULL;

	//SMS_debugPrintf("Added new effect\n");

	GameObject* gameObject = ObjectManager_effectSlots;
	while (gameObject->alive)
		gameObject++;

	gameObject->alive = OBJECTSTATE_PENDING;

	ObjectManager_newObjects[ObjectManager_numNewObjects] = gameObject;
	ObjectManager_numNewObjects++;

	const GameObjectTemplate* gameObjectTemplate = effectCreateInfo->gameObjectTemplate;

	memcpy(&gameObject->x, &effectCreateInfo->startX, 4);
	memcpy(&gameObject->health, &gameObjectTemplate->startHealth, sizeof(GameObjectTemplate));

	ResourceManager_SetupResource(gameObject, gameObjectTemplate->resourceInfo);

	gameObjectTemplate->initFunction(gameObject, (const CreateInfo*)effectCreateInfo);

	//SMS_setBackdropColor(COLOR_DARK_GREEN);

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

	// one 2654/2654/2654.0
	// max 391/2790/1868.2

	// one 2026/2026/2026.0 without sound

	// one 2042/2042/2042.0
	// max 156/2310/1745.2 without sound

	//SMS_setBackdropColor(COLOR_BLUE);


	if (ObjectManager_numActiveProjectiles == NUM_PROJECTILE_SLOTS)
		return NULL;

	GameObject* gameObject = ObjectManager_projectileSlots;
	while (gameObject->alive)
		gameObject++;

create:

	gameObject->alive = OBJECTSTATE_PENDING;

	ObjectManager_newObjects[ObjectManager_numNewObjects] = gameObject;
	ObjectManager_numNewObjects++;

	const GameObjectTemplate* gameObjectTemplate = createInfo->gameObjectTemplate;

	memcpy(&gameObject->x, &createInfo->startX, 4);
	memcpy(&gameObject->health, &gameObjectTemplate->startHealth, sizeof(GameObjectTemplate));

	ResourceManager_SetupResource(gameObject, gameObjectTemplate->resourceInfo);

	gameObjectTemplate->initFunction(gameObject, createInfo);

	//SMS_setBackdropColor(COLOR_DARK_GREEN);

	return gameObject;
}


GameObject* ObjectManager_CreateEnemyProjectile(const CreateInfo* createInfo)
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

	// one 2654/2654/2654.0
	// max 391/2790/1868.2

	// one 2026/2026/2026.0 without sound

	// one 2042/2042/2042.0
	// max 156/2310/1745.2 without sound

	//SMS_setBackdropColor(COLOR_BLUE);


	if (ObjectManager_numActiveEnemyProjectiles == NUM_ENEMY_PROJECTILE_SLOTS)
		return NULL;

	GameObject* gameObject = ObjectManager_enemyProjectileSlots;
	while (gameObject->alive)
		gameObject++;

create:

	gameObject->alive = OBJECTSTATE_PENDING;

	ObjectManager_newObjects[ObjectManager_numNewObjects] = gameObject;
	ObjectManager_numNewObjects++;

	const GameObjectTemplate* gameObjectTemplate = createInfo->gameObjectTemplate;

	memcpy(&gameObject->x, &createInfo->startX, 8);
	memcpy(&gameObject->health, &gameObjectTemplate->startHealth, sizeof(GameObjectTemplate));

	ResourceManager_SetupResource(gameObject, gameObjectTemplate->resourceInfo);

	gameObjectTemplate->initFunction(gameObject, createInfo);

	//SMS_setBackdropColor(COLOR_DARK_GREEN);

	return gameObject;
}

void ObjectManager_DestroyObject(GameObject* gameObject)
{
	gameObject->alive = FALSE;

	switch (gameObject->objectType)
	{
	case OBJECTTYPE_ENEMY: ObjectManager_resetActiveEnemies = TRUE; break;
	case OBJECTTYPE_EFFECT: ObjectManager_resetActiveEffects = TRUE; break;
	case OBJECTTYPE_PROJECTILE: ObjectManager_resetActiveProjectiles = TRUE; break;
	case OBJECTTYPE_ENEMY_PROJECTILE: ObjectManager_resetActiveEnemyProjectiles = TRUE; break;
	default:
		gameObject->Update = ObjectUtils_gameObjectDoNothing;
		gameObject->Draw = DrawUtils_drawNothing;

	}
}
