#include "resource_manager.h"
//#include "resource_types.h"

#include <string.h>

//#include "engine/base_types.h"
#include "engine/animation_utils.h"
#include "engine/map_load.h"

typedef void* (*LoadFunc)(const ResourceInfo* resourceInfo);
typedef void* (*SetupFunc)(struct game_object* gameObject, const ResourceInfo* resourceInfo);

LoadFunc ResourceManager_loadFunctions[NUM_RESOURCE_TYPES];
SetupFunc ResourceManager_setupFunctions[NUM_RESOURCE_TYPES];

OnResourceLoadedCallback ResourceManager_onResourceLoadedCallback = NULL;

const void printResourceTypeName(u8 resourceType)
{
	switch (resourceType)
	{
	case BATCHED_ANIMATION_RESOURCE_TYPE			: SMS_debugPrintf("Batched Animation"); return;
	case STREAMED_BATCHED_ANIMATION_RESOURCE_TYPE	: SMS_debugPrintf("Streamed Batched Animation"); return;
	case PLANE_ANIMATION_RESOURCE_TYPE				: SMS_debugPrintf("Plane Animation"); return;
	case TILE_ANIMATION_RESOURCE_TYPE				: SMS_debugPrintf("Tile Animation"); return;
	case MAP_RESOURCE_TYPE							: SMS_debugPrintf("Map"); return;
	case TILESET_RESOURCE_TYPE						: SMS_debugPrintf("Tileset"); return;
	case ANIMATED_TILESET_RESOURCE_TYPE				: SMS_debugPrintf("Animated Tileset"); return;
	}

	SMS_debugPrintf("Unknown");
}

void ResourceManager_Init(OnResourceLoadedCallback onResourceLoadedCallback)
{
	memset(ResourceManager_loadFunctions, 0, sizeof(ResourceManager_loadFunctions));
	memset(ResourceManager_setupFunctions, 0, sizeof(ResourceManager_setupFunctions));

	// Load
	ResourceManager_loadFunctions[BATCHED_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_BatchedAnimationResource;
	ResourceManager_loadFunctions[STREAMED_BATCHED_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_StreamedBatchedAnimationResource;
	ResourceManager_loadFunctions[PLANE_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_PlaneAnimationResource;
	ResourceManager_loadFunctions[TILE_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_TileAnimationResource;
	ResourceManager_loadFunctions[MAP_RESOURCE_TYPE] = (LoadFunc)Load_MapResource;
	ResourceManager_loadFunctions[TILESET_RESOURCE_TYPE] = (LoadFunc)Load_TilesetResource;
	ResourceManager_loadFunctions[ANIMATED_TILESET_RESOURCE_TYPE] = (LoadFunc)Load_AnimatedTilesetResource;

	// Setup
	ResourceManager_setupFunctions[BATCHED_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_BatchedAnimationResource;
	ResourceManager_setupFunctions[STREAMED_BATCHED_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_BatchedAnimationResource;
	ResourceManager_setupFunctions[PLANE_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_PlaneAnimationResource;
	ResourceManager_setupFunctions[TILE_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_TileAnimationResource;

	ResourceManager_SetOnResourceLoadedCallback(onResourceLoadedCallback);
}

void* ResourceManager_LoadResource(const ResourceInfo* resourceInfo)
{
	u8 currentBank = SMS_getROMBank();
	u8 bankNumber = resourceInfo->bankNumber;

	SMS_debugPrintf("ResourceManager_LoadResource().\n");

	if (currentBank != bankNumber)
	{
		SMS_debugPrintf("Switching to Bank %d.\n", bankNumber);
		SMS_mapROMBank(bankNumber);
	}

	u8 resourceType = resourceInfo->resource->resourceType;

	//SMS_debugPrintf("Load Resource 0x%x of type ", resourceInfo->resource);
	//printResourceTypeName(resourceType);
	//SMS_debugPrintf("\n");

	if (ResourceManager_loadFunctions[resourceType] == 0)
	{
		SMS_debugPrintf("Load function for resource type %d not found.\n", resourceType);
		while (1) {}
	}

	void* value = ResourceManager_loadFunctions[resourceType](resourceInfo);

	if (ResourceManager_onResourceLoadedCallback != NULL)
		ResourceManager_onResourceLoadedCallback(resourceInfo);

	if (currentBank != bankNumber)
	{
		//SMS_debugPrintf("Switching back to Bank %d\n", currentBank);
		SMS_mapROMBank(currentBank);
	}

	return value;
}

void* ResourceManager_SetupResource(struct game_object* gameObject, const ResourceInfo* resourceInfo)
{
	u8 currentBank = SMS_getROMBank();
	u8 bankNumber = resourceInfo->bankNumber;

	//SMS_debugPrintf("ResourceManager_SetupResource().\n");

	if (currentBank != bankNumber)
	{
		SMS_debugPrintf("Switching to Bank %d.\n", bankNumber);
		SMS_mapROMBank(bankNumber);
	}

	u8 resourceType = resourceInfo->resource->resourceType;

	//SMS_debugPrintf("Setup Resource 0x%x of type ", resourceInfo->resource);
	//printResourceTypeName(resourceType);
	//SMS_debugPrintf("\n");

	if (ResourceManager_setupFunctions[resourceType] == 0)
	{
		SMS_debugPrintf("Setup function for resource type %d not found.\n", resourceType);
		while (1) {}
	}

	void* result = ResourceManager_setupFunctions[resourceType](gameObject, resourceInfo);

	if (currentBank != bankNumber)
	{
		//SMS_debugPrintf("Switching back to Bank %d\n", currentBank);
		SMS_mapROMBank(currentBank);
	}

	return result;
}

void ResourceManager_SetOnResourceLoadedCallback(OnResourceLoadedCallback callback)
{
	ResourceManager_onResourceLoadedCallback = callback;
}