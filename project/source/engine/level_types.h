#ifndef LEVEL_TYPES_INCLUDE_H
#define LEVEL_TYPES_INCLUDE_H

#include "engine/spawn_types.h"
#include "engine/map_types.h"

typedef struct
{
	void (*InitLevel)(void);
	const SpawnInfo* levelSpawns;
	const u16 levelSpawnsCount;
	const u8* backgroundPalette;
	const u8* spritePalette;
} Level;

#endif