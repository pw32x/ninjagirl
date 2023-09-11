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
    u8 resourceType;
    const AnimationFrame** const frames;
    const u8* const tileData;

	u16 totalAnimationTime;

    u8 numFrames;
    u8 pixelWidth;
    u8 pixelHeight;
    //u8 maxTilesPerFrame;

    u8 totalTileCount;
    u8* vdpLocation;
} Animation;



typedef struct 
{
    u8 count;
    AnimationSprite sprite;
} AnimationSpriteBatched;

typedef struct
{
    const AnimationSpriteBatched* const spriteBatch;
    u8 frameTime;
} AnimationFrameBatched;


typedef struct
{
    u8 resourceType;
    const AnimationFrameBatched** const frames;
    const u8* const tileData;

	u16 totalAnimationTime;

    u8 numFrames;
    u8 pixelWidth;
    u8 pixelHeight;
    //u8 maxTilesPerFrame;

    u8 totalTileCount;
    u8* vdpLocation;

} AnimationBatched;

typedef struct plane_animation_frame
{
    const u16* frameTilemap;
    u8 frameTime;
    struct plane_animation_frame* nextFrame;
} PlaneAnimationFrame;

typedef struct
{
    u8 resourceType;
    const PlaneAnimationFrame** frames;
    u8 numFrames;
    u8 tileWidth;
    u8 tileHeight;
    u8 totalTileCount;
    const u8* const tileData;
    u16* vdpLocation;
} PlaneAnimation;


#endif