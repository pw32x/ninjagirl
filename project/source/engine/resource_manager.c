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

OnResourceLoadedCallback ResourceManager_onResourceLoadedCallback = NULL;

void ResourceManager_Init(OnResourceLoadedCallback onResourceLoadedCallback)
{
	memset(ResourceManager_loadFunctions, 0, sizeof(ResourceManager_loadFunctions));
	memset(ResourceManager_setupFunctions, 0, sizeof(ResourceManager_setupFunctions));

	ResourceManager_loadFunctions[REGULAR_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_AnimationResource;
	ResourceManager_loadFunctions[STREAMED_REGULAR_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_StreamedAnimationResource;
	ResourceManager_loadFunctions[BATCHED_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_BatchedAnimationResource;
	ResourceManager_loadFunctions[STREAMED_BATCHED_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_StreamedBatchedAnimationResource;
	ResourceManager_loadFunctions[PLANE_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_PlaneAnimationResource;
	ResourceManager_loadFunctions[TILE_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_TileAnimationResource;


	ResourceManager_loadFunctions[MAP_RESOURCE_TYPE] = (LoadFunc)Load_MapResource;
	ResourceManager_loadFunctions[TILESET_RESOURCE_TYPE] = (LoadFunc)Load_TilesetResource;
	ResourceManager_loadFunctions[ANIMATED_TILESET_RESOURCE_TYPE] = (LoadFunc)Load_AnimatedTilesetResource;

	ResourceManager_setupFunctions[REGULAR_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_AnimationResource;
	ResourceManager_setupFunctions[STREAMED_REGULAR_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_StreamedAnimationResource;
	ResourceManager_setupFunctions[BATCHED_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_BatchedAnimationResource;
	ResourceManager_setupFunctions[STREAMED_BATCHED_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_StreamedBatchedAnimationResource;
	ResourceManager_setupFunctions[PLANE_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_PlaneAnimationResource;
	ResourceManager_setupFunctions[TILE_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_TileAnimationResource;

	ResourceManager_SetOnResourceLoadedCallback(onResourceLoadedCallback);
}

void* ResourceManager_LoadResource(void* resource)
{
	u8 resourceType = *(const u8*)resource;

	if (ResourceManager_loadFunctions[resourceType] == 0)
	{
		while (1) {}
	}

	void* value = ResourceManager_loadFunctions[resourceType](resource);

	if (ResourceManager_onResourceLoadedCallback != NULL)
		ResourceManager_onResourceLoadedCallback(resource);

	return value;
}

void* ResourceManager_SetupResource(struct game_object* gameObject, const void* resource)
{
	u8 resourceType = *(const u8*)resource;

	if (ResourceManager_setupFunctions[resourceType] == 0)
	{
		while (1) {}
	}

	return ResourceManager_setupFunctions[resourceType](gameObject, resource);
}

void ResourceManager_SetOnResourceLoadedCallback(OnResourceLoadedCallback callback)
{
	ResourceManager_onResourceLoadedCallback = callback;
}