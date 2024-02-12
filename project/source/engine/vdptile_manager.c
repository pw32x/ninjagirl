#include "vdptile_manager.h"

#include "SMSLib.h"

u16 VDPTileManager_spriteTileLocation;
u16 VDPTileManager_backgroundTileLocation;

#define MAX_TOTAL_TILES 512
#define SPRITE_TILES_START_INDEX 0
#define BACKGROUND_TILES_START_INDEX 256

void VDPTileManager_Init(void)
{
	VDPTileManager_spriteTileLocation = SPRITE_TILES_START_INDEX;
	VDPTileManager_backgroundTileLocation = BACKGROUND_TILES_START_INDEX;
}

u8 VDPTileManager_LoadSpriteTiles(const u8* tileData, 
								  u8 tileCount,
								  u8* vdpLocation)
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

	*vdpLocation = currentSpriteTileLocaton;

	return *vdpLocation;
}

u8 VDPTileManager_ReserveSpriteTilesArea(u8 tileCount, 
										 u8* vdpLocation)
{
	u16 currentSpriteTileLocaton = VDPTileManager_spriteTileLocation;

	if (currentSpriteTileLocaton + tileCount > MAX_TOTAL_TILES)
	{
		while (1) {};
	}

	VDPTileManager_spriteTileLocation += tileCount;

	*vdpLocation = currentSpriteTileLocaton;

	return *vdpLocation;

}

u16 VDPTileManager_LoadBackgroundTileset(const u8* tileData, 
										 u16 tileCount,
										 u16* vdpLocation)
{
	//if (tileCount > SPRITE_TILES_START_INDEX)
	//{
	//	// if no sprite tiles have been loaded yet, just move the start index
	//	if (VDPTileManager_spriteTileLocation == SPRITE_TILES_START_INDEX)
	//	{
	//		VDPTileManager_spriteTileLocation = tileCount;
	//	}
	//	else
	//	{
	//		// we've already loaded sprites, so we're busted.
	//		while (1) {};
	//	}
	//}

	SMS_loadTiles(tileData, VDPTileManager_spriteTileLocation, tileCount * 32);

	*vdpLocation = VDPTileManager_spriteTileLocation;

	VDPTileManager_spriteTileLocation += tileCount;

	return *vdpLocation;
}

