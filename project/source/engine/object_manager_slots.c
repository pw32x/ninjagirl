#include "object_manager_slots.h"
#include "object_manager_create.h"
#include <string.h>

GameObject ObjectManager_projectileSlots[NUM_PROJECTILE_SLOTS];
GameObject ObjectManager_enemyProjectileSlots[NUM_ENEMY_PROJECTILE_SLOTS];



GameObject ObjectManager_player;
GameObject ObjectManager_Item;

// enemies
GameObject ObjectManager_enemySlots[NUM_ENEMY_SLOTS];
u8 ObjectManager_numActiveEnemies;
GameObject* ObjectManager_activeEnemySlots[NUM_ENEMY_SLOTS];

// effects
GameObject ObjectManager_effectSlots[NUM_EFFECT_SLOTS];
u8 ObjectManager_numActiveEffects;
GameObject* ObjectManager_activeEffectSlots[NUM_EFFECT_SLOTS];

void ObjectManager_InitSlots(void)
{
	ObjectManager_numActiveEnemies = 0;
	ObjectManager_numActiveEffects = 0;

	memset(ObjectManager_projectileSlots, 0, sizeof(ObjectManager_projectileSlots));
	memset(ObjectManager_enemyProjectileSlots, 0, sizeof(ObjectManager_enemyProjectileSlots));
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

	objectSlotRunner = ObjectManager_effectSlots;
	counter = NUM_EFFECT_SLOTS;

	while (counter--)
	{
		ObjectManager_DestroyObject(objectSlotRunner);
		objectSlotRunner++;
	}

	ObjectManager_DestroyObject(&ObjectManager_Item);
}