#ifndef SPAWN_TYPES_INCLUDE_H
#define SPAWN_TYPES_INCLUDE_H

#include "engine/types.h"
#include "engine/animation_types.h"
#include "engine/object_types.h"

typedef struct spawn_info
{
	s16 startx;
	s16 starty;
	const Animation* animation;
	u8* animationVdpTileIndexPtr;
	GameObject* (*Object_Create)(const struct spawn_info* spawnInfo);
} SpawnInfo;

#endif