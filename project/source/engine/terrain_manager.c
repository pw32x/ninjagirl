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

void TerrainManager_Init_Strip(void)
{
	memset(TerrainManager_terrain, 0, sizeof(TerrainManager_terrain));

	//u8 currentRomBank = SMS_getROMBank();
	SMS_mapROMBank(MapManager_mapResourceInfo->bankNumber);

	for (u8 loop = 0; loop < TERRAIN_WIDTH; loop++)
	{
		TerrainManager_UpdateTerrain_Strip(loop);
	}

	//SMS_mapROMBank(currentRomBank);
}

void TerrainManager_UpdateTerrain(u16 mapColumnIndex)
{
	// 1496 cycles

	const u16* mapRunner = MapManager_mapData + mapColumnIndex;
	u8* terrainRunner = TerrainManager_terrain + (mapColumnIndex & TERRAIN_WIDTH_MINUS_ONE);

	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_WIDTH;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_WIDTH;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_WIDTH;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_WIDTH;

	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_WIDTH;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_WIDTH;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_WIDTH;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_WIDTH;

	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_WIDTH;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_WIDTH;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_WIDTH;
	*terrainRunner = (*mapRunner) >> TERRAIN_TYPE_SHIFT; mapRunner += MapManager_mapWidth; terrainRunner += TERRAIN_WIDTH;

	
}

void TerrainManager_UpdateTerrain_Strip(u16 mapColumnIndex)
{
	SMS_mapROMBank(MapManager_mapResourceInfo->bankNumber);

	//SMS_debugPrintf("column: %d, %u, %u \n", mapColumnIndex, MapManager_terrainMapStrips, MapManager_terrainMapHeight);

	// as the level always goes forward, the runner could just be offset every time.
	const u8* terrainStripRunner = MapManager_terrainMapStrips + (MapManager_terrainMapHeight * mapColumnIndex);

	u8* terrainRunner = TerrainManager_terrain + (mapColumnIndex & TERRAIN_WIDTH_MINUS_ONE);

	//1182
	*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner += TERRAIN_WIDTH; 
	*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner += TERRAIN_WIDTH; 
	*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner += TERRAIN_WIDTH; 
	*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner += TERRAIN_WIDTH; 
	*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner += TERRAIN_WIDTH; 
	*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner += TERRAIN_WIDTH; 
	*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner += TERRAIN_WIDTH; 
	*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner += TERRAIN_WIDTH; 
	*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner += TERRAIN_WIDTH; 
	*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner += TERRAIN_WIDTH; 
	*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner += TERRAIN_WIDTH; 
	*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d\n", *terrainRunner)*/;terrainRunner += TERRAIN_WIDTH; 

	// 973 if we worked with the terrain as YX and not XY
	//*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner ++; 
	//*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner ++; 
	//*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner ++; 
	//*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner ++; 
	//*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner ++; 
	//*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner ++; 
	//*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner ++; 
	//*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner ++; 
	//*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner ++; 
	//*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner ++; 
	//*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d, ", *terrainRunner)*/;terrainRunner ++; 
	//*terrainRunner = (*terrainStripRunner); terrainStripRunner++; /*SMS_debugPrintf("%d\n", *terrainRunner)*/;terrainRunner ++; 
	
}