#include "waterfall_tileset.h"
#include "resource_types.h"

const unsigned short const waterfall_tileset_metatiles[8] = // 2 metatiles
{
    // metatile 0
    0, 512,
    1, 513,
    // metatile 1
    2, 514,
    3, 515,
};
extern TileAnimation waterfall; // the animation this tileset needs

const AnimatedTileset waterfall_tileset = 
{
    ANIMATED_TILESET_RESOURCE_TYPE,
    waterfall_tileset_metatiles,
    2, // 16x16 metatiles count
    FALSE, // not breakable
    &waterfall, // animation
};

