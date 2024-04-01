#include "bullet.h"
#include "engine\draw_utils.h"
#include "engine\animation_types.h"
#include "engine\animation_utils.h"


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

const s8 bulletFrame0MetaSprites[] = 
{
    -3, -3, 0,
    (s8)0x80 // end marker
};

extern const MetaSpriteAnimationFrame bulletFrame0;


const MetaSpriteAnimationFrame bulletFrame0 = 
{
    bulletFrame0MetaSprites,
    5, // frame time
    &bulletFrame0, // next frame
};
const MetaSpriteAnimationFrame* const bulletFrames[1] = 
{
    &bulletFrame0,
};

const AnimationSetup const bulletSetup = 
{
    DrawUtils_drawMetasprite,
    AnimationUtils_updateMetaSpriteAnimation,
    &bulletFrame0,
    0,
    5,
};

u8 bulletVdpLocation;

const MetaSpriteAnimation bullet = 
{
    METASPRITE_ANIMATION_RESOURCE_TYPE, 
    &bulletSetup,
    (const MetaSpriteAnimationFrame** const)bulletFrames,
    (unsigned char* const)bulletTileData, // start of the sprite data
    1, // number of frames
    8, // width in pixels
    16, // height in pixels
    2, // the total amount of tiles in animation
    2, // the max amount of sprite tiles in a frame
    &bulletVdpLocation,
};
