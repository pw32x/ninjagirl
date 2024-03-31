#include "right_scroller.h"
#include "SMSlib.h"
#include "engine/scroll_manager.h"
#include "engine/scroll_utils.h"
#include "engine/map_types.h"
#include "engine/vdptile_manager.h"
#include "engine/base_defines.h"
#include "engine/terrain_manager.h"
#include "engine/map_manager.h"

#include <string.h>

#include <stdio.h>

void RightScroll_Update(GameObject* target);
void RightScroll_UpdateVDP(void);

void RightScroll_Update_Strip(GameObject* target);
void RightScroll_UpdateVDP_Strip(void);

u16 columnToUpdate;

u8 terrainColumnToUpdate;

GameObject* RightScroller_Init(const Map* map)
{
	//SMS_debugPrintf("RightScroller_Init\n");
	//
	//SMS_debugPrintf("strip map data\n");
	//SMS_debugPrintf("resource type: %d\n", MapManager_mapResourceInfo->resource->resourceType);
	//SMS_debugPrintf("bank: %d\n", MapManager_mapResourceInfo->bankNumber);
	//SMS_debugPrintf("resource: %u\n", (u16)MapManager_mapResourceInfo->resource);


	columnToUpdate = 0;
	terrainColumnToUpdate = 0;

	SMS_mapROMBank(MapManager_mapResourceInfo->bankNumber);

	if (MapManager_mapResourceInfo->resource->resourceType == STRIP_MAP_RESOURCE_TYPE)
	{
		ScrollManager_Update = RightScroll_Update_Strip;
		ScrollManager_UpdateVDP = RightScroll_UpdateVDP_Strip;

		ScrollUtils_InitTilemapStrip();
		TerrainManager_Init_Strip();

		ScrollManager_horizontalScrollLimit = (MapManager_mapWidth << 3) - SCREEN_WIDTH;

		ScrollManager_currentMapStrip = MapManager_mapData + (32 * MapManager_mapHeight);
		TerrainManager_currentTerrainMapStrip = MapManager_terrainMapStrips + (MapManager_terrainMapHeight * 15);
	}
	else
	{
		ScrollManager_Update = RightScroll_Update;
		ScrollManager_UpdateVDP = RightScroll_UpdateVDP;

		ScrollUtils_InitTilemap();
		TerrainManager_Init();

		ScrollManager_horizontalScrollLimit = (MapManager_mapWidth << 4) - SCREEN_WIDTH;
	}

	
	ScrollManager_updateMapVDP = FALSE;
	SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);

	ScrollManager_updateMapVDP = FALSE;

	return NULL;
}


extern s16 playerSpeedX;

#define SCROLL_START_POINT 100

void RightScroll_Update(GameObject* target)
{


	//SMS_setBackdropColor(COLOR_DARK_GREEN);

	//SMS_debugPrintf("playerSpeedX: %d\n", playerSpeedX);
	//
	//if (!playerSpeedX)
	//	return;



	//SMS_setBackdropColor(COLOR_DARK_GREEN);

	// tile map

	u8 scrollSpeedX = 0;

	u8 oldColumn = columnToUpdate;
	u8 oldTerrainColumnToUpdate = terrainColumnToUpdate;

	if (target->x > ScrollManager_horizontalScroll + SCROLL_START_POINT)
	{
		scrollSpeedX = target->x - (ScrollManager_horizontalScroll + SCROLL_START_POINT);
	}

	// here we move the vdp scrolling and logical map scrolling to the same speed
	ScrollManager_horizontalScroll += scrollSpeedX; // scrolling towards the right into the map

	//SMS_debugPrintf("scroll: %d\n", ScrollManager_horizontalScroll);
	//SMS_debugPrintf("scroll speed: %d\n", scrollSpeedX);

	if (ScrollManager_horizontalScroll >= ScrollManager_horizontalScrollLimit)
	{
		// some kind of limit
		scrollSpeedX = (ScrollManager_horizontalScrollLimit - 1) - ScrollManager_horizontalScroll;
		ScrollManager_horizontalScroll = ScrollManager_horizontalScrollLimit - 1;
	}

	ScrollManager_vdpHorizontalScroll = -(ScrollManager_horizontalScroll & 255); // vdp scrolls backwards in comparison

	columnToUpdate = ScrollManager_horizontalScroll >> 3;
	terrainColumnToUpdate = ScrollManager_horizontalScroll >> 4;

	u8 tileDiff = columnToUpdate - oldColumn;

	//u8 currentRomBank = SMS_getROMBank();
	//if (tileDiff) // when we hit a new column, prep a new column to display
	{
		// figure out the column to update
		ScrollUtils_mapColumnToBuild = columnToUpdate + 32; 
		ScrollUtils_buildColumn(ScrollManager_columnBuffer);

		ScrollManager_updateMapVDP = TRUE;
	}	

	// terrain

	//char output[255];	
	//sprintf(output, "%d, %d     ", terrainColumnToUpdate, terrainColumnToUpdate & 15);
	//SMS_printatXY(1, 0, output); 

	if (terrainColumnToUpdate - oldTerrainColumnToUpdate)
	{
		TerrainManager_UpdateTerrain_Strip(terrainColumnToUpdate + 15);
	}

	//SMS_mapROMBank(currentRomBank);


	//SMS_setBackdropColor(COLOR_RED);

	//SMS_setBackdropColor(COLOR_BLUE);
}


