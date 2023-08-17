#include "scroll_utils.h"
#include "SMSLib.h"
#include "engine/map_types.h"
#include "engine/scroll_manager.h"

void ScrollUtils_buildColumn(u16 mapColumn)
{
	u16 mapWidth = ScrollManager_backgroundMap->mapWidth;
	u16 mapHeight = ScrollManager_backgroundMap->mapHeight;

	// from the tile column, get the metatile from the level map
	u16 metamapColumn = (mapColumn >> 1) % mapWidth;

	const u16* metatileMapStart = ScrollManager_backgroundMap->metatileMap + metamapColumn;
	const u16* metatile_lut = ScrollManager_backgroundTileset->metatile_lut;

	// figure out which column of the metatile to get. Metatiles contain two tile columns.
	u8 metatileOffset = mapColumn & 1;

	u16* columnRunner = ScrollManager_buffer;

	// for the height of a map column, fill the ScrollManager_buffer
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

void ScrollUtils_InitTilemap(void)
{
	// fill the map from the second column to the last.
	for (char loop = 1; loop < 32; loop++)
	{
		ScrollUtils_buildColumn(loop);
		SMS_loadTileMapColumn(loop, 0, ScrollManager_buffer, SCROLLMANAGER_BUFFER_HEIGHT);
	}

	// prep the next column to be visible where the first column is.
	// we do this because columns are only updated when we hit an 8 pixel
	// boundary when we scroll. At the start, we're already at the boundary.
	// We won't see it anyway.
	ScrollUtils_buildColumn(32);
	SMS_loadTileMapColumn(0, 0, ScrollManager_buffer, SCROLLMANAGER_BUFFER_HEIGHT);
}
