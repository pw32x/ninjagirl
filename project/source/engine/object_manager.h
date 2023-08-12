#ifndef OBJECT_MANAGER_INCLUDE_H
#define OBJECT_MANAGER_INCLUDE_H

#include "engine/spawn_types.h"
#include "engine/object_types.h"

void ObjectManager_Update(void);
void ObjectManager_Draw(void);

extern GameObject ObjectManager_player;

#endif