#include "right_scroller.h"
#include "SMSlib.h"
#include "engine/scroll_manager.h"
#include "engine/scroll_utils.h"
#include "engine/map_types.h"
#include "engine/vdptile_manager.h"
#include "engine/base_defines.h"

#include <stdio.h>

void RightScroll_Update(GameObject* target);
void RightScroll_UpdateVDP(void);

u16 columnToUpdate;

GameObject* RightScroller_Create(const Map* map)
{
	columnToUpdate = 0;

	ScrollManager_Update = RightScroll_Update;
	ScrollManager_UpdateVDP = RightScroll_UpdateVDP;
	
	ScrollManager_backgroundMap = map;
	ScrollManager_backgroundTileset = ScrollManager_backgroundMap->tileset;

	ScrollManager_mapWidth = ScrollManager_backgroundMap->mapWidth;
	ScrollManager_mapWidthLimit = (ScrollManager_mapWidth << 4) - SCREEN_WIDTH;
	ScrollManager_mapHeight = ScrollManager_backgroundMap->mapHeight;

	ScrollManager_metatileMap = ScrollManager_backgroundMap->metatileMap;
	ScrollManager_metatileLut = ScrollManager_backgroundTileset->metatile_lut;
	ScrollManager_terrainMap = ScrollManager_backgroundMap->terrainMap;

	ScrollManager_updateMapVDP = FALSE;
	SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);

	ScrollManager_tilesetVdpLocation = *ScrollManager_backgroundTileset->vdpLocation;

	ScrollUtils_InitTilemap();

	ScrollManager_updateMapVDP = FALSE;

	return NULL;
}


extern s16 playerSpeedX;

void RightScroll_Update(GameObject* target)
{
	if (!playerSpeedX)
		return;

	//SMS_setBackdropColor(COLOR_DARK_GREEN);

	ScrollManager_speedX = 0;

	u8 oldColumn = columnToUpdate;

	if (target->x > ScrollManager_horizontalScroll + HALF_SCREEN_WIDTH)
	{
		ScrollManager_speedX = target->x - (ScrollManager_horizontalScroll + HALF_SCREEN_WIDTH);
	}

	// here we move the vdp scrolling and logical map scrolling to the same speed
	ScrollManager_horizontalScroll += ScrollManager_speedX; // scrolling towards the right into the map

	if (ScrollManager_horizontalScroll >= ScrollManager_mapWidthLimit)
	{
		// some kind of limit
		ScrollManager_speedX = (ScrollManager_mapWidthLimit - 1) - ScrollManager_horizontalScroll;
		ScrollManager_horizontalScroll = ScrollManager_mapWidthLimit - 1;
	}

	ScrollManager_vdpHorizontalScroll = -(ScrollManager_horizontalScroll & 255); // vdp scrolls backwards in comparison

	columnToUpdate = ScrollManager_horizontalScroll >> 3;

	u8 diff = columnToUpdate - oldColumn;

	if (diff) // when we hit a new column, prep a new column to display
	{
		// figure out the column to update
		ScrollUtils_mapColumnToBuild = columnToUpdate + 32; 
		ScrollUtils_buildColumn(ScrollManager_columnBuffer);

		ScrollManager_updateMapVDP = TRUE;
	}	


	//char output[255];	
	//sprintf(output, "%u %u    ", oldColumn, newColumn);
	//SMS_printatXY(28, 0, output); 
	

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