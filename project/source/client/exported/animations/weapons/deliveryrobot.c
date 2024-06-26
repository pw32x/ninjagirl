#include "deliveryrobot.h"
#include "engine\draw_utils.h"
#include "engine\animation_types.h"
#include "engine\animation_utils.h"


unsigned char const deliveryrobotTileData[1152] = // 36tiles x 32 bytes
{
// tile: 0
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x1e, 0x1e, 0x1e, 
    0x0e, 0x6f, 0x7f, 0x7f, 
    0x3f, 0xbf, 0xff, 0xff, 
    0x00, 0x7f, 0x7f, 0x7f, 
    0x00, 0x04, 0x00, 0x03, 
    0x00, 0x0a, 0x00, 0x05, 
    0x00, 0x0c, 0x00, 0x03, 
// tile: 1
    0x00, 0x0a, 0x00, 0x05, 
    0x01, 0x0c, 0x00, 0x02, 
    0x03, 0x01, 0x1c, 0x00, 
    0x1f, 0x03, 0x21, 0x18, 
    0x1f, 0x07, 0x21, 0x11, 
    0x1f, 0x07, 0x21, 0x11, 
    0x0f, 0x03, 0x11, 0x08, 
    0x03, 0x01, 0x1c, 0x00, 
// tile: 2
    0x00, 0x18, 0x00, 0x00, 
    0x18, 0x24, 0x00, 0x18, 
    0x18, 0xa5, 0x81, 0x99, 
    0x81, 0xe7, 0xdb, 0xc3, 
    0x18, 0xe7, 0x81, 0x99, 
    0x03, 0x3c, 0x03, 0xc3, 
    0x5d, 0x26, 0x5d, 0xdd, 
    0x01, 0x3e, 0x01, 0xc1, 
// tile: 3
    0x5d, 0x26, 0x5d, 0xdd, 
    0xc3, 0xdc, 0x02, 0x22, 
    0xe3, 0xe1, 0x1c, 0x00, 
    0xff, 0xf3, 0xe1, 0xc8, 
    0xff, 0x3f, 0x21, 0x21, 
    0xff, 0x3f, 0x21, 0x21, 
    0xff, 0xf3, 0xe1, 0xc8, 
    0xe3, 0xe1, 0x1c, 0x00, 
// tile: 4
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0xfe, 0xfe, 0xfe, 
    0xfc, 0xfd, 0xff, 0xff, 
    0x70, 0xf6, 0xfe, 0xfe, 
    0x80, 0x70, 0xf0, 0xf0, 
    0xe0, 0x30, 0xe0, 0xe0, 
    0xe0, 0x10, 0xe0, 0xe0, 
// tile: 5
    0xe0, 0x30, 0xe0, 0xe0, 
    0xe0, 0xd0, 0x20, 0x20, 
    0xe0, 0xe0, 0x10, 0x00, 
    0xf0, 0xf0, 0xe8, 0xc0, 
    0xf8, 0x38, 0x20, 0x20, 
    0xf8, 0x38, 0x20, 0x20, 
    0xf0, 0xf0, 0xe8, 0xc0, 
    0xe0, 0xe0, 0x10, 0x00, 
// tile: 6
    0x1c, 0xcf, 0x00, 0x20, 
    0x00, 0xa4, 0x00, 0x5b, 
    0x02, 0xc8, 0x02, 0x37, 
    0x00, 0x68, 0x00, 0x17, 
    0x62, 0x18, 0x02, 0x27, 
    0xc8, 0x07, 0x30, 0x40, 
    0xb8, 0x00, 0x40, 0x30, 
    0xfc, 0x00, 0x00, 0x40, 
// tile: 7
    0x5e, 0x04, 0x2c, 0x0c, 
    0xff, 0x02, 0x5e, 0x5e, 
    0xff, 0x22, 0x62, 0x62, 
    0xf7, 0x22, 0x62, 0x62, 
    0x7b, 0x10, 0x30, 0x30, 
    0x30, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 8
    0x0e, 0xfd, 0x02, 0x02, 
    0xf6, 0x1b, 0xf6, 0xf6, 
    0x76, 0x09, 0x76, 0xf6, 
    0xf4, 0x1a, 0xf4, 0xf4, 
    0x70, 0x0c, 0x70, 0xf0, 
    0x00, 0xf8, 0x00, 0x00, 
    0xb8, 0x00, 0x40, 0x30, 
    0xfc, 0x00, 0x00, 0x40, 
// tile: 9
    0x5e, 0x04, 0x2c, 0x0c, 
    0xff, 0x02, 0x5e, 0x5e, 
    0xff, 0x22, 0x62, 0x62, 
    0xf7, 0x22, 0x62, 0x62, 
    0x7b, 0x10, 0x30, 0x30, 
    0x30, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 10
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x0f, 0x0f, 0x0f, 
    0x00, 0x06, 0x07, 0x07, 
    0x00, 0x01, 0x01, 0x01, 
    0x00, 0x0f, 0x00, 0x00, 
    0x00, 0x10, 0x00, 0x0f, 
    0x01, 0x28, 0x01, 0x17, 
    0x00, 0x30, 0x00, 0x0f, 
// tile: 11
    0x01, 0x28, 0x01, 0x17, 
    0x07, 0x33, 0x00, 0x08, 
    0x0f, 0x07, 0x70, 0x00, 
    0x7f, 0x0f, 0x87, 0x63, 
    0x7f, 0x1c, 0x84, 0x44, 
    0x7f, 0x1c, 0x84, 0x44, 
    0x3f, 0x0f, 0x47, 0x23, 
    0x0f, 0x07, 0x70, 0x00, 
// tile: 12
    0x00, 0x60, 0x00, 0x00, 
    0x00, 0xf8, 0xf8, 0xf8, 
    0xf0, 0xf4, 0xfc, 0xfc, 
    0x60, 0x68, 0xf8, 0xf8, 
    0x00, 0xff, 0xfe, 0xfe, 
    0x00, 0xff, 0x7f, 0x7f, 
    0x77, 0x98, 0x77, 0x77, 
    0x07, 0xf8, 0x07, 0x07, 
// tile: 13
    0x77, 0x98, 0x77, 0x77, 
    0x0f, 0x73, 0x08, 0x88, 
    0x8f, 0x87, 0x70, 0x00, 
    0xff, 0xcf, 0x87, 0x23, 
    0xff, 0xfc, 0x84, 0x84, 
    0xff, 0xfc, 0x84, 0x84, 
    0xff, 0xcf, 0x87, 0x23, 
    0x8f, 0x87, 0x70, 0x00, 
// tile: 14
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x80, 0x00, 0x00, 
    0x80, 0xc0, 0x80, 0x80, 
    0x80, 0x40, 0x80, 0x80, 
// tile: 15
    0x80, 0xc0, 0x80, 0x80, 
    0x80, 0x40, 0x80, 0x80, 
    0x80, 0x80, 0x40, 0x00, 
    0xc0, 0xc0, 0xa0, 0x00, 
    0xe0, 0xe0, 0x80, 0x80, 
    0xe0, 0xe0, 0x80, 0x80, 
    0xc0, 0xc0, 0xa0, 0x00, 
    0x80, 0x80, 0x40, 0x00, 
// tile: 16
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x7f, 0x7f, 0x7f, 
    0x3f, 0xbf, 0xff, 0xff, 
    0x0e, 0x6f, 0x7f, 0x7f, 
    0x01, 0x0e, 0x0f, 0x0f, 
    0x07, 0x0c, 0x07, 0x07, 
    0x07, 0x08, 0x07, 0x07, 
// tile: 17
    0x07, 0x0c, 0x07, 0x07, 
    0x07, 0x0b, 0x04, 0x04, 
    0x07, 0x07, 0x08, 0x00, 
    0x0f, 0x0f, 0x17, 0x03, 
    0x1f, 0x1c, 0x04, 0x04, 
    0x1f, 0x1c, 0x04, 0x04, 
    0x0f, 0x0f, 0x17, 0x03, 
    0x07, 0x07, 0x08, 0x00, 
// tile: 18
    0x00, 0x18, 0x00, 0x00, 
    0x18, 0x24, 0x00, 0x18, 
    0x18, 0xa5, 0x81, 0x99, 
    0x81, 0xe7, 0xdb, 0xc3, 
    0x18, 0xe7, 0x81, 0x99, 
    0xc0, 0x3c, 0xc0, 0xc3, 
    0xba, 0x64, 0xba, 0xbb, 
    0x80, 0x7c, 0x80, 0x83, 
// tile: 19
    0xba, 0x64, 0xba, 0xbb, 
    0xc3, 0x3b, 0x40, 0x44, 
    0xc7, 0x87, 0x38, 0x00, 
    0xff, 0xcf, 0x87, 0x13, 
    0xff, 0xfc, 0x84, 0x84, 
    0xff, 0xfc, 0x84, 0x84, 
    0xff, 0xcf, 0x87, 0x13, 
    0xc7, 0x87, 0x38, 0x00, 
// tile: 20
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x78, 0x78, 0x78, 
    0x70, 0xf6, 0xfe, 0xfe, 
    0xfc, 0xfd, 0xff, 0xff, 
    0x00, 0xfe, 0xfe, 0xfe, 
    0x00, 0x20, 0x00, 0xc0, 
    0x00, 0x50, 0x00, 0xa0, 
    0x00, 0x30, 0x00, 0xc0, 
// tile: 21
    0x00, 0x50, 0x00, 0xa0, 
    0x80, 0x30, 0x00, 0x40, 
    0xc0, 0x80, 0x38, 0x00, 
    0xf8, 0xc0, 0x84, 0x18, 
    0xf8, 0xe0, 0x84, 0x88, 
    0xf8, 0xe0, 0x84, 0x88, 
    0xf0, 0xc0, 0x88, 0x10, 
    0xc0, 0x80, 0x38, 0x00, 
// tile: 22
    0x70, 0xbf, 0x40, 0x40, 
    0x6f, 0xd8, 0x6f, 0x6f, 
    0x6e, 0x90, 0x6e, 0x6f, 
    0x2f, 0x58, 0x2f, 0x2f, 
    0x0e, 0x30, 0x0e, 0x0f, 
    0x00, 0x1f, 0x00, 0x00, 
    0x1d, 0x00, 0x02, 0x0c, 
    0x3f, 0x00, 0x00, 0x02, 
// tile: 23
    0x7a, 0x20, 0x34, 0x30, 
    0xff, 0x40, 0x7a, 0x7a, 
    0xff, 0x44, 0x46, 0x46, 
    0xef, 0x44, 0x46, 0x46, 
    0xde, 0x08, 0x0c, 0x0c, 
    0x0c, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 24
    0x38, 0xf3, 0x00, 0x04, 
    0x00, 0x25, 0x00, 0xda, 
    0x40, 0x13, 0x40, 0xec, 
    0x00, 0x16, 0x00, 0xe8, 
    0x46, 0x18, 0x40, 0xe4, 
    0x13, 0xe0, 0x0c, 0x02, 
    0x1d, 0x00, 0x02, 0x0c, 
    0x3f, 0x00, 0x00, 0x02, 
// tile: 25
    0x7a, 0x20, 0x34, 0x30, 
    0xff, 0x40, 0x7a, 0x7a, 
    0xff, 0x44, 0x46, 0x46, 
    0xef, 0x44, 0x46, 0x46, 
    0xde, 0x08, 0x0c, 0x0c, 
    0x0c, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 26
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x03, 0x03, 0x03, 
    0x01, 0x05, 0x07, 0x07, 
    0x00, 0x02, 0x03, 0x03, 
    0x00, 0x1f, 0x0f, 0x0f, 
    0x00, 0x3f, 0x1f, 0x1f, 
    0x3d, 0x63, 0x3d, 0x3d, 
    0x3c, 0x43, 0x3c, 0x3c, 
// tile: 27
    0x3d, 0x63, 0x3d, 0x3d, 
    0x3e, 0x59, 0x22, 0x22, 
    0x3e, 0x3c, 0x41, 0x00, 
    0x7f, 0x7e, 0xbc, 0x18, 
    0xff, 0xe7, 0x24, 0x24, 
    0xff, 0xe7, 0x24, 0x24, 
    0x7f, 0x7e, 0xbc, 0x18, 
    0x3e, 0x3c, 0x41, 0x00, 
// tile: 28
    0x00, 0xc0, 0x00, 0x00, 
    0x00, 0xfe, 0xfe, 0xfe, 
    0xe0, 0xec, 0xfc, 0xfc, 
    0xc0, 0xd0, 0xf0, 0xf0, 
    0x00, 0xfe, 0xe0, 0xe0, 
    0x00, 0xe1, 0xc0, 0xde, 
    0xd0, 0x22, 0xd0, 0xdd, 
    0x00, 0xe1, 0x00, 0x1e, 
// tile: 29
    0xd0, 0x22, 0xd0, 0xdd, 
    0x1c, 0xd9, 0x00, 0x22, 
    0x3e, 0x3c, 0xc1, 0x00, 
    0xff, 0x7e, 0x3c, 0x98, 
    0xff, 0xe7, 0x24, 0x24, 
    0xff, 0xe7, 0x24, 0x24, 
    0xff, 0x7e, 0x3c, 0x98, 
    0x3e, 0x3c, 0xc1, 0x00, 
// tile: 30
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x80, 0x00, 0x00, 
    0x00, 0x80, 0x00, 0x00, 
// tile: 31
    0x00, 0x80, 0x00, 0x00, 
    0x00, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0xc0, 0x00, 
    0xc0, 0x00, 0x20, 0xc0, 
    0xc0, 0x00, 0x20, 0x40, 
    0xc0, 0x00, 0x20, 0x40, 
    0x80, 0x00, 0x40, 0x80, 
    0x00, 0x00, 0xc0, 0x00, 
// tile: 32
    0x00, 0x3e, 0x00, 0x00, 
    0x1c, 0x42, 0x1c, 0x1c, 
    0x3e, 0x59, 0x22, 0x22, 
    0x3e, 0x3c, 0x41, 0x00, 
    0x7f, 0x7e, 0x3c, 0x18, 
    0x7f, 0x67, 0xa4, 0x24, 
    0xff, 0xe7, 0x24, 0x24, 
    0xff, 0xfe, 0x3c, 0x18, 
// tile: 33
    0x3e, 0x3c, 0xc1, 0x00, 
    0x38, 0x5f, 0x20, 0x20, 
    0x12, 0x49, 0x12, 0x12, 
    0x0c, 0x32, 0x0c, 0x0c, 
    0x00, 0x0c, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 34
    0x30, 0x00, 0x00, 0x00, 
    0x7b, 0x10, 0x30, 0x30, 
    0xf7, 0x22, 0x62, 0x62, 
    0xff, 0x22, 0x62, 0x62, 
    0xff, 0x02, 0x5e, 0x5e, 
    0x5e, 0x04, 0x2c, 0x0c, 
    0xfc, 0x00, 0x00, 0x40, 
    0xb8, 0x00, 0x40, 0x30, 
// tile: 35
    0x00, 0x7c, 0x00, 0x00, 
    0x38, 0x84, 0x38, 0x78, 
    0x78, 0x8c, 0x78, 0x78, 
    0x38, 0x84, 0x38, 0x78, 
    0x38, 0x4c, 0x38, 0x38, 
    0x00, 0x38, 0x00, 0x00, 
    0x00, 0x10, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
};

