#ifndef RESOURCE_TYPES_INCLUDE_H
#define RESOURCE_TYPES_INCLUDE_H

#include "engine/base_types.h"

#define RESOURCE(bank)

#define RESOURCE_INFO_RESOURCE_TYPE					0
#define REGULAR_ANIMATION_RESOURCE_TYPE				1
#define STREAMED_REGULAR_ANIMATION_RESOURCE_TYPE	2
#define BATCHED_ANIMATION_RESOURCE_TYPE				3
#define STREAMED_BATCHED_ANIMATION_RESOURCE_TYPE	4
#define PLANE_ANIMATION_RESOURCE_TYPE				5
#define TILE_ANIMATION_RESOURCE_TYPE				6
#define MAP_RESOURCE_TYPE							7
#define TILESET_RESOURCE_TYPE						8
#define ANIMATED_TILESET_RESOURCE_TYPE				9
#define NUM_RESOURCE_TYPES							10


typedef struct
{
	u8 resourceType;
} Resource;

typedef struct
{
	u8 resourceType;
	u8 bankNumber;
	const Resource* resource;
} ResourceInfo;

#endif