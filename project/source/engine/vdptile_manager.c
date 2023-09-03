#include "vdptile_manager.h"

#include "SMSLib.h"

u16 VDPTileManager_spriteTileLocation;

#define MAX_TOTAL_TILES 512
#define SPRITE_TILES_START_INDEX 256

void VDPTileManager_Init(void)
{
	VDPTileManager_spriteTileLocation = SPRITE_TILES_START_INDEX;
}

u8 VDPTileManager_LoadSpriteTiles(const u8* tileData, u8 tileCount)
{
	u16 currentSpriteTileLocaton = VDPTileManager_spriteTileLocation;

	if (currentSpriteTileLocaton + tileCount > MAX_TOTAL_TILES)
	{
		while (1) {};
	}

	SMS_loadTiles(tileData, 
				  VDPTileManager_spriteTileLocation, 
				  tileCount * 32);

	VDPTileManager_spriteTileLocation += tileCount;

	return currentSpriteTileLocaton - 256;
}

void VDPTileManager_LoadBackgroundTileset(const Tileset* tileset)
{
	u16 numTiles = tileset->numTiles;

	if (numTiles > SPRITE_TILES_START_INDEX)
	{
		// if no sprite tiles have been loaded yet, just move the start index
		if (VDPTileManager_spriteTileLocation == SPRITE_TILES_START_INDEX)
		{
			VDPTileManager_spriteTileLocation = numTiles;
		}
		else
		{
			// we've already loaded sprites, so we're busted.
			while (1) {};
		}
	}

	// always starting at 0 for now
	SMS_loadTiles(tileset->tiles, 0, numTiles * 32);
}