const s8 deliveryrobotFrame0MetaSprites[] = 
{
    -12, -16, 0,
    -4, -16, 2,
    4, -16, 4,
    -8, 0, 6,
    0, 0, 8,
    (s8)0x80 // end marker
};

const s8 deliveryrobotFrame1MetaSprites[] = 
{
    -10, -16, 10,
    -2, -16, 12,
    6, -16, 14,
    -8, 0, 6,
    0, 0, 8,
    (s8)0x80 // end marker
};

const s8 deliveryrobotFrame2MetaSprites[] = 
{
    -12, -16, 16,
    -4, -16, 18,
    4, -16, 20,
    -8, 0, 22,
    0, 0, 24,
    (s8)0x80 // end marker
};

const s8 deliveryrobotFrame3MetaSprites[] = 
{
    -9, -16, 26,
    -1, -16, 28,
    7, -16, 30,
    -8, 0, 22,
    0, 0, 24,
    (s8)0x80 // end marker
};

const s8 deliveryrobotFrame4MetaSprites[] = 
{
    -4, -6, 32,
    (s8)0x80 // end marker
};

const s8 deliveryrobotFrame5MetaSprites[] = 
{
    -4, -8, 34,
    (s8)0x80 // end marker
};

extern const MetaSpriteAnimationFrame deliveryrobotFrame0;
extern const MetaSpriteAnimationFrame deliveryrobotFrame1;
extern const MetaSpriteAnimationFrame deliveryrobotFrame2;
extern const MetaSpriteAnimationFrame deliveryrobotFrame3;
extern const MetaSpriteAnimationFrame deliveryrobotFrame4;
extern const MetaSpriteAnimationFrame deliveryrobotFrame5;


