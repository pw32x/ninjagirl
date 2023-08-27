#ifndef OBJECT_MANAGER_INCLUDE_H
#define OBJECT_MANAGER_INCLUDE_H

#include "engine/spawn_types.h"
#include "engine/object_types.h"

#define OBJECTTYPE_PROJECTILE	0
#define OBJECTTYPE_ENEMY		1


void ObjectManager_Init(void);

void ObjectManager_Update(void);

GameObject* ObjectManager_GetAvailableSlot(u8 objectType);
void ObjectManager_DestroyObject(GameObject* gameObject);

extern GameObject ObjectManager_player;

// per-frame player screen position
extern s16 ObjectManager_playerLeft;
extern s16 ObjectManager_playerTop;
extern s16 ObjectManager_playerRight;
extern s16 ObjectManager_playerBottom;

void ObjectManagerUtils_updatePlayerScreenRect(void);

// when one object is being processed, these values are updated to perform
// drawing and collisions.
extern s16 ObjectManager_objectLeft;
extern s16 ObjectManager_objectTop;
extern s16 ObjectManager_objectRight;
extern s16 ObjectManager_objectBottom;

void ObjectManagerUtils_updateObjectScreenRect(GameObject* gameObject);

BOOL ObjectManagerUtils_collidesWithProjectiles(GameObject* gameObject);

#endif