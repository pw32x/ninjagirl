#ifndef MAP_MANAGER_INCLUDE_H
#define MAP_MANAGER_INCLUDE_H

#include "engine/base_types.h"
#include "engine/map_types.h"
#include "engine/resource_types.h"

extern u8 MapManager_numTilesets;
extern const u16* MapManager_metatileLuts[MAX_TILESETS];
extern const Tileset* MapManager_tilesets[MAX_TILESETS];
extern u16 MapManager_tilesetVdpLocations[MAX_TILESETS];
extern const Resource* MapManager_tilesetResources[MAX_TILESETS];
extern TilesetFunction MapManager_tilesetFunctions[MAX_TILESETS];

extern u16 MapManager_mapWidth;
extern u16 MapManager_mapHeight;

extern const u16* MapManager_mapData;

#define GET_TILESET_INDEX(x, y) ((MapManager_mapData[(x) + ((y) * MapManager_mapWidth)] & TILESET_INDEX_MASK) >> TILESET_INDEX_SHIFT)

typedef struct
{
	u8 tilesetIndex;
	TilesetFunction tilesetFunction;
	const Resource* resource;
} SetTilesetProperties_Params;

void MapManager_SetTilesetProperties_Command(SetTilesetProperties_Params* params);

#endif