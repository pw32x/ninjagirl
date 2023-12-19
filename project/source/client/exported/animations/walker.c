#include "walker.h"


unsigned char const walkerTileData[256] = // 8tiles x 32 bytes
{
// tile: 0
    0x07, 0x00, 0x00, 0x00, 
    0x1c, 0x03, 0x03, 0x07, 
    0x26, 0x01, 0x19, 0x1b, 
    0x40, 0x0f, 0x3f, 0x30, 
    0x71, 0x0e, 0x0e, 0x10, 
    0x99, 0x26, 0x66, 0x48, 
    0x98, 0x27, 0x67, 0x48, 
    0x98, 0x67, 0x67, 0x08, 
// tile: 1
    0xf1, 0x0e, 0x0e, 0x10, 
    0x81, 0x3e, 0x7e, 0x40, 
    0xe0, 0x1f, 0x1f, 0x00, 
    0xf0, 0x2f, 0x2f, 0x60, 
    0xaf, 0x60, 0x20, 0x77, 
    0x47, 0x38, 0x00, 0x38, 
    0x38, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 2
    0xee, 0x00, 0x00, 0x00, 
    0xb9, 0x46, 0x46, 0x2e, 
    0x72, 0x8c, 0x8c, 0x9c, 
    0xdc, 0x20, 0x20, 0x00, 
    0xfc, 0xd8, 0xd8, 0xd8, 
    0xb6, 0xd8, 0x90, 0x90, 
    0xde, 0x20, 0x20, 0x04, 
    0x06, 0xf8, 0xf8, 0x04, 
// tile: 3
    0xfe, 0x00, 0x00, 0x04, 
    0x0e, 0xf0, 0xf0, 0x04, 
    0x65, 0x9a, 0x98, 0x62, 
    0x09, 0xf2, 0xf0, 0x66, 
    0xfd, 0x0e, 0x0c, 0xee, 
    0xfa, 0x04, 0x00, 0x0c, 
    0x0c, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 4
    0x07, 0x00, 0x00, 0x00, 
    0x1c, 0x03, 0x03, 0x07, 
    0x26, 0x01, 0x19, 0x1b, 
    0x40, 0x0f, 0x3f, 0x30, 
    0x71, 0x0e, 0x0e, 0x10, 
    0x99, 0x26, 0x66, 0x48, 
    0x98, 0x27, 0x67, 0x48, 
    0x98, 0x67, 0x67, 0x08, 
// tile: 5
    0xf1, 0x0e, 0x0e, 0x10, 
    0x81, 0x3e, 0x7e, 0x40, 
    0x40, 0x1f, 0x3f, 0x20, 
    0x43, 0x1c, 0x3c, 0x20, 
    0x2f, 0x03, 0x13, 0x1b, 
    0x1f, 0x01, 0x01, 0x03, 
    0x04, 0x03, 0x00, 0x03, 
    0x07, 0x00, 0x00, 0x00, 
// tile: 6
    0xee, 0x00, 0x00, 0x00, 
    0xb9, 0x46, 0x46, 0x2e, 
    0x72, 0x8c, 0x8c, 0x9c, 
    0xdc, 0x20, 0x20, 0x00, 
    0xfc, 0xd8, 0xd8, 0xd8, 
    0xb6, 0xd8, 0x90, 0x90, 
    0xde, 0x20, 0x20, 0x04, 
    0x06, 0xf8, 0xf8, 0x04, 
// tile: 7
    0xfe, 0x00, 0x00, 0x04, 
    0x0e, 0xf0, 0xf0, 0x04, 
    0x6c, 0x90, 0x90, 0x68, 
    0x8c, 0x70, 0x70, 0x68, 
    0x78, 0x00, 0x00, 0x90, 
    0xd0, 0xa0, 0x80, 0xe0, 
    0x10, 0xe0, 0x00, 0xe0, 
    0xf0, 0x00, 0x00, 0x00, 
};

const BatchedAnimationSpriteStrip walkerFrame0SpriteStrips[] = 
{
    { 2, 0, 1, 0 },
    {0},
};

const BatchedAnimationSpriteStrip walkerFrame1SpriteStrips[] = 
{
    { 2, 0, 0, 4 },
    {0},
};

extern const BatchedAnimationFrame walkerFrame0;
extern const BatchedAnimationFrame walkerFrame1;


const BatchedAnimationFrame walkerFrame0 = 
{
    walkerFrame0SpriteStrips,
    12, // frame time
    &walkerFrame1, // next frame
};

const BatchedAnimationFrame walkerFrame1 = 
{
    walkerFrame1SpriteStrips,
    12, // frame time
    &walkerFrame0, // next frame
};
const BatchedAnimationFrame* const walkerFrames[2] = 
{
    &walkerFrame0,
    &walkerFrame1,
};

u8 walkerVdpLocation;

const BatchedAnimation walker = 
{
    BATCHED_ANIMATION_RESOURCE_TYPE, 
    (const BatchedAnimationFrame** const)walkerFrames,
    (unsigned char* const)walkerTileData, // start of the sprite data
    2, // number of frames
    16, // width in pixels
    16, // height in pixels
    8, // the total amount of tiles in animation
    4, // the max amount of sprite tiles in a frame
    &walkerVdpLocation,
};
