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


typedef struct animation_frame_streamed
{
    const AnimationSprite* const sprites;
    u8 numSprites;
    u8 tileIndex;
    u8 frameTime;
    struct animation_frame_streamed* nextFrame;
} AnimationFrameStreamed;

typedef struct
{
    u8 resourceType;
    const AnimationFrameStreamed** const frames;
    const u8* const tileData;

    u8 numFrames;
    u8 pixelWidth;
    u8 pixelHeight;
    u8 totalTileCount;
    u8 maxTilesInFrame;
    u8* vdpLocation;
} AnimationStreamed;

// batched. a sprite call contains multiple sprites. for use with the SMS_add***AdjoiningSprites functions.

typedef struct 
{
    u8 count;
    AnimationSprite sprite;
} AnimationSpriteBatched;

typedef struct animation_frame_batched
{
    const AnimationSpriteBatched* const spriteBatch;
    u8 frameTime;
    struct animation_frame_batched* nextFrame;
} AnimationFrameBatched;


typedef struct
{
    u8 resourceType;
    const AnimationFrameBatched** const frames;
    const u8* const tileData;

    u8 numFrames;
    u8 pixelWidth;
    u8 pixelHeight;
    //u8 maxTilesPerFrame;

    u8 totalTileCount;
    u8* vdpLocation;

} AnimationBatched;



// special "streamed" animation type that only upates one frame at a time to VDP

typedef struct animation_frame_batched_streamed
{
    const AnimationSpriteBatched* const spriteBatch;
    u8 tileIndex;
    u8 frameTime;
    struct animation_frame_batched_streamed* nextFrame;
} AnimationFrameBatchedStreamed;


typedef struct
{
    u8 resourceType;
    const AnimationFrameBatchedStreamed** const frames;
    const u8* const tileData;

    u8 numFrames;
    u8 pixelWidth;
    u8 pixelHeight;

    u8 totalTileCount;
    u8 maxTilesInFrame;
    u8* vdpLocation;
} AnimationBatchedStreamed;


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


#endif