#include "map_manager.h"

#include "engine/resource_manager.h"


u8 MapManager_numTilesets;
const u16* MapManager_metatileLuts[MAX_TILESETS];
const Tileset* MapManager_tilesets[MAX_TILESETS];
u16 MapManager_tilesetVdpLocations[MAX_TILESETS];
TilesetFunction MapManager_tilesetFunctions[MAX_TILESETS];
const Resource* MapManager_tilesetResources[MAX_TILESETS];

u16 MapManager_mapWidth;
u16 MapManager_mapHeight;

const u16* MapManager_mapData;


void MapManager_SetTilesetProperties_Command(SetTilesetProperties_Params* params)
{
	MapManager_tilesetFunctions[params->tilesetIndex] = params->tilesetFunction;
	MapManager_tilesetResources[params->tilesetIndex] = params->resource;

	if (params->resource)
		ResourceManager_LoadResource(params->resource);
}