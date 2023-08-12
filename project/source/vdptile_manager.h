#ifndef VDP_TILE_MANAGER_INCLUDE_H
#define VDP_TILE_MANAGER_INCLUDE_H

#include "types.h"
#include "animation_types.h"
#include "map_types.h"

void VDPTileManager_Init(void);

// returns the sprite arearelative vdp index (ie returns 0 for the first sprite tile, not 256)
u8 VDPTileManager_LoadAnimationTiles(const Animation* animation); 

// always loads at index 0 in the vdp
void VDPTileManager_LoadBackgroundTileset(const Tileset* tileset);

#endif