#include "terrain_manager.h"

#include "SMSlib.h"

#include "engine/map_types.h"
#include "engine/map_manager.h"
#include "engine/scroll_manager.h"

#include <string.h>


u8 TerrainManager_terrain[TERRAIN_WIDTH * TERRAIN_HEIGHT]; // 192 bytes

void TerrainManager_Init(void)
{
	memset(TerrainManager_terrain, 0, sizeof(TerrainManager_terrain));

	u8 currentRomBank = SMS_getROMBank();
	SMS_mapROMBank(MapManager_mapResourceInfo->bankNumber);

	for (u8 loop = 0; loop < TERRAIN_WIDTH; loop++)
	{
		TerrainManager_UpdateTerrain(loop);
	}

	SMS_mapROMBank(currentRomBank);
}

void TerrainManager_UpdateTerrain(u16 mapColumnIndex)
{
	const u16* mapRunner = MapManager_mapData + mapColumnIndex;
	u8* terrainRunner = TerrainManager_terrain + (mapColumnIndex & TERRAIN_WIDTH_MINUS_ONE);

	for (u8 loop = 0; loop < TERRAIN_HEIGHT; loop++)
	{
		*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT;

		mapRunner += MapManager_mapWidth;
		terrainRunner += TERRAIN_WIDTH;
	}
}