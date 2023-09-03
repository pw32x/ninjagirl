#ifndef VDP_TILE_MANAGER_INCLUDE_H
#define VDP_TILE_MANAGER_INCLUDE_H

#include "engine/base_types.h"
#include "engine/animation_types.h"
#include "engine/map_types.h"

void VDPTileManager_Init(void);

// returns the sprite arearelative vdp index (ie returns 0 for the first sprite tile, not 256)
u8 VDPTileManager_LoadSpriteTiles(const u8* tileData, u8 tileCount); 

// always loads at index 0 in the vdp
void VDPTileManager_LoadBackgroundTileset(const Tileset* tileset);

#endif