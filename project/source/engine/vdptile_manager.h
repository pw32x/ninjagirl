#ifndef VDP_TILE_MANAGER_INCLUDE_H
#define VDP_TILE_MANAGER_INCLUDE_H

#include "engine/base_types.h"
#include "engine/animation_types.h"
#include "engine/map_types.h"

void VDPTileManager_Init(void);

u8 VDPTileManager_LoadSpriteTiles(const u8* tileData, 
								  u8 tileCount,
								  u8* vdpLocation); 

u8 VDPTileManager_ReserveSpriteTilesArea(u8 tileCount, 
										 u8* vdpLocation);

u16 VDPTileManager_LoadBackgroundTileset(const u8* tileData, 
										 u16 tileCount,
										 u16* vdpLocation);




#endif