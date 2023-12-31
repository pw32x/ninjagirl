#include "waterfall_tileset.h"
#include "resource_types.h"

const unsigned short const waterfall_tileset_metatiles[8] = // 2 metatiles
{
    // metatile 0
    0, 512,
    2, 514,
    // metatile 1
    1, 513,
    3, 515,
};

const unsigned char const waterfall_tileset_tiles[128] = // 4 tiles
{
// tile: 0
    0xFF, 0x00, 0xFF, 0xFF, 
    0xFD, 0x00, 0xFD, 0xFF, 
    0xFF, 0x00, 0xFF, 0xFF, 
    0xEF, 0x00, 0xEF, 0xFF, 
    0xFF, 0x00, 0xFF, 0xFF, 
    0x78, 0x00, 0x78, 0xFF, 
    0x97, 0x83, 0x97, 0xFF, 
    0x03, 0x00, 0x03, 0xFF, 
// tile: 1
    0xFF, 0x7F, 0xFF, 0xFF, 
    0xFF, 0x1F, 0xFF, 0xFF, 
    0x7F, 0x07, 0x7F, 0xFF, 
    0x3F, 0x01, 0x3F, 0xFF, 
    0x0F, 0x00, 0x0F, 0xFF, 
    0x03, 0x00, 0x03, 0xFF, 
    0x00, 0x00, 0x00, 0xFF, 
    0x00, 0x00, 0x00, 0xFF, 
// tile: 2
    0x00, 0x00, 0x00, 0xFF, 
    0x60, 0x00, 0x60, 0xFF, 
    0xB8, 0x00, 0xB8, 0xFF, 
    0xCE, 0x80, 0xCE, 0xFF, 
    0xF3, 0xC0, 0xF3, 0xFF, 
    0xFC, 0xF0, 0xFC, 0xFF, 
    0xFF, 0xFC, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 
// tile: 3
    0x80, 0x00, 0x80, 0xFF, 
    0x60, 0x00, 0x60, 0xFF, 
    0xB8, 0x00, 0xB8, 0xFF, 
    0xCE, 0x80, 0xCE, 0xFF, 
    0xF3, 0xC0, 0xF3, 0xFF, 
    0xFC, 0xF0, 0xFC, 0xFF, 
    0xFF, 0xFC, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 
};

u16 waterfall_tilesetVdpLocation;

RESOURCE(BANK3) const Tileset waterfall_tileset = 
{
    TILESET_RESOURCE_TYPE,
    waterfall_tileset_metatiles,
    2, // 16x16 metatiles count
    FALSE, // not breakable
    waterfall_tileset_tiles,
    4, // unique tile count
    &waterfall_tilesetVdpLocation,
};

