#ifndef OBJECT_MANAGER_SLOTS_INCLUDE_H
#define OBJECT_MANAGER_SLOTS_INCLUDE_H

#include "engine/object_types.h"

#define MAX_PROJECTILES 3
#define MAX_ENEMY_PROJECTILES 3
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
extern GameObject ObjectManager_projectiles[MAX_PROJECTILES];
extern u8 ObjectManager_numActiveProjectiles;
extern u8 ObjectManager_numPendingProjectiles;
extern GameObject* ObjectManager_activeProjectilesA[MAX_PROJECTILES];
extern GameObject* ObjectManager_activeProjectilesB[MAX_PROJECTILES];
extern GameObject** ObjectManager_currentActiveProjectiles;
extern GameObject** ObjectManager_pendingProjectiles;

// enemy projectiles
extern GameObject ObjectManager_enemyProjectiles[MAX_ENEMY_PROJECTILES];
extern u8 ObjectManager_numActiveEnemyProjectiles;
extern u8 ObjectManager_numPendingEnemyProjectiles;
extern GameObject* ObjectManager_activeEnemyProjectilesA[MAX_ENEMY_PROJECTILES];
extern GameObject* ObjectManager_activeEnemyProjectilesB[MAX_ENEMY_PROJECTILES];
extern GameObject** ObjectManager_currentActiveEnemyProjectiles;
extern GameObject** ObjectManager_pendingEnemyProjectiles;

extern GameObject ObjectManager_player;
extern GameObject ObjectManager_Item;

void ObjectManager_InitSlots(void);

#endif