const MetaSpriteAnimationFrame deliveryrobotFrame0 = 
{
    deliveryrobotFrame0MetaSprites,
    4, // frame time
    &deliveryrobotFrame1, // next frame
};

const MetaSpriteAnimationFrame deliveryrobotFrame1 = 
{
    deliveryrobotFrame1MetaSprites,
    4, // frame time
    &deliveryrobotFrame0, // next frame
};

const MetaSpriteAnimationFrame deliveryrobotFrame2 = 
{
    deliveryrobotFrame2MetaSprites,
    4, // frame time
    &deliveryrobotFrame3, // next frame
};

const MetaSpriteAnimationFrame deliveryrobotFrame3 = 
{
    deliveryrobotFrame3MetaSprites,
    4, // frame time
    &deliveryrobotFrame2, // next frame
};

const MetaSpriteAnimationFrame deliveryrobotFrame4 = 
{
    deliveryrobotFrame4MetaSprites,
    4, // frame time
    &deliveryrobotFrame4, // next frame
};

const MetaSpriteAnimationFrame deliveryrobotFrame5 = 
{
    deliveryrobotFrame5MetaSprites,
    4, // frame time
    &deliveryrobotFrame5, // next frame
};
const MetaSpriteAnimationFrame* const deliveryrobotFrames[6] = 
{
    &deliveryrobotFrame0,
    &deliveryrobotFrame1,
    &deliveryrobotFrame2,
    &deliveryrobotFrame3,
    &deliveryrobotFrame4,
    &deliveryrobotFrame5,
};

const AnimationSetup const deliveryrobotSetup = 
{
    DrawUtils_drawMetasprite,
    AnimationUtils_updateMetaSpriteAnimation,
    &deliveryrobotFrame0,
    0,
    4,
};

u8 deliveryrobotVdpLocation;

const MetaSpriteAnimation deliveryrobot = 
{
    METASPRITE_ANIMATION_RESOURCE_TYPE, 
    &deliveryrobotSetup,
    (const MetaSpriteAnimationFrame** const)deliveryrobotFrames,
    (unsigned char* const)deliveryrobotTileData, // start of the sprite data
    6, // number of frames
    24, // width in pixels
    32, // height in pixels
    36, // the total amount of tiles in animation
    10, // the max amount of sprite tiles in a frame
    &deliveryrobotVdpLocation,
};
