#ifndef TERRAIN_MANAGER_INCLUDE_H
#define TERRAIN_MANAGER_INCLUDE_H

#include "engine/base_types.h"

#define TERRAIN_WIDTH 16  // 256 / 16
#define TERRAIN_WIDTH_MINUS_ONE 15  // 256 / 16
#define TERRAIN_WIDTH_SHIFT 4
#define TERRAIN_HEIGHT 12 // 192 / 16

extern u8 TerrainManager_terrain[TERRAIN_WIDTH * TERRAIN_HEIGHT]; // in ram

void TerrainManager_Init(void); // inits from ScrollManager_map
void TerrainManager_UpdateTerrain(u16 mapColumnIndex);

#define GET_TERRAIN(terrain_x, terrain_y) (TerrainManager_terrain[(terrain_x & TERRAIN_WIDTH_MINUS_ONE) + ((terrain_y) << TERRAIN_WIDTH_SHIFT)])
#define SET_TERRAIN_VALUE(terrain_x, terrain_y, value) (TerrainManager_terrain[(terrain_x & TERRAIN_WIDTH_MINUS_ONE) + ((terrain_y) << TERRAIN_WIDTH_SHIFT)] = value)

#endif