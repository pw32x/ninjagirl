#include "walker_small.h"
#include "engine\draw_utils.h"
#include "engine\animation_types.h"
#include "engine\animation_utils.h"


unsigned char const walker_smallTileData[128] = // 4tiles x 32 bytes
{
// tile: 0
    0x3e, 0x00, 0x00, 0x00, 
    0x52, 0x2d, 0x2d, 0x1b, 
    0x8b, 0x7e, 0x7e, 0x0a, 
    0x81, 0x3e, 0x74, 0x40, 
    0xc3, 0xff, 0xff, 0x00, 
    0xe7, 0xff, 0xff, 0x42, 
    0xff, 0x66, 0x66, 0x00, 
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
// tile: 2
    0x3e, 0x00, 0x00, 0x00, 
    0x52, 0x2d, 0x2d, 0x1b, 
    0x8b, 0x7e, 0x7e, 0x0a, 
    0x81, 0x3e, 0x74, 0x40, 
    0x81, 0x7e, 0x7e, 0x00, 
    0x42, 0x3c, 0x3c, 0x00, 
    0x3e, 0x1c, 0x1c, 0x18, 
    0x3e, 0x1c, 0x1c, 0x00, 
// tile: 3
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
};

const s8 walker_smallFrame0MetaSprites[] = 
{
    -4, -3, 0,
    (s8)0x80 // end marker
};

const s8 walker_smallFrame1MetaSprites[] = 
{
    -4, -4, 2,
    (s8)0x80 // end marker
};

extern const MetaSpriteAnimationFrame walker_smallFrame0;
extern const MetaSpriteAnimationFrame walker_smallFrame1;


const MetaSpriteAnimationFrame walker_smallFrame0 = 
{
    walker_smallFrame0MetaSprites,
    8, // frame time
    &walker_smallFrame1, // next frame
};

const MetaSpriteAnimationFrame walker_smallFrame1 = 
{
    walker_smallFrame1MetaSprites,
    8, // frame time
    &walker_smallFrame0, // next frame
};
const MetaSpriteAnimationFrame* const walker_smallFrames[2] = 
{
    &walker_smallFrame0,
    &walker_smallFrame1,
};

const AnimationSetup const walker_smallSetup = 
{
    DrawUtils_drawMetasprite,
    AnimationUtils_updateMetaSpriteAnimation,
    &walker_smallFrame0,
    0,
    8,
};

u8 walker_smallVdpLocation;

const MetaSpriteAnimation walker_small = 
{
    METASPRITE_ANIMATION_RESOURCE_TYPE, 
    &walker_smallSetup,
    (const MetaSpriteAnimationFrame** const)walker_smallFrames,
    (unsigned char* const)walker_smallTileData, // start of the sprite data
    2, // number of frames
    8, // width in pixels
    8, // height in pixels
    4, // the total amount of tiles in animation
    2, // the max amount of sprite tiles in a frame
    &walker_smallVdpLocation,
};
