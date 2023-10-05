#ifndef MAP_TYPES_INCLUDE_H
#define MAP_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "animation_types.h"

typedef struct
{
    u8 resourceType;
    const u8* const tiles;
    const u16* const metatile_lut;
    const u16 numTiles;
    const u16 numMetatiles;
    u16* vdpLocation;
} Tileset;

typedef struct
{
    u8 resourceType;
    const u16* const metatile_lut;
    const u16 numMetatiles;
    const TileAnimation* tileAnimation;
} AnimatedTileset;

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