#ifndef MAP_TYPES_INCLUDE_H
#define MAP_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "animation_types.h"

// exported format of map values
// terrain_type  | blockmap_index | block_index
// 1111            111              111111111
// 0 - 15          0 - 7            0 - 511



#define BLOCK_MASK          0x01FF
#define TILESET_INDEX_MASK  0x0E00
#define TERRAIN_TYPE_MASK   0xF000

#define SHORT_TILESET_INDEX_MASK    0x07

#define TILESET_INDEX_SHIFT 9
#define TERRAIN_TYPE_SHIFT 12

#define GET_TILESET_INDEX(x, y) ((ScrollManager_map[(x) + ((y) * ScrollManager_mapWidth)] & TILESET_INDEX_MASK) >> TILESET_INDEX_SHIFT)



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