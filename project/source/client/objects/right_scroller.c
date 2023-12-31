#include "right_scroller.h"
#include "SMSlib.h"
#include "engine/scroll_manager.h"
#include "engine/scroll_utils.h"
#include "engine/map_types.h"
#include "engine/vdptile_manager.h"
#include "engine/base_defines.h"
#include "engine/terrain_manager.h"
#include "engine/map_manager.h"

#include <stdio.h>

void RightScroll_Update(GameObject* target);
void RightScroll_UpdateVDP(void);

u16 columnToUpdate;

u8 terrainColumnToUpdate;

GameObject* RightScroller_Init(const Map* map)
{
	columnToUpdate = 0;
	terrainColumnToUpdate = 0;

	ScrollManager_Update = RightScroll_Update;
	ScrollManager_UpdateVDP = RightScroll_UpdateVDP;

	ScrollManager_horizontalScrollLimit = (MapManager_mapWidth << 4) - SCREEN_WIDTH;

	ScrollManager_updateMapVDP = FALSE;
	SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);

	ScrollUtils_InitTilemap();
	TerrainManager_Init();

	ScrollManager_updateMapVDP = FALSE;

	return NULL;
}


extern s16 playerSpeedX;

void RightScroll_Update(GameObject* target)
{
	if (!playerSpeedX)
		return;

	//SMS_setBackdropColor(COLOR_DARK_GREEN);

	// tile map

	ScrollManager_speedX = 0;

	u8 oldColumn = columnToUpdate;
	u8 oldTerrainColumnToUpdate = terrainColumnToUpdate;

	if (target->x > ScrollManager_horizontalScroll + HALF_SCREEN_WIDTH)
	{
		ScrollManager_speedX = target->x - (ScrollManager_horizontalScroll + HALF_SCREEN_WIDTH);
	}

	// here we move the vdp scrolling and logical map scrolling to the same speed
	ScrollManager_horizontalScroll += ScrollManager_speedX; // scrolling towards the right into the map

	if (ScrollManager_horizontalScroll >= ScrollManager_horizontalScrollLimit)
	{
		// some kind of limit
		ScrollManager_speedX = (ScrollManager_horizontalScrollLimit - 1) - ScrollManager_horizontalScroll;
		ScrollManager_horizontalScroll = ScrollManager_horizontalScrollLimit - 1;
	}

	ScrollManager_vdpHorizontalScroll = -(ScrollManager_horizontalScroll & 255); // vdp scrolls backwards in comparison

	columnToUpdate = ScrollManager_horizontalScroll >> 3;
	terrainColumnToUpdate = ScrollManager_horizontalScroll >> 4;

	u8 tileDiff = columnToUpdate - oldColumn;

	u8 currentRomBank = SMS_getROMBank();
	SMS_mapROMBank(MapManager_mapResourceInfo->bankNumber);

	if (tileDiff) // when we hit a new column, prep a new column to display
	{
		// figure out the column to update
		ScrollUtils_mapColumnToBuild = columnToUpdate + 32; 
		ScrollUtils_buildColumn(ScrollManager_columnBuffer);

		ScrollManager_updateMapVDP = TRUE;
	}	

	// terrain

	u8 terrainDiff = terrainColumnToUpdate - oldTerrainColumnToUpdate;


	//char output[255];	
	//sprintf(output, "%d, %d     ", terrainColumnToUpdate, terrainColumnToUpdate & 15);
	//SMS_printatXY(1, 0, output); 

	if (terrainDiff)
	{
		TerrainManager_UpdateTerrain(terrainColumnToUpdate + 15);
	}

	SMS_mapROMBank(currentRomBank);

	//SMS_setBackdropColor(COLOR_RED);
}

void RightScroll_UpdateVDP(void)
{
	SMS_setBackdropColor(COLOR_DARK_BLUE);

	SMS_setBGScrollX(ScrollManager_vdpHorizontalScroll);
	
	if (ScrollManager_updateMapVDP)
	{
		ScrollManager_updateMapVDP = FALSE;
		SMS_loadTileMapColumn(columnToUpdate & 31, 0, ScrollManager_columnBuffer, 24);
	}
}