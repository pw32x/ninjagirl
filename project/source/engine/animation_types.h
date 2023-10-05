#ifndef ANIMATION_TYPES_INCLUDE_H
#define ANIMATION_TYPES_INCLUDE_H

#include "engine/base_types.h"


typedef struct
{
    s8 xOffset;
    s8 yOffset;
    u8 tileIndex;
} AnimationSprite;

typedef struct animation_frame
{
    const AnimationSprite* const sprites;
    u8 numSprites;
    u8 frameTime;
    struct animation_frame* nextFrame;
} AnimationFrame;

typedef struct
{
    u8 resourceType;
    const AnimationFrame** const frames;
    const u8* const tileData;

    u8 numFrames;
    u8 pixelWidth;
    u8 pixelHeight;
    //u8 maxTilesPerFrame;

    u8 totalTileCount;
    u8* vdpLocation;
} Animation;

// streamed version


typedef struct streamed_animation_frame
{
    const AnimationSprite* const sprites;
    u8 numSprites;
    u8 tileIndex;
    u8 frameTime;
    struct streamed_animation_frame* nextFrame;
} StreamedAnimationFrame;

typedef struct
{
    u8 resourceType;
    const StreamedAnimationFrame** const frames;
    const u8* const tileData;

    u8 numFrames;
    u8 pixelWidth;
    u8 pixelHeight;
    u8 totalTileCount;
    u8 maxTilesInFrame;
    u8* vdpLocation;
} StreamedAnimation;

// batched. a sprite call contains multiple sprites. for use with the SMS_add***AdjoiningSprites functions.

typedef struct 
{
    u8 count;
    AnimationSprite sprite;
} BatchedAnimationSprite;

typedef struct batched_animation_frame
{
    const BatchedAnimationSprite* const batchedSprite;
    u8 frameTime;
    struct batched_animation_frame* nextFrame;
} BatchedAnimationFrame;


typedef struct
{
    u8 resourceType;
    const BatchedAnimationFrame** const frames;
    const u8* const tileData;

    u8 numFrames;
    u8 pixelWidth;
    u8 pixelHeight;
    //u8 maxTilesPerFrame;

    u8 totalTileCount;
    u8* vdpLocation;

} BatchedAnimation;



// special "streamed" animation type that only upates one frame at a time to VDP

typedef struct streamed_batched_animation_frame
{
    const BatchedAnimationSprite* const batchedSprites;
    u8 tileIndex;
    u8 frameTime;
    struct streamed_batched_animation_frame* nextFrame;
} StreamedBatchedAnimationFrame;


typedef struct
{
    u8 resourceType;
    const StreamedBatchedAnimationFrame** const frames;
    const u8* const tileData;

    u8 numFrames;
    u8 pixelWidth;
    u8 pixelHeight;

    u8 totalTileCount;
    u8 maxTilesInFrame;
    u8* vdpLocation;
} StreamedBatchedAnimation;


// plane

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

// tile animation

typedef struct tile_animation_frame
{
    u8 tileDataIndex;
    u8 frameTime;
    struct tile_animation_frame* nextFrame;
} TileAnimationFrame;

typedef struct
{
    u8 resourceType;
    const TileAnimationFrame** const frames;
    const u8* const tileData;
    u8 numFrames;
    u8 tilesPerFrame;
    u8 totalTileCount;
    u8* vdpLocation;
} TileAnimation;


#endif