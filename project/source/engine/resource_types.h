#ifndef RESOURCE_TYPES_INCLUDE_H
#define RESOURCE_TYPES_INCLUDE_H

#include "engine/base_types.h"

#define RESOURCE(bank)

#define BATCHED_ANIMATION_RESOURCE_TYPE				0
#define METASPRITE_ANIMATION_RESOURCE_TYPE			1
#define STREAMED_BATCHED_ANIMATION_RESOURCE_TYPE	2	
#define PLANE_ANIMATION_RESOURCE_TYPE				3
#define TILE_ANIMATION_RESOURCE_TYPE				4
#define MAP_RESOURCE_TYPE							5
#define TILESET_RESOURCE_TYPE						6
#define ANIMATED_TILESET_RESOURCE_TYPE				7
#define PALETTE_RESOURCE_TYPE						8
#define NUM_RESOURCE_TYPES							9


typedef struct
{
	u8 resourceType;
} Resource;

typedef struct
{
	u8 bankNumber;
	const Resource* resource;
} ResourceInfo;

#endif