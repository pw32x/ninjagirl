#ifndef SPAWN_TYPES_INCLUDE_H
#define SPAWN_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "engine/animation_types.h"
#include "engine/map_types.h"
#include "engine/object_types.h"

typedef struct spawn_info
{
	s16 startX;
	s16 startY;
	const void* payload;
	u32 additionalPayload;
	GameObject* (*Object_Create)(const struct spawn_info* spawnInfo);
} SpawnInfo;

#endif