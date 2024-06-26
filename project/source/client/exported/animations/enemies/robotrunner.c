#include "robotrunner.h"
#include "engine\draw_utils.h"
#include "engine\animation_types.h"
#include "engine\animation_utils.h"


unsigned char const robotrunnerTileData[1024] = // 32tiles x 32 bytes
{
// tile: 0
    0x00, 0x0f, 0x00, 0x00, 
    0x0f, 0x3d, 0x0f, 0x02, 
    0x3f, 0x70, 0x1f, 0x0f, 
    0x70, 0xef, 0x30, 0x10, 
    0x78, 0xf7, 0x18, 0x08, 
    0x76, 0xe9, 0x36, 0x16, 
    0x76, 0xff, 0x16, 0x06, 
    0x76, 0xef, 0x36, 0x16, 
// tile: 1
    0x7b, 0xf7, 0x1b, 0x0b, 
    0x3c, 0x63, 0x3c, 0x1c, 
    0x00, 0x3f, 0x00, 0x00, 
    0x0e, 0x1f, 0x00, 0x00, 
    0x0e, 0x1f, 0x06, 0x00, 
    0x00, 0x3f, 0x00, 0x00, 
    0x3f, 0xfa, 0x1f, 0x05, 
    0x7f, 0xfc, 0x2f, 0x03, 
// tile: 2
    0x00, 0xe0, 0x00, 0x00, 
    0xe0, 0x38, 0xe0, 0xe0, 
    0xf8, 0x14, 0xf8, 0xf8, 
    0x70, 0xaf, 0x70, 0x70, 
    0x20, 0xde, 0x20, 0x20, 
    0x02, 0xfd, 0x02, 0x02, 
    0x52, 0xaf, 0x52, 0x52, 
    0x52, 0xff, 0x52, 0x52, 
// tile: 3
    0xac, 0xde, 0xac, 0xac, 
    0x70, 0x8c, 0x70, 0x70, 
    0x00, 0xf8, 0x00, 0x00, 
    0xa0, 0xf0, 0xa0, 0x00, 
    0xa0, 0xf0, 0xa0, 0xa0, 
    0x00, 0xf8, 0x00, 0x00, 
    0xf8, 0x0e, 0xf8, 0xf8, 
    0xfc, 0x06, 0xfc, 0xfc, 
// tile: 4
    0x01, 0x3f, 0x01, 0x00, 
    0x36, 0x7f, 0x06, 0x00, 
    0x5a, 0xed, 0x22, 0x12, 
    0x49, 0xff, 0x30, 0x00, 
    0x30, 0x7f, 0x00, 0x00, 
    0x70, 0xff, 0x70, 0x00, 
    0x38, 0x4f, 0x38, 0x38, 
    0x38, 0x6f, 0x38, 0x18, 
// tile: 5
    0x18, 0x2f, 0x18, 0x18, 
    0x00, 0x27, 0x18, 0x00, 
    0x04, 0x1b, 0x08, 0x04, 
    0x04, 0x1b, 0x08, 0x04, 
    0x04, 0x0b, 0x00, 0x04, 
    0x00, 0x07, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 6
    0xf3, 0xac, 0xf3, 0x53, 
    0xed, 0xdb, 0xed, 0x24, 
    0xef, 0xbf, 0xec, 0x40, 
    0xf5, 0xde, 0xf2, 0x21, 
    0x04, 0xff, 0x03, 0x00, 
    0xfb, 0xff, 0xf8, 0x00, 
    0x7b, 0x87, 0x7b, 0x78, 
    0x03, 0x7e, 0x03, 0x01, 
// tile: 7
    0x03, 0x06, 0x03, 0x01, 
    0x03, 0x86, 0x03, 0x01, 
    0x00, 0x84, 0x03, 0x00, 
    0x01, 0x86, 0x02, 0x01, 
    0x00, 0x87, 0x02, 0x00, 
    0x00, 0x87, 0x02, 0x00, 
    0x00, 0x82, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 8
    0xc0, 0x38, 0xc0, 0xc0, 
    0xd8, 0x3c, 0xc0, 0xc0, 
    0xcc, 0xb6, 0xd0, 0x48, 
    0x84, 0xfe, 0x18, 0x00, 
    0x98, 0xfc, 0x00, 0x00, 
    0x1c, 0xfe, 0x1c, 0x00, 
    0xb8, 0xec, 0xb8, 0x18, 
    0xb8, 0xcc, 0xb8, 0xb8, 
// tile: 9
    0x30, 0xd8, 0x30, 0x30, 
    0x00, 0xc8, 0x30, 0x00, 
    0x20, 0xd0, 0x40, 0x20, 
    0x20, 0xd0, 0x40, 0x20, 
    0x00, 0x60, 0x40, 0x00, 
    0x00, 0x40, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 10
    0x05, 0x0f, 0x01, 0x00, 
    0x02, 0x0f, 0x02, 0x00, 
    0x06, 0x3d, 0x06, 0x02, 
    0x36, 0x7d, 0x06, 0x02, 
    0x58, 0xef, 0x20, 0x10, 
    0x48, 0xff, 0x30, 0x00, 
    0x30, 0x7f, 0x00, 0x00, 
    0x70, 0xff, 0x70, 0x00, 
// tile: 11
    0x38, 0x4f, 0x38, 0x38, 
    0x38, 0x6f, 0x38, 0x18, 
    0x18, 0x2f, 0x18, 0x18, 
    0x00, 0x27, 0x18, 0x00, 
    0x04, 0x1b, 0x08, 0x04, 
    0x04, 0x1a, 0x08, 0x04, 
    0x04, 0x0a, 0x00, 0x04, 
    0x00, 0x04, 0x00, 0x00, 
// tile: 12
    0xf3, 0xac, 0xf3, 0x53, 
    0xef, 0xdb, 0xec, 0x24, 
    0xed, 0xbe, 0xea, 0x41, 
    0xf4, 0xcf, 0xf3, 0x30, 
    0x03, 0xff, 0x00, 0x00, 
    0xfb, 0xff, 0xfb, 0x00, 
    0x7b, 0x86, 0x7b, 0x79, 
    0x03, 0x7e, 0x03, 0x01, 
// tile: 13
    0x03, 0x86, 0x03, 0x01, 
    0x00, 0x84, 0x03, 0x00, 
    0x01, 0x86, 0x02, 0x01, 
    0x00, 0x87, 0x02, 0x00, 
    0x00, 0x87, 0x02, 0x00, 
    0x00, 0x82, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 14
    0xc0, 0x20, 0xc0, 0xc0, 
    0xc0, 0xa0, 0xc0, 0x40, 
    0xc0, 0xf8, 0x40, 0x00, 
    0x98, 0xfc, 0x00, 0x00, 
    0x0c, 0xf6, 0x10, 0x08, 
    0xa4, 0xfe, 0x98, 0x00, 
    0x98, 0xfc, 0x80, 0x80, 
    0x1c, 0xfe, 0x1c, 0x00, 
// tile: 15
    0x38, 0xec, 0x38, 0x18, 
    0x38, 0xcc, 0x38, 0x38, 
    0x30, 0xd8, 0x30, 0x30, 
    0x00, 0x48, 0x30, 0x00, 
    0x20, 0xd0, 0x40, 0x20, 
    0x20, 0xd0, 0x40, 0x20, 
    0x00, 0xe0, 0x40, 0x00, 
    0x00, 0x40, 0x00, 0x00, 
// tile: 16
    0x00, 0x07, 0x00, 0x00, 
    0x07, 0x1c, 0x07, 0x07, 
    0x1f, 0x28, 0x1f, 0x1f, 
    0x0e, 0xf5, 0x0e, 0x0e, 
    0x04, 0x7b, 0x04, 0x04, 
    0x40, 0xbf, 0x40, 0x40, 
    0x4a, 0xf5, 0x4a, 0x4a, 
    0x4a, 0xff, 0x4a, 0x4a, 
// tile: 17
    0x35, 0x7b, 0x35, 0x35, 
    0x0e, 0x31, 0x0e, 0x0e, 
    0x00, 0x1f, 0x00, 0x00, 
    0x05, 0x0f, 0x05, 0x00, 
    0x05, 0x0f, 0x05, 0x05, 
    0x00, 0x1f, 0x00, 0x00, 
    0x1f, 0x70, 0x1f, 0x1f, 
    0x3f, 0x60, 0x3f, 0x3f, 
// tile: 18
    0x00, 0xf0, 0x00, 0x00, 
    0xf0, 0xbc, 0xf0, 0x40, 
    0xfc, 0x0e, 0xf8, 0xf0, 
    0x0e, 0xf7, 0x0c, 0x08, 
    0x1e, 0xef, 0x18, 0x10, 
    0x6e, 0x97, 0x6c, 0x68, 
    0x6e, 0xff, 0x68, 0x60, 
    0x6e, 0xf7, 0x6c, 0x68, 
// tile: 19
    0xde, 0xef, 0xd8, 0xd0, 
    0x3c, 0xc6, 0x3c, 0x38, 
    0x00, 0xfc, 0x00, 0x00, 
    0x70, 0xf8, 0x00, 0x00, 
    0x70, 0xf8, 0x60, 0x00, 
    0x00, 0xfc, 0x00, 0x00, 
    0xfc, 0x5f, 0xf8, 0xa0, 
    0xfe, 0x3f, 0xf4, 0xc0, 
// tile: 20
    0x07, 0x38, 0x07, 0x07, 
    0x37, 0x79, 0x07, 0x06, 
    0x67, 0xdb, 0x16, 0x24, 
    0x43, 0xfe, 0x30, 0x01, 
    0x32, 0x7f, 0x01, 0x00, 
    0x71, 0xff, 0x70, 0x00, 
    0x3b, 0x6f, 0x3b, 0x30, 
    0x3b, 0x66, 0x3b, 0x3b, 
// tile: 21
    0x19, 0x36, 0x19, 0x19, 
    0x01, 0x26, 0x19, 0x01, 
    0x08, 0x16, 0x05, 0x08, 
    0x09, 0x16, 0x04, 0x09, 
    0x00, 0x0d, 0x04, 0x00, 
    0x00, 0x05, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 22
    0x9f, 0x6b, 0x9f, 0x94, 
    0x6e, 0xb7, 0x6e, 0x48, 
    0xee, 0xfb, 0x6e, 0x04, 
    0x5f, 0xf7, 0x9e, 0x08, 
    0x40, 0xff, 0x80, 0x00, 
    0xbe, 0xff, 0x3e, 0x00, 
    0xbc, 0xc3, 0xbc, 0x3c, 
    0x80, 0xfd, 0x80, 0x00, 
// tile: 23
    0x80, 0xc1, 0x80, 0x00, 
    0x80, 0xc3, 0x80, 0x00, 
    0x00, 0x43, 0x80, 0x00, 
    0x00, 0xc3, 0x80, 0x00, 
    0x00, 0xc3, 0x80, 0x00, 
    0x00, 0xc3, 0x80, 0x00, 
    0x00, 0x82, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 24
    0x00, 0xf8, 0x00, 0x00, 
    0xd8, 0xfc, 0xc0, 0x00, 
    0xb4, 0x6e, 0x88, 0x90, 
    0x24, 0xfe, 0x18, 0x00, 
    0x18, 0xfc, 0x00, 0x00, 
    0x1c, 0xfe, 0x1c, 0x00, 
    0x38, 0xe4, 0x38, 0x38, 
    0x38, 0xec, 0x38, 0x30, 
// tile: 25
    0x30, 0xe8, 0x30, 0x30, 
    0x00, 0xc8, 0x30, 0x00, 
    0x40, 0xb0, 0x20, 0x40, 
    0x40, 0xb0, 0x20, 0x40, 
    0x40, 0xa0, 0x00, 0x40, 
    0x00, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 26
    0x07, 0x08, 0x07, 0x07, 
    0x07, 0x0b, 0x06, 0x04, 
    0x07, 0x3e, 0x04, 0x01, 
    0x32, 0x7f, 0x01, 0x00, 
    0x61, 0xdf, 0x10, 0x20, 
    0x4b, 0xff, 0x33, 0x00, 
    0x33, 0x7e, 0x03, 0x03, 
    0x71, 0xfe, 0x71, 0x01, 
// tile: 27
    0x39, 0x6e, 0x39, 0x31, 
    0x38, 0x66, 0x39, 0x38, 
    0x19, 0x36, 0x18, 0x19, 
    0x00, 0x25, 0x18, 0x00, 
    0x08, 0x17, 0x04, 0x08, 
    0x08, 0x16, 0x04, 0x08, 
    0x00, 0x0e, 0x04, 0x00, 
    0x00, 0x04, 0x00, 0x00, 
// tile: 28
    0x9f, 0x6b, 0x9f, 0x94, 
    0xee, 0xb7, 0x6e, 0x48, 
    0x6e, 0xfb, 0xae, 0x04, 
    0x5e, 0xe7, 0x9e, 0x18, 
    0x80, 0xff, 0x00, 0x00, 
    0xbe, 0xff, 0xbe, 0x00, 
    0xbc, 0xc3, 0xbc, 0x3c, 
    0x80, 0xfd, 0x80, 0x00, 
// tile: 29
    0x80, 0xc3, 0x80, 0x00, 
    0x00, 0x43, 0x80, 0x00, 
    0x00, 0xc3, 0x80, 0x00, 
    0x00, 0xc3, 0x80, 0x00, 
    0x00, 0xc3, 0x80, 0x00, 
    0x00, 0x82, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 30
    0x40, 0xe0, 0x00, 0x00, 
    0x80, 0xe0, 0x80, 0x00, 
    0xc0, 0x78, 0xc0, 0x80, 
    0xd8, 0x7c, 0xc0, 0x80, 
    0x34, 0xee, 0x08, 0x10, 
    0x24, 0xfe, 0x18, 0x00, 
    0x18, 0xfc, 0x00, 0x00, 
    0x1c, 0xfe, 0x1c, 0x00, 
// tile: 31
    0x38, 0xe4, 0x38, 0x38, 
    0x38, 0xec, 0x38, 0x30, 
    0x30, 0xe8, 0x30, 0x30, 
    0x00, 0xc8, 0x30, 0x00, 
    0x40, 0xb0, 0x20, 0x40, 
    0x40, 0xb0, 0x20, 0x40, 
    0x40, 0xa0, 0x00, 0x40, 
    0x00, 0x40, 0x00, 0x00, 
};

