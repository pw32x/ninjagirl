#include "shotgun_item.h"


unsigned char const shotgun_itemTileData[64] = // 2tiles x 32 bytes
{
// tile: 0
    0x0c, 0x30, 0x30, 0x3c, 
    0x00, 0x7e, 0x7e, 0x42, 
    0x24, 0xdb, 0xdb, 0xa5, 
    0xff, 0x00, 0x00, 0xff, 
    0xff, 0x3c, 0x3c, 0x3c, 
    0x7e, 0x42, 0x42, 0x42, 
    0xc3, 0x40, 0x7c, 0x40, 
    0xfd, 0x3c, 0x3e, 0x3c, 
// tile: 1
    0xbf, 0x02, 0x42, 0x02, 
    0x42, 0x42, 0x7e, 0x42, 
    0x7e, 0x3c, 0x3c, 0x3c, 
    0xbd, 0x00, 0x42, 0x00, 
    0x3f, 0xc0, 0xc0, 0xff, 
    0x24, 0xdb, 0xdb, 0xa5, 
    0x00, 0x7e, 0x7e, 0x42, 
    0x3c, 0x00, 0x00, 0x3c, 
};

const BatchedAnimationSpriteStrip shotgun_itemFrame0SpriteStrips[] = 
{
    { 1, -4, -8, 0 },
    {0},
};

extern const BatchedAnimationFrame shotgun_itemFrame0;


const BatchedAnimationFrame shotgun_itemFrame0 = 
{
    shotgun_itemFrame0SpriteStrips,
    3, // frame time
    &shotgun_itemFrame0, // next frame
};
const BatchedAnimationFrame* const shotgun_itemFrames[1] = 
{
    &shotgun_itemFrame0,
};

u8 shotgun_itemVdpLocation;

const BatchedAnimation shotgun_item = 
{
    BATCHED_ANIMATION_RESOURCE_TYPE, 
    (const BatchedAnimationFrame** const)shotgun_itemFrames,
    (unsigned char* const)shotgun_itemTileData, // start of the sprite data
    1, // number of frames
    8, // width in pixels
    16, // height in pixels
    2, // the total amount of tiles in animation
    2, // the max amount of sprite tiles in a frame
    &shotgun_itemVdpLocation,
};
