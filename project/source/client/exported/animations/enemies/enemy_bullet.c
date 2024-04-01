#include "enemy_bullet.h"
#include "engine\draw_utils.h"
#include "engine\animation_types.h"
#include "engine\animation_utils.h"


unsigned char const enemy_bulletTileData[128] = // 4tiles x 32 bytes
{
// tile: 0
    0x00, 0x3c, 0x3c, 0x00, 
    0x3c, 0x42, 0x42, 0x3c, 
    0x7e, 0x81, 0x81, 0x7e, 
    0x7e, 0x81, 0x81, 0x7e, 
    0x7e, 0x81, 0x81, 0x7e, 
    0x7e, 0x81, 0x81, 0x7e, 
    0x3c, 0x42, 0x42, 0x3c, 
    0x00, 0x3c, 0x3c, 0x00, 
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
    0x00, 0x3c, 0x00, 0x3c, 
    0x3c, 0x7e, 0x00, 0x42, 
    0x7e, 0xff, 0x00, 0x81, 
    0x7e, 0xff, 0x00, 0x81, 
    0x7e, 0xff, 0x00, 0x81, 
    0x7e, 0xff, 0x00, 0x81, 
    0x3c, 0x7e, 0x00, 0x42, 
    0x00, 0x3c, 0x00, 0x3c, 
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

const s8 enemy_bulletFrame0MetaSprites[] = 
{
    -4, -4, 0,
    (s8)0x80 // end marker
};

const s8 enemy_bulletFrame1MetaSprites[] = 
{
    -4, -4, 2,
    (s8)0x80 // end marker
};

extern const MetaSpriteAnimationFrame enemy_bulletFrame0;
extern const MetaSpriteAnimationFrame enemy_bulletFrame1;


const MetaSpriteAnimationFrame enemy_bulletFrame0 = 
{
    enemy_bulletFrame0MetaSprites,
    4, // frame time
    &enemy_bulletFrame1, // next frame
};

const MetaSpriteAnimationFrame enemy_bulletFrame1 = 
{
    enemy_bulletFrame1MetaSprites,
    4, // frame time
    &enemy_bulletFrame0, // next frame
};
const MetaSpriteAnimationFrame* const enemy_bulletFrames[2] = 
{
    &enemy_bulletFrame0,
    &enemy_bulletFrame1,
};

const AnimationSetup const enemy_bulletSetup = 
{
    DrawUtils_drawMetasprite,
    AnimationUtils_updateMetaSpriteAnimation,
    &enemy_bulletFrame0,
    0,
    4,
};

u8 enemy_bulletVdpLocation;

const MetaSpriteAnimation enemy_bullet = 
{
    METASPRITE_ANIMATION_RESOURCE_TYPE, 
    &enemy_bulletSetup,
    (const MetaSpriteAnimationFrame** const)enemy_bulletFrames,
    (unsigned char* const)enemy_bulletTileData, // start of the sprite data
    2, // number of frames
    8, // width in pixels
    16, // height in pixels
    4, // the total amount of tiles in animation
    2, // the max amount of sprite tiles in a frame
    &enemy_bulletVdpLocation,
};
