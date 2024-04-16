#ifndef OBJECT_MANAGER_SLOTS_INCLUDE_H
#define OBJECT_MANAGER_SLOTS_INCLUDE_H

#include "engine/object_types.h"

#define NUM_PROJECTILE_SLOTS 3
#define NUM_ENEMY_PROJECTILE_SLOTS 3
#define NUM_ENEMY_SLOTS 8
#define NUM_EFFECT_SLOTS 8
#define NUM_EFFECT_SLOTS_MASK 0x7



// enemies
extern u8 ObjectManager_numActiveEnemies;
extern GameObject* ObjectManager_activeEnemySlots[NUM_ENEMY_SLOTS];
extern GameObject ObjectManager_enemySlots[NUM_ENEMY_SLOTS];

// effects
extern u8 ObjectManager_numActiveEffects;
extern GameObject* ObjectManager_activeEffectSlots[NUM_EFFECT_SLOTS];
extern GameObject ObjectManager_effectSlots[NUM_EFFECT_SLOTS];

// player projectiles
extern GameObject ObjectManager_projectileSlots[NUM_PROJECTILE_SLOTS];
extern u8 ObjectManager_numActiveProjectiles;
extern GameObject* ObjectManager_activeProjectileSlots[NUM_PROJECTILE_SLOTS];

// enemy projectile slots
extern GameObject ObjectManager_enemyProjectileSlots[NUM_ENEMY_PROJECTILE_SLOTS];
extern u8 ObjectManager_numActiveEnemyProjectiles;
extern GameObject* ObjectManager_activeEnemyProjectileSlots[NUM_ENEMY_PROJECTILE_SLOTS];

extern GameObject ObjectManager_player;
extern GameObject ObjectManager_Item;

void ObjectManager_InitSlots(void);

#endif