#ifndef MAP_TYPES_INCLUDE_H
#define MAP_TYPES_INCLUDE_H

#include "types.h"

typedef struct
{
    const u8* const tiles;
    const u16* const metatile_lut;
    const u8 numTiles;
    const u8 numMetatiles;
} Tileset;

typedef struct
{
    const u16* const metatileMap;
    const Tileset* const tileset;
    u16 mapWidth;
    u16 mapHeight;
} Map;

#endif