#include "scroll_utils.h"
#include "SMSLib.h"
#include "engine/map_types.h"
#include "engine/scroll_manager.h"
#include "engine/map_manager.h"

u16 ScrollUtils_mapColumnToBuild;

void ScrollUtils_buildColumn(u8* buffer)
{
	SMS_mapROMBank(MapManager_mapResourceInfo->bankNumber);

	// from the tile column, get the metatile from the level map
	u16 metamapColumn = (ScrollUtils_mapColumnToBuild >> 1);

	const u16* mapStart = MapManager_mapData + metamapColumn;

	// figure out which column of the metatile to get. Metatiles contain two tile columns.
	u8 metatileOffset = ScrollUtils_mapColumnToBuild & 1;

	u16* columnRunner = buffer;

	const u16* sum;
	u16 metatile_index;

	const u16* metatileLut = MapManager_metatileLuts[0];
	u16 vdpLocation = MapManager_tilesetVdpLocations[0];

#define FILL_COLUMN()\
metatile_index = ((*mapStart & BLOCK_MASK) << 2) + metatileOffset;\
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
		SMS_loadTileMapColumn(loop, 0, ScrollManager_columnBuffer, SCROLLMANAGER_COLUMNBUFFER_HEIGHT);
	}

	// prep the next column to be visible where the first column is.
	// we do this because columns are only updated when we hit an 8 pixel
	// boundary when we scroll. At the start, we're already at the boundary.
	// We won't see it anyway.
	ScrollUtils_mapColumnToBuild = 32;
	ScrollUtils_buildColumn(ScrollManager_columnBuffer);
	SMS_loadTileMapColumn(0, 0, ScrollManager_columnBuffer, SCROLLMANAGER_COLUMNBUFFER_HEIGHT);

	SMS_mapROMBank(currentRomBank);
}


void ScrollUtils_InitTilemapStrip(void)
{
	u8 currentRomBank = SMS_getROMBank();
	SMS_mapROMBank(MapManager_mapResourceInfo->bankNumber);

	const u16* stripMapRunner = MapManager_mapData + MapManager_mapHeight;

	// fill the map from the second column to the last.
	for (char loop = 1; loop < 32; loop++)
	{
		SMS_loadTileMapColumn(loop, 0, stripMapRunner, SCROLLMANAGER_COLUMNBUFFER_HEIGHT);
		stripMapRunner += MapManager_mapHeight;
	}

	// prep the next column to be visible where the first column is.
	// we do this because columns are only updated when we hit an 8 pixel
	// boundary when we scroll. At the start, we're already at the boundary.
	// We won't see it anyway.
	SMS_loadTileMapColumn(0, 0, stripMapRunner, SCROLLMANAGER_COLUMNBUFFER_HEIGHT);

	SMS_mapROMBank(currentRomBank);
}