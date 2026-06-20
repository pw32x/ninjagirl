#ifndef OBJECT_MANAGER_SLOTS_INCLUDE_H
#define OBJECT_MANAGER_SLOTS_INCLUDE_H

#include "engine/object_types.h"

#define NUM_PROJECTILES 3
#define NUM_ENEMY_PROJECTILE_SLOTS 3
#define NUM_ENEMY_SLOTS 4
#define NUM_EFFECT_SLOTS 4
#define NUM_EFFECT_SLOTS_MASK 0x3



// enemies
extern u8 ObjectManager_numActiveEnemies;
extern GameObject* ObjectManager_activeEnemySlots[NUM_ENEMY_SLOTS];
extern GameObject ObjectManager_enemySlots[NUM_ENEMY_SLOTS];

// effects
extern u8 ObjectManager_numActiveEffects;
extern GameObject* ObjectManager_activeEffectSlots[NUM_EFFECT_SLOTS];
extern GameObject ObjectManager_effectSlots[NUM_EFFECT_SLOTS];

// player projectiles
extern GameObject ObjectManager_projectiles[NUM_PROJECTILES];
extern u8 ObjectManager_numActiveProjectiles;
extern u8 ObjectManager_numPendingProjectiles;
extern GameObject* ObjectManager_activeProjectilesA[NUM_PROJECTILES];
extern GameObject* ObjectManager_activeProjectilesB[NUM_PROJECTILES];
extern GameObject** ObjectManager_currentActiveProjectiles;
extern GameObject** ObjectManager_pendingProjectileSlots;

// enemy projectile slots
extern GameObject ObjectManager_enemyProjectileSlots[NUM_ENEMY_PROJECTILE_SLOTS];
extern u8 ObjectManager_numActiveEnemyProjectiles;
extern GameObject* ObjectManager_activeEnemyProjectileSlots[NUM_ENEMY_PROJECTILE_SLOTS];

/*
// enemy projectile slots
extern GameObject ObjectManager_enemyProjectileSlots[NUM_ENEMY_PROJECTILE_SLOTS];
extern u8 ObjectManager_numActiveEnemyProjectiles;
extern u8 ObjectManager_numPendingEnemyProjectiles;
extern GameObject* ObjectManager_activeEnemyProjectileSlots1[NUM_PROJECTILES];
extern GameObject* ObjectManager_activeEnemyProjectileSlots2[NUM_PROJECTILES];
extern GameObject** ObjectManager_currentActiveEnemyProjectileSlots;
extern GameObject** ObjectManager_pendingEnemyProjectileSlots;
*/

extern GameObject ObjectManager_player;
extern GameObject ObjectManager_Item;

void ObjectManager_InitSlots(void);

#endif