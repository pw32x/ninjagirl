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

u8 ObjectManager_resetActiveEnemies;
u8 ObjectManager_resetActiveEffects;
u8 ObjectManager_resetActiveProjectiles;
u8 ObjectManager_resetActiveEnemyProjectiles;

void ObjectManager_InitCreate(void)
{
	ObjectManager_objectId = 0;
	ObjectManager_resetActiveEnemies = FALSE;
	ObjectManager_resetActiveEffects = FALSE;
	ObjectManager_resetActiveProjectiles = FALSE;
	ObjectManager_resetActiveEnemyProjectiles = FALSE;
}

/*
GameObject* ObjectManager_CreateObject(u8 objectType)
{
	//MSG("ObjectManager_CreateObject\n");

	GameObject* objectSlotRunner = ObjectManager_enemieslots;
	u8 counter = MAX_ENEMIES;

	if (objectType == OBJECTTYPE_ITEM)
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
*/

void ObjectManager_refreshActiveEnemies(void)
{
	if (!ObjectManager_resetActiveEnemies)
		return;

	GameObject** activeEnemiesRunner = ObjectManager_currentActiveEnemies;
	GameObject** activeEnemiesRunnerEnd = ObjectManager_currentActiveEnemies + ObjectManager_numActiveEnemies;

	GameObject** ObjectManager_pendingEnemiesRunner = ObjectManager_pendingEnemies + ObjectManager_numPendingEnemies;

	// Copy the alive objects to the pending list. Then swap
	// the pointer to the current and pending lists.

	while (activeEnemiesRunner != activeEnemiesRunnerEnd)
	{
		if ((*activeEnemiesRunner)->alive)
		{
			*ObjectManager_pendingEnemiesRunner = *activeEnemiesRunner;
			ObjectManager_pendingEnemiesRunner++;
		}

		activeEnemiesRunner++;
	};

	ObjectManager_numActiveEnemies = ObjectManager_pendingEnemiesRunner - ObjectManager_pendingEnemies;

	ObjectManager_resetActiveEnemies = FALSE;
	ObjectManager_numPendingEnemies = 0;

	if (ObjectManager_currentActiveEnemies == ObjectManager_activeEnemiesA)
	{
		ObjectManager_currentActiveEnemies = ObjectManager_activeEnemiesB;
		ObjectManager_pendingEnemies = ObjectManager_activeEnemiesA;
	}
	else
	{
		ObjectManager_currentActiveEnemies = ObjectManager_activeEnemiesA;
		ObjectManager_pendingEnemies = ObjectManager_activeEnemiesB;
	}
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

GameObject* FindFreeGameObject(u8 objectType)
{
	MSG("FindFreeGameObject\n");
	// 108/738/481.1

	if (objectType == 	OBJECTTYPE_COMMANDRUNNER)
	{
		return &CommandManager_commandRunnerObject;
	}

	if (objectType == OBJECTTYPE_ITEM)
	{
		ObjectManager_Item.alive = TRUE;
		return &ObjectManager_Item;
	}

	return NULL;
}


GameObject* ObjectManager_CreateCommandRunner(const CreateInfo* createInfo)
{
	const GameObjectTemplate* gameObjectTemplate = createInfo->gameObjectTemplate;
	u8 objectType = gameObjectTemplate->objectType;

	GameObject* gameObject = &CommandManager_commandRunnerObject;

	gameObject->objectId = ObjectManager_objectId++;

	memcpy(&gameObject->x, &createInfo->startX, 4);
	memcpy(&gameObject->health, &gameObjectTemplate->startHealth, sizeof(GameObjectTemplate));

	if (gameObjectTemplate->resourceInfo != NULL)
		ResourceManager_SetupResource(gameObject, gameObjectTemplate->resourceInfo);

	gameObjectTemplate->initFunction(gameObject, createInfo);

	return gameObject;
}


GameObject* ObjectManager_CreatePlayer(const CreateInfo* createInfo)
{
	const GameObjectTemplate* gameObjectTemplate = createInfo->gameObjectTemplate;
	u8 objectType = gameObjectTemplate->objectType;

	GameObject* gameObject = &ObjectManager_player;

	gameObject->objectId = ObjectManager_objectId++;

	memcpy(&gameObject->x, &createInfo->startX, 4);
	memcpy(&gameObject->health, &gameObjectTemplate->startHealth, sizeof(GameObjectTemplate));

	if (gameObjectTemplate->resourceInfo != NULL)
		ResourceManager_SetupResource(gameObject, gameObjectTemplate->resourceInfo);

	gameObjectTemplate->initFunction(gameObject, createInfo);

	return gameObject; 

}

GameObject* ObjectManager_CreateEnemy(const CreateInfo* createInfo)
{
	// Be careful not create more objects than active slots.
	if (ObjectManager_numActiveEnemies == MAX_ENEMIES ||
		ObjectManager_numPendingEnemies == MAX_ENEMIES)
	{
		return NULL;
	}

	GameObject* gameObject = ObjectManager_enemies;
	while (gameObject->alive)
		gameObject++;

	gameObject->alive = TRUE;

	ObjectManager_pendingEnemies[ObjectManager_numPendingEnemies] = gameObject;
	ObjectManager_numPendingEnemies++;

	const GameObjectTemplate* gameObjectTemplate = createInfo->gameObjectTemplate;

	memcpy(&gameObject->x, &createInfo->startX, 4);
	memcpy(&gameObject->health, &gameObjectTemplate->startHealth, sizeof(GameObjectTemplate));

	ResourceManager_SetupResource(gameObject, gameObjectTemplate->resourceInfo);

	gameObjectTemplate->initFunction(gameObject, createInfo);

	ObjectManager_resetActiveEnemies = TRUE;

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

GameObject* ObjectManager_CreateItem(const CreateInfo* createInfo)
{

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