const s8 robotrunnerFrame0MetaSprites[] = 
{
    -8, -15, 0,
    0, -15, 2,
    -12, 1, 4,
    -4, 1, 6,
    4, 1, 8,
    (s8)0x80 // end marker
};

const s8 robotrunnerFrame1MetaSprites[] = 
{
    -8, -16, 0,
    0, -16, 2,
    -12, 0, 10,
    -4, 0, 12,
    4, 0, 14,
    (s8)0x80 // end marker
};

const s8 robotrunnerFrame2MetaSprites[] = 
{
    -8, -15, 16,
    0, -15, 18,
    -11, 1, 20,
    -3, 1, 22,
    5, 1, 24,
    (s8)0x80 // end marker
};

const s8 robotrunnerFrame3MetaSprites[] = 
{
    -8, -16, 16,
    0, -16, 18,
    -11, 0, 26,
    -3, 0, 28,
    5, 0, 30,
    (s8)0x80 // end marker
};

extern const MetaSpriteAnimationFrame robotrunnerFrame0;
extern const MetaSpriteAnimationFrame robotrunnerFrame1;
extern const MetaSpriteAnimationFrame robotrunnerFrame2;
extern const MetaSpriteAnimationFrame robotrunnerFrame3;


const MetaSpriteAnimationFrame robotrunnerFrame0 = 
{
    robotrunnerFrame0MetaSprites,
    5, // frame time
    &robotrunnerFrame1, // next frame
};

