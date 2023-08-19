#ifndef OBJECT_MANAGER_INCLUDE_H
#define OBJECT_MANAGER_INCLUDE_H

#include "engine/spawn_types.h"
#include "engine/object_types.h"

void ObjectManager_Init(void);

void ObjectManager_Update(void);
void ObjectManager_Draw(void);

GameObject* ObjectManager_GetAvailableSlot(void);

extern GameObject ObjectManager_player;

#endif