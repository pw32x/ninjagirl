#include "scroll_utils.h"
#include "SMSLib.h"
#include "engine/map_types.h"
#include "engine/scroll_manager.h"

u16 ScrollUtils_mapColumnToBuild;

void ScrollUtils_buildColumn(void)
{
	// from the tile column, get the metatile from the level map
	u16 metamapColumn = (ScrollUtils_mapColumnToBuild >> 1);

	const u16* metatileMapStart = ScrollManager_metatileMap + metamapColumn;

	// figure out which column of the metatile to get. Metatiles contain two tile columns.
	u8 metatileOffset = ScrollUtils_mapColumnToBuild & 1;

	u16* columnRunner = ScrollManager_buffer;

	// for the height of a map column, fill the ScrollManager_buffer
	u8 loop =  ScrollManager_mapHeight;

	const u16* sum;
	u16 metatile_index;

#define FILL_COLUMN()\
metatile_index = (*(metatileMapStart) << 2) + metatileOffset;\
metatileMapStart += ScrollManager_mapWidth;\
sum = ScrollManager_metatileLut + metatile_index;\
*columnRunner = *(sum);\
*(columnRunner + 1) = *(sum + 2);\
columnRunner += 2

	FILL_COLUMN();
	FILL_COLUMN();
	FILL_COLUMN();
	FILL_COLUMN();
	FILL_COLUMN();
	FILL_COLUMN();
	FILL_COLUMN();
	FILL_COLUMN();
	FILL_COLUMN();
	FILL_COLUMN();
	FILL_COLUMN();
	FILL_COLUMN();
}

void ScrollUtils_InitTilemap(void)
{
	// fill the map from the second column to the last.
	for (char loop = 1; loop < 32; loop++)
	{
		ScrollUtils_mapColumnToBuild = loop;

		ScrollUtils_buildColumn();
		SMS_loadTileMapColumn(loop, 0, ScrollManager_buffer, SCROLLMANAGER_BUFFER_HEIGHT);
	}

	// prep the next column to be visible where the first column is.
	// we do this because columns are only updated when we hit an 8 pixel
	// boundary when we scroll. At the start, we're already at the boundary.
	// We won't see it anyway.
	ScrollUtils_mapColumnToBuild = 32;
	ScrollUtils_buildColumn();
	SMS_loadTileMapColumn(0, 0, ScrollManager_buffer, SCROLLMANAGER_BUFFER_HEIGHT);
}
