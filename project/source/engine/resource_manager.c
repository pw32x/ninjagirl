#include "resource_manager.h"
#include "resource_types.h"

#include <string.h>

#include "engine/base_types.h"
#include "engine/animation_utils.h"
#include "engine/map_types.h"

typedef void* (*LoadFunc)(const void* resource);
typedef void* (*SetupFunc)(struct game_object* gameObject, const void* resource);

LoadFunc ResourceManager_loadFunctions[NUM_RESOURCE_TYPES];
SetupFunc ResourceManager_setupFunctions[NUM_RESOURCE_TYPES];

void ResourceManager_Init(void)
{
	memset(ResourceManager_loadFunctions, 0, sizeof(ResourceManager_loadFunctions));
	memset(ResourceManager_setupFunctions, 0, sizeof(ResourceManager_setupFunctions));

	ResourceManager_loadFunctions[REGULAR_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_AnimationResource;
	ResourceManager_loadFunctions[STREAMED_REGULAR_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_StreamedAnimationResource;
	ResourceManager_loadFunctions[BATCHED_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_BatchedAnimationResource;
	ResourceManager_loadFunctions[STREAMED_BATCHED_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_StreamedBatchedAnimationResource;
	ResourceManager_loadFunctions[PLANE_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_PlaneAnimationResource;
	ResourceManager_loadFunctions[MAP_RESOURCE_TYPE] = (LoadFunc)Load_MapResource;


	ResourceManager_setupFunctions[REGULAR_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_AnimationResource;
	ResourceManager_setupFunctions[STREAMED_REGULAR_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_StreamedAnimationResource;
	ResourceManager_setupFunctions[BATCHED_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_BatchedAnimationResource;
	ResourceManager_setupFunctions[STREAMED_BATCHED_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_StreamedBatchedAnimationResource;
	ResourceManager_setupFunctions[PLANE_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_PlaneAnimationResource;
}

void* ResourceManager_LoadResource(void* resource)
{
	u8 resourceType = *(const u8*)resource;

	return ResourceManager_loadFunctions[resourceType](resource);
}

void* ResourceManager_SetupResource(struct game_object* gameObject, const void* resource)
{
	u8 resourceType = *(const u8*)resource;

	return ResourceManager_setupFunctions[resourceType](gameObject, resource);
}