#include "scroll_manager.h"
#include "SMSLib.h"
#include "map_types.h"

u16 ScrollManager_horizontalScroll = 0;
u8 ScrollManager_vdpHorizontalScroll = 0;

// hard-coded column when we need to show more of the map. Replace
// this with an actual larger map.
#define SCROLLMANAGER_COLUMNBUFFER_HEIGHT 24
u16 ScrollManager_columnBuffer[SCROLLMANAGER_COLUMNBUFFER_HEIGHT];

u8 ScrollManager_updateMap = FALSE;
u8 ScrollManager_speed = 0;

const Map* ScrollManager_backgroundMap;
const Tileset* ScrollManager_backgroundTileset;

void ScrollManager_InitTilemap(void);

void ScrollManager_Init(const Map* backgroundMap)
{
	ScrollManager_backgroundMap = backgroundMap;
	ScrollManager_backgroundTileset = backgroundMap->tileset;
	ScrollManager_updateMap = FALSE;
	SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);
	ScrollManager_InitTilemap();
}

void buildColumnOld(u16 tileColumn)
{
	// from the tile column, get the metatile from the level map
	u16 metatileColumn = (tileColumn >> 1) % ScrollManager_backgroundMap->mapWidth;

	// figure out which column of the metatile to get. Metatiles contain two tile columns.
	u8 metatileOffset = tileColumn & 1;

	u16* columnRunner = ScrollManager_columnBuffer;

	// for the height of a map column, fill the ScrollManager_columnBuffer
	for (u8 loop = 0; loop < ScrollManager_backgroundMap->mapHeight; loop++)
	{
		// get the index into the metatile loop-up table
		u16 metatile_index = (ScrollManager_backgroundMap->metatileMap[metatileColumn + (loop * ScrollManager_backgroundMap->mapWidth)] * 4) + metatileOffset;

		// set the first tile
		*columnRunner = ScrollManager_backgroundTileset->metatile_lut[metatile_index];
		columnRunner++;

		// set the second tile
		*columnRunner = ScrollManager_backgroundTileset->metatile_lut[metatile_index + 2];
		columnRunner++;
	}
}

void buildColumn(u16 tileColumn)
{
	u16 mapWidth = ScrollManager_backgroundMap->mapWidth;
	u16 mapHeight = ScrollManager_backgroundMap->mapHeight;

	// from the tile column, get the metatile from the level map
	u16 metatileColumn = (tileColumn >> 1) % mapWidth;

	const u16* metatileMapStart = ScrollManager_backgroundMap->metatileMap + metatileColumn;
	const u16* metatile_lut = ScrollManager_backgroundTileset->metatile_lut;



	// figure out which column of the metatile to get. Metatiles contain two tile columns.
	u8 metatileOffset = tileColumn & 1;

	u16* columnRunner = ScrollManager_columnBuffer;

	// for the height of a map column, fill the ScrollManager_columnBuffer
	u8 loop =  mapHeight;

	while (loop--)
	{
		// get the index into the metatile loop-up table
		u16 metatile_index = (*(metatileMapStart) << 2) + metatileOffset;

		metatileMapStart += mapWidth;

		// set the first tile
		*columnRunner = *(metatile_lut + metatile_index);
		columnRunner++;

		// set the second tile
		*columnRunner = *(metatile_lut + metatile_index + 2);
		columnRunner++;
	}
}

void ScrollManager_InitTilemap(void)
{
	// fill the map from the second column to the last.
	for (char loop = 1; loop < 32; loop++)
	{
		buildColumn(loop);
		SMS_loadTileMapColumn(loop, 0, ScrollManager_columnBuffer, SCROLLMANAGER_COLUMNBUFFER_HEIGHT);
	}

	// prep the next column to be visible where the first column is.
	// we do this because columns are only updated when we hit an 8 pixel
	// boundary when we scroll. At the start, we're already at the boundary.
	// We won't see it anyway.
	buildColumn(32);
	SMS_loadTileMapColumn(0, 0, ScrollManager_columnBuffer, SCROLLMANAGER_COLUMNBUFFER_HEIGHT);
}

void ScrollManager_Update(GameObject* gameObject)
{
	if (gameObject->x > ScrollManager_horizontalScroll + 128)
	{
		ScrollManager_speed = gameObject->x - (ScrollManager_horizontalScroll + 128);
	}
	else
	{
		ScrollManager_speed = 0;
	}

	// here we move the vdp scrolling and logical map scrolling to the same speed
	ScrollManager_horizontalScroll += ScrollManager_speed; // scrolling towards the right into the map
	ScrollManager_vdpHorizontalScroll -= ScrollManager_speed; // vdp scrolls backwards in comparison

	ScrollManager_horizontalScroll %= (ScrollManager_backgroundMap->mapWidth * 16); // clamp the scrolling to the pixel width of the map.

	if (ScrollManager_horizontalScroll % 8 == 0 && ScrollManager_speed) // when we hit a 8 pixel boundary, prep a new column to display
	{
		// figure out the column to update
		u16 tileColumn = (ScrollManager_horizontalScroll >> 3) + 32; 
		buildColumn(tileColumn);

		ScrollManager_updateMap = TRUE;
	}	
}

void ScrollManager_UpdateVDP(void)
{
	SMS_setBGScrollX(ScrollManager_vdpHorizontalScroll);

	if (ScrollManager_updateMap)
	{
		ScrollManager_updateMap = FALSE;
		u8 scrollMapColumn = ScrollManager_vdpHorizontalScroll >> 3;
		SMS_loadTileMapColumn((32 - scrollMapColumn) & 31, 0, ScrollManager_columnBuffer, 24);
	}
}