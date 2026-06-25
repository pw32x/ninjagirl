#include "shotgun_item_anim.h"
#include "engine\draw_utils.h"
#include "engine\animation_types.h"
#include "engine\animation_utils.h"


unsigned char const shotgun_item_animTileData[64] = // 2tiles x 32 bytes
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

const s8 shotgun_item_animFrame0MetaSprites[] = 
{
    -4, -8, 0,
    (s8)0x80 // end marker
};

extern const MetaSpriteAnimationFrame shotgun_item_animFrame0;


const MetaSpriteAnimationFrame shotgun_item_animFrame0 = 
{
    shotgun_item_animFrame0MetaSprites,
    3, // frame time
    &shotgun_item_animFrame0, // next frame
};
const MetaSpriteAnimationFrame* const shotgun_item_animFrames[1] = 
{
    &shotgun_item_animFrame0,
};

const AnimationSetup const shotgun_item_animSetup = 
{
    DrawUtils_drawMetasprite,
    AnimationUtils_updateMetaSpriteAnimation,
    &shotgun_item_animFrame0,
    0,
    3,
};

u8 shotgun_item_animVdpLocation;

const MetaSpriteAnimation shotgun_item_anim = 
{
    METASPRITE_ANIMATION_RESOURCE_TYPE, 
    &shotgun_item_animSetup,
    (const MetaSpriteAnimationFrame** const)shotgun_item_animFrames,
    (unsigned char* const)shotgun_item_animTileData, // start of the sprite data
    1, // number of frames
    8, // width in pixels
    16, // height in pixels
    2, // the total amount of tiles in animation
    2, // the max amount of sprite tiles in a frame
    &shotgun_item_animVdpLocation,
};
