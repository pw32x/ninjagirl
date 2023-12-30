#include "robotspring.h"


unsigned char const robotspringTileData[512] = // 16tiles x 32 bytes
{
// tile: 0
    0x7f, 0x00, 0x00, 0x00, 
    0xc2, 0x3d, 0x3d, 0x00, 
    0xba, 0x45, 0x45, 0x38, 
    0xfd, 0x02, 0x02, 0x64, 
    0xe6, 0x19, 0x19, 0x5a, 
    0xdb, 0x24, 0x24, 0x25, 
    0xff, 0x24, 0x24, 0x25, 
    0xfe, 0x3d, 0x3d, 0x3d, 
// tile: 1
    0xfc, 0x1b, 0x1b, 0x59, 
    0xde, 0x27, 0x27, 0x66, 
    0xc7, 0x3f, 0x3f, 0x7f, 
    0xc3, 0x3f, 0x3f, 0x7f, 
    0xe3, 0x1c, 0x1c, 0x7c, 
    0xbc, 0x43, 0x43, 0x3b, 
    0xc4, 0x3b, 0x3b, 0x00, 
    0x7f, 0x00, 0x00, 0x00, 
// tile: 2
    0xfe, 0x00, 0x00, 0x00, 
    0x43, 0xbc, 0xbc, 0x00, 
    0x5d, 0xa2, 0xa2, 0x1c, 
    0xbf, 0x40, 0x40, 0x26, 
    0x67, 0x98, 0x98, 0x5a, 
    0xdb, 0x24, 0x24, 0xa4, 
    0xff, 0x24, 0x24, 0xa4, 
    0x7f, 0xbc, 0xbc, 0xbc, 
// tile: 3
    0x3f, 0xd8, 0xd8, 0x9a, 
    0x7b, 0xe4, 0xe4, 0x66, 
    0xe3, 0xfc, 0xfc, 0xfe, 
    0xc3, 0xfc, 0xfc, 0xfe, 
    0xc7, 0x38, 0x38, 0x3e, 
    0x3d, 0xc2, 0xc2, 0xdc, 
    0x23, 0xdc, 0xdc, 0x00, 
    0xfe, 0x00, 0x00, 0x00, 
// tile: 4
    0x3f, 0x43, 0x03, 0x03, 
    0x7f, 0xff, 0x3c, 0x3c, 
    0x00, 0x7f, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 5
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 6
    0xc0, 0xe0, 0xc0, 0xc0, 
    0xe0, 0xf0, 0x00, 0x00, 
    0x00, 0xe0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 7
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 8
    0x00, 0xff, 0x00, 0x70, 
    0x00, 0x7f, 0x00, 0x0e, 
    0x01, 0x0f, 0x01, 0x01, 
    0x0e, 0x7f, 0x0e, 0x0e, 
    0x70, 0xfe, 0x70, 0x70, 
    0x00, 0x7f, 0x00, 0x0e, 
    0x01, 0x0f, 0x01, 0x01, 
    0x0e, 0x7f, 0x0e, 0x0e, 
// tile: 9
    0x70, 0xfe, 0x70, 0x70, 
    0x00, 0x7f, 0x00, 0x0e, 
    0x01, 0x7f, 0x01, 0x01, 
    0x7e, 0xff, 0x7e, 0x7e, 
    0x00, 0x7e, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 10
    0x00, 0xc0, 0x00, 0x00, 
    0x00, 0xc0, 0x00, 0x00, 
    0xc0, 0xe0, 0xc0, 0xc0, 
    0x00, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0xc0, 0x00, 0x00, 
    0xc0, 0xe0, 0xc0, 0xc0, 
    0x00, 0xc0, 0x00, 0x00, 
// tile: 11
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0xc0, 0x00, 0x00, 
    0xc0, 0xe0, 0xc0, 0xc0, 
    0x00, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 12
    0x3f, 0x43, 0x03, 0x03, 
    0x7f, 0xff, 0x3c, 0x3c, 
    0x3f, 0x7f, 0x03, 0x03, 
    0x7f, 0xff, 0x3c, 0x3c, 
    0x03, 0x7f, 0x03, 0x03, 
    0x00, 0x03, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 13
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 14
    0xc0, 0xe0, 0xc0, 0xc0, 
    0xe0, 0xf0, 0x00, 0x00, 
    0xc0, 0xe0, 0xc0, 0xc0, 
    0xe0, 0xf0, 0x00, 0x00, 
    0xc0, 0xe0, 0xc0, 0xc0, 
    0x00, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 15
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
};

const BatchedAnimationSpriteStrip robotspringFrame0SpriteStrips[] = 
{
    { 2, -8, -8, 0 },
    { 2, -6, 8, 4 },
    {0},
};

const BatchedAnimationSpriteStrip robotspringFrame1SpriteStrips[] = 
{
    { 2, -8, -8, 0 },
    { 2, -5, 8, 8 },
    {0},
};

const BatchedAnimationSpriteStrip robotspringFrame2SpriteStrips[] = 
{
    { 2, -8, -8, 0 },
    { 2, -6, 8, 12 },
    {0},
};

extern const BatchedAnimationFrame robotspringFrame0;
extern const BatchedAnimationFrame robotspringFrame1;
extern const BatchedAnimationFrame robotspringFrame2;


const BatchedAnimationFrame robotspringFrame0 = 
{
    robotspringFrame0SpriteStrips,
    5, // frame time
    &robotspringFrame1, // next frame
};

const BatchedAnimationFrame robotspringFrame1 = 
{
    robotspringFrame1SpriteStrips,
    4, // frame time
    &robotspringFrame2, // next frame
};

const BatchedAnimationFrame robotspringFrame2 = 
{
    robotspringFrame2SpriteStrips,
    24, // frame time
    &robotspringFrame0, // next frame
};
const BatchedAnimationFrame* const robotspringFrames[3] = 
{
    &robotspringFrame0,
    &robotspringFrame1,
    &robotspringFrame2,
};

u8 robotspringVdpLocation;

const BatchedAnimation robotspring = 
{
    BATCHED_ANIMATION_RESOURCE_TYPE, 
    (const BatchedAnimationFrame** const)robotspringFrames,
    (unsigned char* const)robotspringTileData, // start of the sprite data
    3, // number of frames
    16, // width in pixels
    32, // height in pixels
    16, // the total amount of tiles in animation
    8, // the max amount of sprite tiles in a frame
    &robotspringVdpLocation,
};
