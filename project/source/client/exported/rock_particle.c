#include "rock_particle.h"


unsigned char const rock_particleTileData[128] = // 4tiles x 32 bytes
{
// tile: 0
    0x00, 0x3c, 0x3c, 0x3c, 
    0xc8, 0x30, 0x34, 0xf8, 
    0x60, 0x80, 0x90, 0xe0, 
    0x08, 0x04, 0xc4, 0x0c, 
    0x34, 0x08, 0x08, 0x34, 
    0x70, 0x00, 0x08, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 1
    0x34, 0x08, 0x08, 0x1c, 
    0x84, 0x7c, 0x7c, 0x3c, 
    0x90, 0x70, 0x70, 0xf0, 
    0xcc, 0xc0, 0xc0, 0xc4, 
    0x0c, 0x00, 0x30, 0x0c, 
    0x00, 0x00, 0x78, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 2
    0x08, 0x04, 0x34, 0x08, 
    0x64, 0x18, 0x98, 0x7c, 
    0x30, 0xc0, 0xc0, 0xf0, 
    0x04, 0xc0, 0xc8, 0xc4, 
    0x10, 0x1c, 0x3c, 0x1c, 
    0x78, 0x70, 0x70, 0x78, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 3
    0x3c, 0x30, 0x30, 0x3c, 
    0x9c, 0xe0, 0xe0, 0xf8, 
    0x10, 0xe0, 0xe0, 0xc0, 
    0xc8, 0x0c, 0x0c, 0x8c, 
    0x28, 0x14, 0x14, 0x3c, 
    0x38, 0x40, 0x40, 0x78, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
};

const AnimationSprite rock_particleFrame0Sprites[] = 
{
    { 0, 0, 0 },
};

const AnimationSprite rock_particleFrame1Sprites[] = 
{
    { 0, 0, 1 },
};

const AnimationSprite rock_particleFrame2Sprites[] = 
{
    { 0, 0, 2 },
};

const AnimationSprite rock_particleFrame3Sprites[] = 
{
    { 0, 0, 3 },
};

extern const AnimationFrame rock_particleFrame0;
extern const AnimationFrame rock_particleFrame1;
extern const AnimationFrame rock_particleFrame2;
extern const AnimationFrame rock_particleFrame3;

const AnimationFrame rock_particleFrame0 = 
{
    rock_particleFrame0Sprites,
    1, // number of sprites
    4, // frame time
    &rock_particleFrame1, // next frame
};

const AnimationFrame rock_particleFrame1 = 
{
    rock_particleFrame1Sprites,
    1, // number of sprites
    4, // frame time
    &rock_particleFrame2, // next frame
};

const AnimationFrame rock_particleFrame2 = 
{
    rock_particleFrame2Sprites,
    1, // number of sprites
    4, // frame time
    &rock_particleFrame3, // next frame
};

const AnimationFrame rock_particleFrame3 = 
{
    rock_particleFrame3Sprites,
    1, // number of sprites
    4, // frame time
    &rock_particleFrame0, // next frame
};
const AnimationFrame* const rock_particleFrames[4] = 
{
    &rock_particleFrame0,
    &rock_particleFrame1,
    &rock_particleFrame2,
    &rock_particleFrame3,
};

u8 rock_particleVdpLocation;

const Animation rock_particle = 
{
    REGULAR_ANIMATION_RESOURCE_TYPE, 
    (const AnimationFrame** const)rock_particleFrames,
    (unsigned char* const)rock_particleTileData, // start of the sprite data
    4, // number of frames
    6, // width in pixels
    6, // height in pixels
    4, // the total amount of tiles in animation
    &rock_particleVdpLocation,
};