void RightScroll_Update_Strip(GameObject* target)
{
	// 2836
	// 2788 
	// 2691
	// 890

	//SMS_setBackdropColor(COLOR_DARK_GREEN);

	//SMS_debugPrintf("playerSpeedX: %d\n", playerSpeedX);
	//
	//if (!playerSpeedX)
	//	return;



	//SMS_setBackdropColor(COLOR_DARK_GREEN);

	// tile map

	//u8 scrollSpeedX = 0;

	u8 oldColumn = columnToUpdate;
	u8 oldTerrainColumnToUpdate = terrainColumnToUpdate;

	if (target->x > ScrollManager_horizontalScroll + SCROLL_START_POINT)
	{
		ScrollManager_horizontalScroll += target->x - (ScrollManager_horizontalScroll + SCROLL_START_POINT);
	}

	// here we move the vdp scrolling and logical map scrolling to the same speed
	// ScrollManager_horizontalScroll += scrollSpeedX; // scrolling towards the right into the map

	//SMS_debugPrintf("scroll: %d\n", ScrollManager_horizontalScroll);
	//SMS_debugPrintf("scroll speed: %d\n", scrollSpeedX);

	if (ScrollManager_horizontalScroll >= ScrollManager_horizontalScrollLimit)
	{
		// some kind of limit
		//scrollSpeedX = (ScrollManager_horizontalScrollLimit - 1) - ScrollManager_horizontalScroll;
		ScrollManager_horizontalScroll = ScrollManager_horizontalScrollLimit - 1;
	}

	ScrollManager_vdpHorizontalScroll = -(ScrollManager_horizontalScroll & 255); // vdp scrolls backwards in comparison

	columnToUpdate = ScrollManager_horizontalScroll >> 3;


	//u8 currentRomBank = SMS_getROMBank();
	if (columnToUpdate - oldColumn) // when we hit a new column, prep a new column to display
	{
		// move to the next column
		ScrollManager_currentMapStrip += MapManager_mapHeight;
		ScrollManager_updateMapVDP = TRUE;
	}	

	// terrain
	terrainColumnToUpdate = ScrollManager_horizontalScroll >> 4;

	//char output[255];	
	//sprintf(output, "%d, %d     ", terrainColumnToUpdate, terrainColumnToUpdate & 15);
	//SMS_printatXY(1, 0, output); 

	if (terrainColumnToUpdate - oldTerrainColumnToUpdate)
	{
		TerrainManager_currentTerrainMapStrip += MapManager_terrainMapHeight;
		TerrainManager_UpdateTerrain_Strip(terrainColumnToUpdate + 15);
	}

	//SMS_mapROMBank(currentRomBank);


	//SMS_setBackdropColor(COLOR_RED);

	//SMS_setBackdropColor(COLOR_BLUE);
}

void RightScroll_UpdateVDP(void)
{
	//SMS_setBackdropColor(COLOR_DARK_BLUE);

	SMS_setBGScrollX(ScrollManager_vdpHorizontalScroll);
	
	if (ScrollManager_updateMapVDP)
	{
		ScrollManager_updateMapVDP = FALSE;
		SMS_loadTileMapColumn(columnToUpdate & 31, 0, ScrollManager_columnBuffer, 26);
	}
	//SMS_setBackdropColor(COLOR_RED);
}

void RightScroll_UpdateVDP_Strip(void)
{
	//SMS_setBackdropColor(COLOR_DARK_BLUE);

	SMS_setBGScrollX(ScrollManager_vdpHorizontalScroll);

	if (ScrollManager_updateMapVDP)
	{
		SMS_mapROMBank(MapManager_mapResourceInfo->bankNumber);
		ScrollManager_updateMapVDP = FALSE;
		SMS_loadTileMapColumn(columnToUpdate & 31, 0, ScrollManager_currentMapStrip, 24);
	}
	//SMS_setBackdropColor(COLOR_RED);
}
