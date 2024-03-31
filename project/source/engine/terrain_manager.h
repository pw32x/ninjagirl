#ifndef TERRAIN_MANAGER_INCLUDE_H
#define TERRAIN_MANAGER_INCLUDE_H

#include "engine/base_types.h"

#define TERRAIN_WIDTH 16  // 256 / 16
#define TERRAIN_WIDTH_MINUS_ONE 15  // 256 / 16
#define TERRAIN_WIDTH_SHIFT 4
#define TERRAIN_HEIGHT 12 // 192 / 16

extern u8 TerrainManager_terrain[TERRAIN_WIDTH * TERRAIN_HEIGHT]; // in ram

extern const u8* TerrainManager_currentTerrainMapStrip;

void TerrainManager_Init(void); // inits from ScrollManager_map
void TerrainManager_Init_Strip(void); 

void TerrainManager_UpdateTerrain(u16 mapColumnIndex);
void TerrainManager_UpdateTerrain_Strip(u8 mapColumnIndex);

#define GET_TERRAIN(terrain_x, terrain_y) (TerrainManager_terrain[(terrain_x & TERRAIN_WIDTH_MINUS_ONE) + ((terrain_y) << TERRAIN_WIDTH_SHIFT)])
#define SET_TERRAIN_VALUE(terrain_x, terrain_y, value) (TerrainManager_terrain[(terrain_x & TERRAIN_WIDTH_MINUS_ONE) + ((terrain_y) << TERRAIN_WIDTH_SHIFT)] = value)

// terrain types
#define TERRAIN_EMPTY				0
#define TERRAIN_SOLID				1
#define TERRAIN_TOPSOLID			2
#define TERRAIN_CLIMB				3
#define TERRAIN_HURT				4
#define TERRAIN_WATER				5
#define TERRAIN_SLOPE45RIGHT		6
#define TERRAIN_SLOPE45LEFT			7
#define TERRAIN_SLOPE30RIGHT1		8
#define TERRAIN_SLOPE30RIGHT2		9
#define TERRAIN_SLOPE30LEFT1		10
#define TERRAIN_SLOPE30LEFT2		11

#define TERRAIN_INVALID	((u8)-1)

// #define TERRAIN_12
// #define TERRAIN_13
// #define TERRAIN_14
// #define TERRAIN_15


#endif