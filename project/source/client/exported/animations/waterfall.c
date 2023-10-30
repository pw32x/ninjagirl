#include "waterfall.h"


unsigned char const waterfallTileData[512] = // 16tiles x 32 bytes
{
// tile: 0
    0xff, 0x00, 0xff, 0xff, 
    0xfd, 0x00, 0xfd, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xef, 0x00, 0xef, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0x78, 0x00, 0x78, 0xff, 
    0x97, 0x83, 0x97, 0xff, 
    0x03, 0x00, 0x03, 0xff, 
// tile: 1
    0x00, 0x00, 0x00, 0xff, 
    0x60, 0x00, 0x60, 0xff, 
    0xb8, 0x00, 0xb8, 0xff, 
    0xce, 0x80, 0xce, 0xff, 
    0xf3, 0xc0, 0xf3, 0xff, 
    0xfc, 0xf0, 0xfc, 0xff, 
    0xff, 0xfc, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 
// tile: 2
    0xff, 0x7f, 0xff, 0xff, 
    0xff, 0x1f, 0xff, 0xff, 
    0x7f, 0x07, 0x7f, 0xff, 
    0x3f, 0x01, 0x3f, 0xff, 
    0x0f, 0x00, 0x0f, 0xff, 
    0x03, 0x00, 0x03, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
// tile: 3
    0x80, 0x00, 0x80, 0xff, 
    0x60, 0x00, 0x60, 0xff, 
    0xb8, 0x00, 0xb8, 0xff, 
    0xce, 0x80, 0xce, 0xff, 
    0xf3, 0xc0, 0xf3, 0xff, 
    0xfc, 0xf0, 0xfc, 0xff, 
    0xff, 0xfc, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 
// tile: 4
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xef, 0x00, 0xef, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xfd, 0x00, 0xfd, 0xff, 
    0xbf, 0x00, 0xbf, 0xff, 
    0xf8, 0x00, 0xf8, 0xff, 
    0x17, 0x07, 0x17, 0xff, 
// tile: 5
    0x7f, 0x1f, 0x7f, 0xff, 
    0x3f, 0x01, 0x3f, 0xff, 
    0x01, 0x00, 0x01, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
    0x80, 0x00, 0x80, 0xff, 
    0x60, 0x00, 0x60, 0xff, 
    0xb8, 0x00, 0xb8, 0xff, 
    0xce, 0x00, 0xce, 0xff, 
// tile: 6
    0xf3, 0xc0, 0xf3, 0xff, 
    0xfc, 0xf0, 0xfc, 0xff, 
    0xff, 0xfc, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 
    0xff, 0x7f, 0xff, 0xff, 
    0xff, 0x1f, 0xff, 0xff, 
    0x7f, 0x07, 0x7f, 0xff, 
    0x3f, 0x01, 0x3f, 0xff, 
// tile: 7
    0x0f, 0x00, 0x0f, 0xff, 
    0x03, 0x00, 0x03, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
    0x80, 0x00, 0x80, 0xff, 
    0x60, 0x00, 0x60, 0xff, 
    0xb8, 0x00, 0xb8, 0xff, 
    0xce, 0x00, 0xce, 0xff, 
// tile: 8
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xfb, 0x00, 0xfb, 0xff, 
    0xdf, 0x00, 0xdf, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xe0, 0x00, 0xe0, 0xff, 
    0x5f, 0x1f, 0x5f, 0xff, 
// tile: 9
    0xbf, 0xbf, 0xbf, 0xff, 
    0xff, 0x7f, 0xff, 0xff, 
    0x7f, 0x0f, 0x7f, 0xff, 
    0x3f, 0x03, 0x3f, 0xff, 
    0x0f, 0x00, 0x0f, 0xff, 
    0x03, 0x00, 0x03, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
// tile: 10
    0x80, 0x00, 0x80, 0xff, 
    0x60, 0x00, 0x60, 0xff, 
    0xb8, 0x00, 0xb8, 0xff, 
    0xce, 0x80, 0xce, 0xff, 
    0xf3, 0xc0, 0xf3, 0xff, 
    0xfc, 0xf0, 0xfc, 0xff, 
    0xff, 0xfc, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 
// tile: 11
    0xff, 0x7f, 0xff, 0xff, 
    0xff, 0x1f, 0xff, 0xff, 
    0x7f, 0x07, 0x7f, 0xff, 
    0x3f, 0x01, 0x3f, 0xff, 
    0x0f, 0x00, 0x0f, 0xff, 
    0x03, 0x00, 0x03, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
// tile: 12
    0xff, 0x00, 0xff, 0xff, 
    0xf7, 0x00, 0xf7, 0xff, 
    0xbf, 0x00, 0xbf, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xef, 0x00, 0xef, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0x70, 0x00, 0x70, 0xff, 
    0x80, 0x00, 0x80, 0xff, 
// tile: 13
    0xf8, 0x80, 0xf8, 0xff, 
    0xff, 0xf8, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 
    0xff, 0x7f, 0xff, 0xff, 
    0xff, 0x1f, 0xff, 0xff, 
    0x7f, 0x07, 0x7f, 0xff, 
    0x3f, 0x01, 0x3f, 0xff, 
// tile: 14
    0x0f, 0x00, 0x0f, 0xff, 
    0x03, 0x00, 0x03, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
    0x80, 0x00, 0x80, 0xff, 
    0x60, 0x00, 0x60, 0xff, 
    0xb8, 0x00, 0xb8, 0xff, 
    0xce, 0x80, 0xce, 0xff, 
// tile: 15
    0xf3, 0xc0, 0xf3, 0xff, 
    0xfc, 0xf0, 0xfc, 0xff, 
    0xff, 0xfc, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 
    0xff, 0x7f, 0xff, 0xff, 
    0xff, 0x1f, 0xff, 0xff, 
    0x7f, 0x07, 0x7f, 0xff, 
    0x3f, 0x01, 0x3f, 0xff, 
};

extern const TileAnimationFrame waterfallFrame0;
extern const TileAnimationFrame waterfallFrame1;
extern const TileAnimationFrame waterfallFrame2;
extern const TileAnimationFrame waterfallFrame3;

const TileAnimationFrame waterfallFrame0 = 
{
    0, // tile data index
    8, // frame time
    &waterfallFrame1, // next frame
};

const TileAnimationFrame waterfallFrame1 = 
{
    4, // tile data index
    8, // frame time
    &waterfallFrame2, // next frame
};

const TileAnimationFrame waterfallFrame2 = 
{
    8, // tile data index
    8, // frame time
    &waterfallFrame3, // next frame
};

const TileAnimationFrame waterfallFrame3 = 
{
    12, // tile data index
    8, // frame time
    &waterfallFrame0, // next frame
};
const TileAnimationFrame* const waterfallFrames[4] = 
{
    &waterfallFrame0,
    &waterfallFrame1,
    &waterfallFrame2,
    &waterfallFrame3,
};

u8 waterfallVdpLocation;

RESOURCE(BANK2) const TileAnimation waterfall = 
{
    TILE_ANIMATION_RESOURCE_TYPE, 
    (const TileAnimationFrame** const)waterfallFrames,
    (unsigned char* const)waterfallTileData, // start of the sprite data
    4, // number of frames
    4, // the max amount of sprite tiles in a frame
    16, // the total amount of tiles in animation
    &waterfallVdpLocation,
};
