#ifndef MATH_UTILS_INCLUDE_H
#define MATH_UTILS_INCLUDE_H

#include "engine/base_types.h"

typedef s32 POSITION;
typedef s16 POSITION_PIXEL;

#define VIRTUAL_SIZE 4

#define PIXEL_TO_VIRTUAL(value) ((value) << 4) // 16 virtual pixels per on screen pixel
#define PIXEL_TO_TILE(value)    ((value) >> 3) // 8 pixels per tile
#define PIXEL_TO_BLOCK(value)    ((value) >> 4) // 16 pixels per block

#define VIRTUAL_TO_PIXEL(value) ((value) >> 4) // 16 virtual pixels per on screen pixel
#define VIRTUAL_TO_TILE(value)  ((value) >> 7) // 16 virtual pixels per pixel, 8 pixels per tile
#define VIRTUAL_TO_BLOCK(value)  ((value) >> 8) // 16 virtual pixels per pixel, 8 pixels per tile, 2 tiles per block

#define TILE_TO_PIXEL(value)    ((value) << 3) // 8 pixels per tile
#define TILE_TO_VIRTUAL(value)  ((value) << 7) // 64 virtual pixels per pixel, 8 pixels per tile
#define TILE_TO_BLOCK(value)    ((value) >> 1) // 2 tiles per block pixels per tile

#define BLOCK_TO_PIXEL(value)    ((value) << 4) // 16 pixels per block
#define BLOCK_TO_VIRTUAL(value)  ((value) << 8) // 162 virtual pixels per pixel, 16 pixels per block
#define BLOCK_TO_TILE(value)    ((value) << 1) // 2 tiles per block pixels per tile

#define P2V(value) PIXEL_TO_VIRTUAL(value)
#define P2T(value) PIXEL_TO_TILE(value)
#define P2B(value) PIXEL_TO_BLOCK(value)

#define V2P(value) VIRTUAL_TO_PIXEL(value)
#define V2T(value) VIRTUAL_TO_TILE(value)
#define V2B(value) VIRTUAL_TO_BLOCK(value)

#define T2V(value) TILE_TO_VIRTUAL(value)
#define T2P(value) TILE_TO_PIXEL(value)
#define T2B(value) TILE_TO_BLOCK(value)

#define B2V(value) BLOCK_TO_VIRTUAL(value)
#define B2P(value) BLOCK_TO_PIXEL(value)
#define B2T(value) BLOCK_TO_TILE(value)

#endif