#include "ninja_girl.h"


unsigned char const ninja_girlTileData[640] = // 20tiles x 32 bytes
{
// tile: 0
    0x60, 0x00, 0x00, 0x00, 
    0x97, 0x60, 0x60, 0x00, 
    0x68, 0x17, 0x17, 0x10, 
    0xb0, 0x46, 0x4f, 0x29, 
    0xf0, 0x09, 0x0f, 0x46, 
    0x60, 0x1f, 0x1f, 0x00, 
    0x21, 0x1e, 0x1e, 0x00, 
    0x47, 0x39, 0x39, 0x03, 
// tile: 1
    0x49, 0x33, 0x37, 0x05, 
    0x88, 0x72, 0x77, 0x05, 
    0xc4, 0x3a, 0x3b, 0x41, 
    0x74, 0x0a, 0x0b, 0x31, 
    0x30, 0x0e, 0x03, 0x01, 
    0x04, 0x14, 0x05, 0x0f, 
    0x0e, 0x22, 0x0e, 0x1f, 
    0x1f, 0x41, 0x1f, 0x3f, 
// tile: 2
    0x00, 0x00, 0x00, 0x00, 
    0xc0, 0x00, 0x00, 0x00, 
    0x30, 0xc0, 0xc0, 0x00, 
    0x08, 0x60, 0xf0, 0x90, 
    0x04, 0x98, 0xf8, 0x60, 
    0x04, 0xf8, 0xf8, 0x00, 
    0xb4, 0x48, 0x48, 0x00, 
    0x28, 0x20, 0x60, 0xf0, 
// tile: 3
    0x28, 0xb0, 0x60, 0x60, 
    0x18, 0x00, 0xe0, 0xf0, 
    0x14, 0xc8, 0xe8, 0x30, 
    0x34, 0x08, 0xc8, 0xe0, 
    0xc8, 0x30, 0x20, 0xc0, 
    0x70, 0x00, 0xc0, 0xc0, 
    0x48, 0x00, 0x30, 0xb0, 
    0x4c, 0x04, 0x30, 0xb0, 
// tile: 4
    0x17, 0x40, 0x11, 0x39, 
    0x39, 0x80, 0x36, 0x76, 
    0x39, 0x90, 0x26, 0x66, 
    0x3e, 0x79, 0x19, 0x18, 
    0x7c, 0x7f, 0x33, 0x30, 
    0xf3, 0xf1, 0x43, 0x4f, 
    0x47, 0x49, 0x07, 0x07, 
    0x00, 0x08, 0x00, 0x07, 
// tile: 5
    0x06, 0x19, 0x01, 0x06, 
    0x19, 0x20, 0x16, 0x1f, 
    0x39, 0x50, 0x36, 0x3f, 
    0x2c, 0x57, 0x2f, 0x2c, 
    0x04, 0x53, 0x03, 0x2e, 
    0x03, 0x33, 0x03, 0x0f, 
    0x00, 0x18, 0x00, 0x07, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 6
    0xbe, 0x8e, 0x8c, 0xcc, 
    0x9f, 0x9f, 0x86, 0xe6, 
    0xa7, 0x97, 0xa1, 0xe1, 
    0x21, 0xc1, 0xc0, 0x20, 
    0x20, 0xc0, 0xc0, 0x20, 
    0x40, 0x20, 0x40, 0xc0, 
    0x00, 0x20, 0x00, 0xc0, 
    0x00, 0x40, 0x00, 0x80, 
// tile: 7
    0x00, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 
    0x40, 0x80, 0x80, 0x00, 
    0xe0, 0xc0, 0xe0, 0xe0, 
    0x00, 0x20, 0x00, 0xc0, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 8
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x80, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 9
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 10
    0x60, 0x00, 0x00, 0x00, 
    0x97, 0x60, 0x60, 0x00, 
    0x68, 0x17, 0x17, 0x10, 
    0xb0, 0x46, 0x4f, 0x29, 
    0xf0, 0x09, 0x0f, 0x46, 
    0x60, 0x1f, 0x1f, 0x00, 
    0x21, 0x1e, 0x1e, 0x00, 
    0x47, 0x39, 0x39, 0x03, 
// tile: 11
    0x49, 0x33, 0x37, 0x05, 
    0x88, 0x72, 0x77, 0x05, 
    0xc4, 0x3a, 0x3b, 0x41, 
    0x74, 0x0a, 0x0b, 0x31, 
    0x30, 0x0e, 0x03, 0x01, 
    0x04, 0x14, 0x05, 0x0f, 
    0x0e, 0x22, 0x0e, 0x1f, 
    0x1f, 0x41, 0x1f, 0x3f, 
// tile: 12
    0x00, 0x00, 0x00, 0x00, 
    0xc0, 0x00, 0x00, 0x00, 
    0x30, 0xc0, 0xc0, 0x00, 
    0x08, 0x60, 0xf0, 0x90, 
    0x04, 0x98, 0xf8, 0x60, 
    0x04, 0xf8, 0xf8, 0x00, 
    0xb4, 0x48, 0x48, 0x00, 
    0x28, 0x20, 0x60, 0xf0, 
// tile: 13
    0x28, 0xb0, 0x60, 0x60, 
    0x18, 0x00, 0xe0, 0xf0, 
    0x14, 0xc8, 0xe8, 0x30, 
    0x34, 0x08, 0xc8, 0xe0, 
    0xc8, 0x30, 0x20, 0xc0, 
    0x70, 0x00, 0xc0, 0xc0, 
    0x48, 0x00, 0x30, 0xb0, 
    0x4c, 0x04, 0x30, 0xb0, 
// tile: 14
    0x05, 0x10, 0x04, 0x0e, 
    0x0e, 0x20, 0x0d, 0x1d, 
    0x0e, 0x24, 0x09, 0x19, 
    0x0f, 0x1e, 0x06, 0x06, 
    0x1f, 0x1f, 0x0c, 0x0c, 
    0x3c, 0x3c, 0x10, 0x13, 
    0x1d, 0x32, 0x01, 0x01, 
    0x04, 0x48, 0x00, 0x37, 
// tile: 15
    0x18, 0x41, 0x0c, 0x3e, 
    0x0a, 0x99, 0x1c, 0x7e, 
    0x34, 0xb2, 0x38, 0x7c, 
    0x28, 0xb0, 0x30, 0x68, 
    0x50, 0xe0, 0x60, 0x40, 
    0x60, 0x00, 0x40, 0x40, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 16
    0xef, 0x23, 0x63, 0x73, 
    0x67, 0x27, 0xa1, 0xb9, 
    0x69, 0x25, 0xa8, 0xb8, 
    0x88, 0x70, 0x70, 0x08, 
    0x08, 0xf0, 0xf0, 0x08, 
    0xe8, 0x24, 0xe8, 0xf8, 
    0xe0, 0x24, 0xe0, 0xf8, 
    0x5b, 0x00, 0x40, 0xfc, 
// tile: 17
    0x26, 0x81, 0x19, 0x7e, 
    0x21, 0x41, 0x1f, 0x3f, 
    0x1a, 0x03, 0x07, 0x1f, 
    0x07, 0x00, 0x02, 0x07, 
    0x00, 0x02, 0x00, 0x01, 
    0x00, 0x01, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 18
    0x80, 0x80, 0x00, 0x00, 
    0xc0, 0xc0, 0x80, 0x80, 
    0xe0, 0xe0, 0x40, 0x40, 
    0x40, 0x40, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0xc0, 0x00, 0x40, 0x40, 
    0x40, 0xe0, 0xc0, 0x40, 
// tile: 19
    0x80, 0xa0, 0x80, 0xc0, 
    0x80, 0xa0, 0x80, 0xc0, 
    0x00, 0x20, 0x00, 0xc0, 
    0x00, 0x40, 0x00, 0x80, 
    0x00, 0x40, 0x00, 0x80, 
    0x00, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
};

const AnimationSprite ninja_girlFrame0Sprites[] = 
{
    { -8, -15, 0 },
    { 0, -15, 2 },
    { -8, 1, 4 },
    { 0, 1, 6 },
    { 8, 1, 8 },
};

const AnimationSprite ninja_girlFrame1Sprites[] = 
{
    { -8, -16, 10 },
    { 0, -16, 12 },
    { -10, 0, 14 },
    { -2, 0, 16 },
    { 6, 0, 18 },
};


const AnimationFrame ninja_girlFrame0 = 
{
    ninja_girlFrame0Sprites,
    5, // number of sprites
    8, // frame time
};

const AnimationFrame ninja_girlFrame1 = 
{
    ninja_girlFrame1Sprites,
    5, // number of sprites
    8, // frame time
};
const AnimationFrame* const ninja_girlFrames[2] = 
{
    &ninja_girlFrame0,
    &ninja_girlFrame1,
};

const Animation ninja_girl = 
{
    (const AnimationFrame** const)ninja_girlFrames,
    (unsigned char* const)ninja_girlTileData, // start of the sprite data
    16, // the total time of the animation
    2, // number of frames
    24, // width in pixels
    32, // height in pixels
    20, // the total amount of tiles in animation
};
