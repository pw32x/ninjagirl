#ifndef MAP_TYPES_INCLUDE_H
#define MAP_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "animation_types.h"

#define COMMON_TILESET_PROPERTIES \
    u8 resourceType;\
    const u16* const metatile_lut;\
    const u16 numMetatiles;\
    const u8 breakable

typedef struct
{
    COMMON_TILESET_PROPERTIES;
    const u8* const tiles;
    const u16 numTiles;
    u16* vdpLocation;
} Tileset;

typedef struct
{
    COMMON_TILESET_PROPERTIES;
    const TileAnimation* tileAnimation;
} AnimatedTileset;

typedef struct
{
    u8 resourceType;
    const u16* const metatileMap;
    const Tileset** const tilesets;
    u8 numTilesets;
    u16 mapWidth;
    u16 mapHeight;
} Map;

u16 Load_MapResource(const Map* map);
u16 Load_TilesetResource(const Tileset* tileset);
u16 Load_AnimatedTilesetResource(const AnimatedTileset* animatedTileset);

#endif