const MetaSpriteAnimationFrame robotrunnerFrame1 = 
{
    robotrunnerFrame1MetaSprites,
    5, // frame time
    &robotrunnerFrame0, // next frame
};

const MetaSpriteAnimationFrame robotrunnerFrame2 = 
{
    robotrunnerFrame2MetaSprites,
    5, // frame time
    &robotrunnerFrame3, // next frame
};

const MetaSpriteAnimationFrame robotrunnerFrame3 = 
{
    robotrunnerFrame3MetaSprites,
    5, // frame time
    &robotrunnerFrame2, // next frame
};
const MetaSpriteAnimationFrame* const robotrunnerFrames[4] = 
{
    &robotrunnerFrame0,
    &robotrunnerFrame1,
    &robotrunnerFrame2,
    &robotrunnerFrame3,
};

const AnimationSetup const robotrunnerSetup = 
{
    DrawUtils_drawMetasprite,
    AnimationUtils_updateMetaSpriteAnimation,
    &robotrunnerFrame0,
    0,
    5,
};

u8 robotrunnerVdpLocation;

const MetaSpriteAnimation robotrunner = 
{
    METASPRITE_ANIMATION_RESOURCE_TYPE, 
    &robotrunnerSetup,
    (const MetaSpriteAnimationFrame** const)robotrunnerFrames,
    (unsigned char* const)robotrunnerTileData, // start of the sprite data
    4, // number of frames
    24, // width in pixels
    32, // height in pixels
    32, // the total amount of tiles in animation
    10, // the max amount of sprite tiles in a frame
    &robotrunnerVdpLocation,
};
