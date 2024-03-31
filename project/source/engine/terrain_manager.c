#include "terrain_manager.h"

#include "SMSlib.h"

#include "engine/map_types.h"
#include "engine/map_manager.h"
#include "engine/scroll_manager.h"

#include <string.h>


u8 TerrainManager_terrain[TERRAIN_SIDE * TERRAIN_SIDE]; // 192 bytes
const u8* TerrainManager_currentTerrainMapStrip;

void TerrainManager_Init(void)
{
	memset(TerrainManager_terrain, 0, sizeof(TerrainManager_terrain));

	u8 currentRomBank = SMS_getROMBank();
	SMS_mapROMBank(MapManager_mapResourceInfo->bankNumber);

	for (u8 loop = 0; loop < TERRAIN_SIDE; loop++)
	{
		TerrainManager_UpdateTerrain(loop);
	}

	SMS_mapROMBank(currentRomBank);
}

void TerrainManager_Init_Strip(void)
{
	memset(TerrainManager_terrain, 0, sizeof(TerrainManager_terrain));

	//u8 currentRomBank = SMS_getROMBank();
	SMS_mapROMBank(MapManager_mapResourceInfo->bankNumber);
	TerrainManager_currentTerrainMapStrip = MapManager_terrainMapStrips;

	for (u8 loop = 0; loop < TERRAIN_SIDE; loop++)
	{
		TerrainManager_UpdateTerrain_Strip(loop);
		TerrainManager_currentTerrainMapStrip += MapManager_terrainMapHeight;
	}

	//SMS_mapROMBank(currentRomBank);
}

void TerrainManager_UpdateTerrain(u16 mapColumnIndex)
{
	// 1496 cycles

	const u16* mapRunner = MapManager_mapData + mapColumnIndex;
	u8* terrainRunner = TerrainManager_terrain + (mapColumnIndex & TERRAIN_SIDE_MINUS_ONE);

	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;

	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;

	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_SIDE;

	
}

void TerrainManager_UpdateTerrain_Strip(u8 mapColumnIndex)
{
	// 451
	SMS_mapROMBank(MapManager_mapResourceInfo->bankNumber);

	//SMS_debugPrintf("column: %d, %u, %u \n", mapColumnIndex, MapManager_terrainMapStrips, MapManager_terrainMapHeight);

	// as the level always goes forward, the runner could just be offset every time.
	const u8* terrainStripRunner = TerrainManager_currentTerrainMapStrip;

	u8* terrainRunner = TerrainManager_terrain + ((mapColumnIndex & TERRAIN_SIDE_MINUS_ONE) << TERRAIN_SIDE_SHIFT);

	
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
	*terrainRunner++ = *terrainStripRunner++; 
}