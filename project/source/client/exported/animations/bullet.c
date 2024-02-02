#include "bullet.h"


unsigned char const bulletTileData[64] = // 2tiles x 32 bytes
{
// tile: 0
    0x00, 0x78, 0x00, 0x00, 
    0x78, 0xfc, 0x78, 0x78, 
    0x78, 0xfc, 0x78, 0x78, 
    0x78, 0xfc, 0x78, 0x78, 
    0x78, 0xfc, 0x78, 0x78, 
    0x00, 0x78, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 1
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
};

const BatchedAnimationSpriteStrip bulletFrame0SpriteStrips[] = 
{
    { 1, -3, -3, 0 },
    {0},
};

extern const BatchedAnimationFrame bulletFrame0;


const BatchedAnimationFrame bulletFrame0 = 
{
    bulletFrame0SpriteStrips,
    5, // frame time
    &bulletFrame0, // next frame
};
const BatchedAnimationFrame* const bulletFrames[1] = 
{
    &bulletFrame0,
};

u8 bulletVdpLocation;

const BatchedAnimation bullet = 
{
    BATCHED_ANIMATION_RESOURCE_TYPE, 
    (const BatchedAnimationFrame** const)bulletFrames,
    (unsigned char* const)bulletTileData, // start of the sprite data
    1, // number of frames
    8, // width in pixels
    16, // height in pixels
    2, // the total amount of tiles in animation
    2, // the max amount of sprite tiles in a frame
    &bulletVdpLocation,
};
