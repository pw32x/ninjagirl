#include "right_scroller.h"
#include "SMSlib.h"
#include "engine/scroll_manager.h"
#include "engine/scroll_utils.h"
#include "engine/map_types.h"
#include "engine/vdptile_manager.h"
#include "engine/base_defines.h"

void RightScroll_Update(GameObject* gameObject);
void RightScroll_UpdateVDP(void);

GameObject* RightScroller_Create(const SpawnInfo* spawnInfo)
{
	ScrollManager_Update = RightScroll_Update;
	ScrollManager_UpdateVDP = RightScroll_UpdateVDP;
	
	ScrollManager_backgroundMap = (const Map*)spawnInfo->payload;
	ScrollManager_backgroundTileset = ScrollManager_backgroundMap->tileset;

	ScrollManager_mapWidth = ScrollManager_backgroundMap->mapWidth;
	ScrollManager_mapWidthLimit = (ScrollManager_mapWidth << 4) - SCREEN_WIDTH;
	ScrollManager_mapHeight = ScrollManager_backgroundMap->mapHeight;

	ScrollManager_metatileMap = ScrollManager_backgroundMap->metatileMap;
	ScrollManager_metatileLut = ScrollManager_backgroundTileset->metatile_lut;

	ScrollManager_updateMapVDP = FALSE;
	SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);

	ScrollManager_tilesetVdpLocation = VDPTileManager_LoadBackgroundTileset(ScrollManager_backgroundTileset->tiles, ScrollManager_backgroundTileset->numTiles);

	ScrollUtils_InitTilemap();

	return NULL;
}

void RightScroll_Update(GameObject* gameObject)
{
	SMS_setBackdropColor(COLOR_DARK_GREEN);

	ScrollManager_speedX = 0;

	if (gameObject->x > ScrollManager_horizontalScroll + 128)
	{
		ScrollManager_speedX = gameObject->x - (ScrollManager_horizontalScroll + 128);
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

	if (ScrollManager_horizontalScroll % 8 == 0 && ScrollManager_speedX) // when we hit a 8 pixel boundary, prep a new column to display
	{
		// figure out the column to update
		ScrollUtils_mapColumnToBuild = (ScrollManager_horizontalScroll >> 3) + 32; 
		ScrollUtils_buildColumn();

		ScrollManager_updateMapVDP = TRUE;
	}	

	SMS_setBackdropColor(COLOR_RED);
}

void RightScroll_UpdateVDP(void)
{
	SMS_setBackdropColor(COLOR_DARK_BLUE);

	SMS_setBGScrollX(ScrollManager_vdpHorizontalScroll);
	
	if (ScrollManager_updateMapVDP)
	{
		ScrollManager_updateMapVDP = FALSE;
		u8 scrollMapColumn = ScrollManager_vdpHorizontalScroll >> 3;
		SMS_loadTileMapColumn((32 - scrollMapColumn) & 31, 0, ScrollManager_buffer, 24);
	}

	SMS_setBackdropColor(COLOR_DARK_GREY);
}