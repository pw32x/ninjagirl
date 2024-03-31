#include "map_manager.h"


#include "SMSlib.h"
#include "engine/resource_manager.h"
#include "engine/gameobject_template_types.h"

u8 MapManager_numTilesets;
const u16* MapManager_metatileLuts[MAX_TILESETS];

#define METATILE_LUT_DATA_SIZE 2048
u16 MapManager_metatileLutsData[METATILE_LUT_DATA_SIZE];
u16 MapManager_metatileLutsDataSize;

Tileset MapManager_tilesets[MAX_TILESETS];
u16 MapManager_tilesetVdpLocations[MAX_TILESETS];
TilesetFunction MapManager_tilesetFunctions[MAX_TILESETS];
const GameObjectTemplate* MapManager_tilesetGameObjectTemplates[MAX_TILESETS];

u16 MapManager_mapWidth;
u16 MapManager_mapHeight;

const u16* MapManager_mapData;
const ResourceInfo* MapManager_mapResourceInfo;

const u8* MapManager_terrainMapStrips;
u16 MapManager_terrainMapWidth;
u16 MapManager_terrainMapHeight;

void MapManager_SetTilesetProperties_Command(SetTilesetProperties_Params* params)
{
	MapManager_tilesetFunctions[params->tilesetIndex] = params->tilesetFunction;
	MapManager_tilesetGameObjectTemplates[params->tilesetIndex] = params->gameObjectTemplate;

	if (params->gameObjectTemplate->resourceInfo != NULL)
	{
		ResourceManager_LoadResource(params->gameObjectTemplate->resourceInfo);
	}
}