#include "scroll_utils.h"
#include "SMSLib.h"
#include "engine/map_types.h"
#include "engine/scroll_manager.h"
#include "engine/map_manager.h"

u16 ScrollUtils_mapColumnToBuild;

void ScrollUtils_buildColumn(u8* buffer)
{
	// from the tile column, get the metatile from the level map
	u16 metamapColumn = (ScrollUtils_mapColumnToBuild >> 1);

	const u16* mapStart = MapManager_mapData + metamapColumn;

	// figure out which column of the metatile to get. Metatiles contain two tile columns.
	u8 metatileOffset = ScrollUtils_mapColumnToBuild & 1;

	u16* columnRunner = buffer;

	// for the height of a map column, fill the buffer
	u8 loop =  MapManager_mapHeight;

	const u16* sum;
	u16 metatile_index;
	u8 tileset_index;
	const u16* metatileLut;
	u8 vdpLocation;
	u16 metatileMapItem;

#define FILL_COLUMN()\
metatileMapItem = *mapStart;\
tileset_index = (metatileMapItem >> 9) & SHORT_TILESET_INDEX_MASK;\
vdpLocation = MapManager_tilesetVdpLocations[tileset_index];\
metatileLut = MapManager_metatileLuts[tileset_index];\
metatile_index = ((metatileMapItem & BLOCK_MASK) << 2) + metatileOffset;\
mapStart += MapManager_mapWidth;\
sum = metatileLut + metatile_index;\
*columnRunner = *(sum) + vdpLocation;\
*(columnRunner + 1) = *(sum + 2) + vdpLocation;\
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
	u8 currentRomBank = SMS_getROMBank();
	SMS_mapROMBank(MapManager_mapResourceInfo->bankNumber);


	// fill the map from the second column to the last.
	for (char loop = 1; loop < 32; loop++)
	{
		ScrollUtils_mapColumnToBuild = loop;

		ScrollUtils_buildColumn(ScrollManager_columnBuffer);
		SMS_loadTileMapColumn(loop, 0, ScrollManager_columnBuffer, SCROLLMANAGER_BUFFER_HEIGHT);
	}

	// prep the next column to be visible where the first column is.
	// we do this because columns are only updated when we hit an 8 pixel
	// boundary when we scroll. At the start, we're already at the boundary.
	// We won't see it anyway.
	ScrollUtils_mapColumnToBuild = 32;
	ScrollUtils_buildColumn(ScrollManager_columnBuffer);
	SMS_loadTileMapColumn(0, 0, ScrollManager_columnBuffer, SCROLLMANAGER_BUFFER_HEIGHT);

	SMS_mapROMBank(currentRomBank);
}
