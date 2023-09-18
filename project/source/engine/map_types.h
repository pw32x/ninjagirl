#ifndef MAP_TYPES_INCLUDE_H
#define MAP_TYPES_INCLUDE_H

#include "engine/base_types.h"

typedef struct
{
    const u8* const tiles;
    const u16* const metatile_lut;
    const u16 numTiles;
    const u16 numMetatiles;
    const u16* animatedTileIndexes;
    u16 animatedTileIndexesCount;
    u16* vdpLocation;
} Tileset;

typedef struct
{
    u8 resourceType;
    const u16* const metatileMap;
    const u8* const terrainMap;
    const Tileset* const tileset;
    u16 mapWidth;
    u16 mapHeight;
} Map;

u16 Load_MapResource(const Map* map);

#endif