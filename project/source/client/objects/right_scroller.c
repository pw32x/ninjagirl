#include "right_scroller.h"
#include "SMSlib.h"
#include "engine/scroll_manager.h"
#include "engine/scroll_utils.h"
#include "engine/map_types.h"
#include "engine/vdptile_manager.h"

void RightScroll_Update(GameObject* gameObject);
void RightScroll_UpdateVDP(void);

void RightScroller_Create(const SpawnInfo* spawnInfo)
{
	ScrollManager_Update = RightScroll_Update;
	ScrollManager_UpdateVDP = RightScroll_UpdateVDP;
	
	ScrollManager_backgroundMap = (const Map*)spawnInfo->payload;
	ScrollManager_backgroundTileset = ScrollManager_backgroundMap->tileset;
	ScrollManager_updateMapVDP = FALSE;
	SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);

	VDPTileManager_LoadBackgroundTileset(ScrollManager_backgroundTileset);

	ScrollUtils_InitTilemap();
}

void RightScroll_Update(GameObject* gameObject)
{

	if (gameObject->x > ScrollManager_horizontalScroll + 128)
	{
		ScrollManager_speedX = gameObject->x - (ScrollManager_horizontalScroll + 128);
	}
	else
	{
		ScrollManager_speedX = 0;
	}

	// here we move the vdp scrolling and logical map scrolling to the same speed
	ScrollManager_horizontalScroll += ScrollManager_speedX; // scrolling towards the right into the map
	ScrollManager_vdpHorizontalScroll -= ScrollManager_speedX; // vdp scrolls backwards in comparison

	ScrollManager_horizontalScroll %= (ScrollManager_backgroundMap->mapWidth * 16); // clamp the scrolling to the pixel width of the map.

	if (ScrollManager_horizontalScroll % 8 == 0 && ScrollManager_speedX) // when we hit a 8 pixel boundary, prep a new column to display
	{
		// figure out the column to update
		u16 tileColumn = (ScrollManager_horizontalScroll >> 3) + 32; 
		ScrollUtils_buildColumn(tileColumn);

		ScrollManager_updateMapVDP = TRUE;
	}	

}

void RightScroll_UpdateVDP(void)
{
	SMS_setBGScrollX(ScrollManager_vdpHorizontalScroll);
	
	if (ScrollManager_updateMapVDP)
	{
		ScrollManager_updateMapVDP = FALSE;
		u8 scrollMapColumn = ScrollManager_vdpHorizontalScroll >> 3;
		SMS_loadTileMapColumn((32 - scrollMapColumn) & 31, 0, ScrollManager_buffer, 24);
	}
}