#include "object_manager_slots.h"
#include "object_manager_create.h"
#include <string.h>
#include "SMSlib.h"


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

// player projectiles
GameObject ObjectManager_projectileSlots[NUM_PROJECTILE_SLOTS];
u8 ObjectManager_numActiveProjectiles;
GameObject* ObjectManager_activeProjectileSlots[NUM_PROJECTILE_SLOTS];

void ObjectManager_InitSlots(void)
{
	ObjectManager_numActiveEnemies = 0;
	ObjectManager_numActiveEffects = 0;
	ObjectManager_numActiveProjectiles = 0;
}