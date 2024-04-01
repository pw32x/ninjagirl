#ifndef ANIMATION_TYPES_INCLUDE_H
#define ANIMATION_TYPES_INCLUDE_H

#include "engine/base_types.h"

struct game_object;

typedef struct
{
    void (*Draw)(struct game_object* gameObject);
    void (*UpdateAnimation)(struct game_object* gameObject);
    const void* startingAnimationFrame;
    u8 startAnimationFrameIndex;
    u8 animationTime;
} AnimationSetup;

// a sprite call contains multiple strips for use with the SMS_add***AdjoiningSprites functions.
typedef struct 
{
    u8 count;
    s8 xOffset;
    s8 yOffset;
    u8 tileIndex;
} BatchedAnimationSpriteStrip;


typedef struct batched_animation_frame
{
    const BatchedAnimationSpriteStrip* const spriteStrips;
    u8 frameTime;
    struct batched_animation_frame* nextFrame;
    u8 frameNumber;
} BatchedAnimationFrame;


typedef struct
{
    u8 resourceType;
    const AnimationSetup* animationSetup;
    const BatchedAnimationFrame** const frames;
    const u8* const tileData;

    u8 numFrames;
    u8 pixelWidth;
    u8 pixelHeight;
    u8 totalTileCount;
    u8 maxTilesPerFrame;
    u8* vdpLocation;
} BatchedAnimation;

// devkitSMS metasprites
typedef struct metasprite_animation_frame
{
    const s8* metaSprite;
    u8 frameTime;
    struct metasprite_animation_frame* nextFrame;
} MetaSpriteAnimationFrame;


typedef struct
{
    u8 resourceType;
    const AnimationSetup* animationSetup;
    const MetaSpriteAnimationFrame** const frames;
    const u8* const tileData;

    u8 numFrames;
    u8 pixelWidth;
    u8 pixelHeight;
    u8 totalTileCount;
    u8 maxTilesPerFrame;
    u8* vdpLocation;
} MetaSpriteAnimation;


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
    u8 tileIndex;
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
    u16* vdpLocation;
} TileAnimation;


#endif