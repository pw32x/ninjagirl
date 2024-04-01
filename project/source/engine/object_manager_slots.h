#ifndef OBJECT_MANAGER_SLOTS_INCLUDE_H
#define OBJECT_MANAGER_SLOTS_INCLUDE_H

#include "engine/object_types.h"

#define NUM_PROJECTILE_SLOTS 3
#define NUM_ENEMY_PROJECTILE_SLOTS 3
#define NUM_ENEMY_SLOTS 8
#define NUM_EFFECT_SLOTS 8
#define NUM_EFFECT_SLOTS_MASK 0x7

extern GameObject ObjectManager_projectileSlots[NUM_PROJECTILE_SLOTS];
extern GameObject ObjectManager_enemyProjectileSlots[NUM_ENEMY_PROJECTILE_SLOTS];
extern GameObject ObjectManager_enemySlots[NUM_ENEMY_SLOTS];
extern GameObject ObjectManager_effectSlots[NUM_EFFECT_SLOTS];

extern GameObject ObjectManager_player;
extern GameObject ObjectManager_Item;

void ObjectManager_InitSlots(void);

#endif