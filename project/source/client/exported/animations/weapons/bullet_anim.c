#include "bullet_anim.h"
#include "engine\draw_utils.h"
#include "engine\animation_types.h"
#include "engine\animation_utils.h"


unsigned char const bullet_animTileData[64] = // 2tiles x 32 bytes
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

const s8 bullet_animFrame0MetaSprites[] = 
{
    -3, -3, 0,
    (s8)0x80 // end marker
};

extern const MetaSpriteAnimationFrame bullet_animFrame0;


const MetaSpriteAnimationFrame bullet_animFrame0 = 
{
    bullet_animFrame0MetaSprites,
    5, // frame time
    &bullet_animFrame0, // next frame
};
const MetaSpriteAnimationFrame* const bullet_animFrames[1] = 
{
    &bullet_animFrame0,
};

const AnimationSetup const bullet_animSetup = 
{
    DrawUtils_drawMetasprite,
    AnimationUtils_updateMetaSpriteAnimation,
    &bullet_animFrame0,
    0,
    5,
};

u8 bullet_animVdpLocation;

const MetaSpriteAnimation bullet_anim = 
{
    METASPRITE_ANIMATION_RESOURCE_TYPE, 
    &bullet_animSetup,
    (const MetaSpriteAnimationFrame** const)bullet_animFrames,
    (unsigned char* const)bullet_animTileData, // start of the sprite data
    1, // number of frames
    8, // width in pixels
    16, // height in pixels
    2, // the total amount of tiles in animation
    2, // the max amount of sprite tiles in a frame
    &bullet_animVdpLocation,
};
