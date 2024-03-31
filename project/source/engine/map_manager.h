#ifndef MAP_MANAGER_INCLUDE_H
#define MAP_MANAGER_INCLUDE_H

#include "engine/base_types.h"
#include "engine/map_types.h"
#include "engine/gameobject_template_types.h"

extern u8 MapManager_numTilesets;
extern const u16* MapManager_metatileLuts[MAX_TILESETS];

#define METATILE_LUT_DATA_SIZE 2048
extern u16 MapManager_metatileLutsData[METATILE_LUT_DATA_SIZE];

extern u16 MapManager_metatileLutsDataSize;

extern Tileset MapManager_tilesets[MAX_TILESETS];
extern u16 MapManager_tilesetVdpLocations[MAX_TILESETS];
extern const GameObjectTemplate* MapManager_tilesetGameObjectTemplates[MAX_TILESETS];
extern TilesetFunction MapManager_tilesetFunctions[MAX_TILESETS];

extern u16 MapManager_mapWidth;
extern u16 MapManager_mapHeight;

extern const u16* MapManager_mapData;

extern const u8* MapManager_terrainMapStrips;
extern u16 MapManager_terrainMapWidth;
extern u16 MapManager_terrainMapHeight;

extern const ResourceInfo* MapManager_mapResourceInfo;

#define GET_TILESET_INDEX(x, y) ((MapManager_mapData[(x) + ((y) * MapManager_mapWidth)] & TILESET_INDEX_MASK) >> TILESET_INDEX_SHIFT)

typedef struct
{
	u8 tilesetIndex;
	TilesetFunction tilesetFunction;
	const GameObjectTemplate* gameObjectTemplate;
} SetTilesetProperties_Params;


// [COMMAND "MapManager_SetTilesetProperties_Command" SetTilesetProperties_Params]
void MapManager_SetTilesetProperties_Command(SetTilesetProperties_Params* params);

#endif