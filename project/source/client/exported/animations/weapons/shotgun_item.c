#include "shotgun_item.h"


unsigned char const shotgun_itemTileData[64] = // 2tiles x 32 bytes
{
// tile: 0
    0x00, 0x3c, 0x00, 0x00, 
    0x00, 0x7e, 0x3c, 0x00, 
    0x00, 0xff, 0x7e, 0x00, 
    0x3c, 0xc3, 0x42, 0x3c, 
    0x7e, 0xbd, 0x3c, 0x3c, 
    0x7e, 0x42, 0x42, 0x42, 
    0x42, 0xc1, 0x7c, 0x40, 
    0x7c, 0xbd, 0x3e, 0x3c, 
// tile: 1
    0x3e, 0x83, 0x42, 0x02, 
    0x42, 0x42, 0x7e, 0x42, 
    0x7e, 0x3c, 0x3c, 0x3c, 
    0x3c, 0x81, 0x42, 0x00, 
    0x3c, 0xc3, 0x42, 0x3c, 
    0x00, 0xff, 0x7e, 0x00, 
    0x00, 0x7e, 0x3c, 0x00, 
    0x00, 0x3c, 0x00, 0x00, 
};

const s8 shotgun_itemFrame0MetaSprites[] = 
{
    -4, -8, 0,
    (s8)0x80 // end marker
};

extern const MetaSpriteAnimationFrame shotgun_itemFrame0;


const MetaSpriteAnimationFrame shotgun_itemFrame0 = 
{
    shotgun_itemFrame0MetaSprites,
    3, // frame time
    &shotgun_itemFrame0, // next frame
};
const MetaSpriteAnimationFrame* const shotgun_itemFrames[1] = 
{
    &shotgun_itemFrame0,
};

u8 shotgun_itemVdpLocation;

const MetaSpriteAnimation shotgun_item = 
{
    METASPRITE_ANIMATION_RESOURCE_TYPE, 
    (const MetaSpriteAnimationFrame** const)shotgun_itemFrames,
    (unsigned char* const)shotgun_itemTileData, // start of the sprite data
    1, // number of frames
    8, // width in pixels
    16, // height in pixels
    2, // the total amount of tiles in animation
    2, // the max amount of sprite tiles in a frame
    &shotgun_itemVdpLocation,
};
