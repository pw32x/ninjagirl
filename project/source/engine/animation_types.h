#ifndef ANIMATION_TYPES_INCLUDE_H
#define ANIMATION_TYPES_INCLUDE_H

#include "engine/base_types.h"

typedef struct
{
    s8 xOffset;
    s8 yOffset;
    u8 tileIndex;
} AnimationSprite;

typedef struct
{
    const AnimationSprite* const sprites;
    u8 numSprites;
    u8 frameTime;
} AnimationFrame;

typedef struct
{
    const AnimationFrame** const frames;
    const u8* const tileData;

    u8 numFrames;
    u8 pixelWidth;
    u8 pixelHeight;
    u8 maxTilesPerFrame;

    u8 totalTileCount;
	u16 totalAnimationTime;

} Animation;

#endif