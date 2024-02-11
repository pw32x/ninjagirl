#include "colorTweakerCursor.h"


unsigned char const colorTweakerCursorTileData[64] = // 2tiles x 32 bytes
{
// tile: 0
    0xe0, 0xe0, 0xe0, 0xe0, 
    0xf0, 0x90, 0xf0, 0xf0, 
    0xf8, 0x88, 0xf8, 0xf8, 
    0xfc, 0x84, 0xfc, 0xfc, 
    0xfc, 0x84, 0xfc, 0xfc, 
    0xf8, 0x88, 0xf8, 0xf8, 
    0xf0, 0x90, 0xf0, 0xf0, 
    0xe0, 0xe0, 0xe0, 0xe0, 
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

const BatchedAnimationSpriteStrip colorTweakerCursorFrame0SpriteStrips[] = 
{
    { 1, 1, 0, 0 },
    {0},
};

extern const BatchedAnimationFrame colorTweakerCursorFrame0;


const BatchedAnimationFrame colorTweakerCursorFrame0 = 
{
    colorTweakerCursorFrame0SpriteStrips,
    59, // frame time
    &colorTweakerCursorFrame0, // next frame
};
const BatchedAnimationFrame* const colorTweakerCursorFrames[1] = 
{
    &colorTweakerCursorFrame0,
};

u8 colorTweakerCursorVdpLocation;

const BatchedAnimation colorTweakerCursor = 
{
    BATCHED_ANIMATION_RESOURCE_TYPE, 
    (const BatchedAnimationFrame** const)colorTweakerCursorFrames,
    (unsigned char* const)colorTweakerCursorTileData, // start of the sprite data
    1, // number of frames
    8, // width in pixels
    16, // height in pixels
    2, // the total amount of tiles in animation
    2, // the max amount of sprite tiles in a frame
    &colorTweakerCursorVdpLocation,
};
