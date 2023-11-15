#include "resource_manager.h"
#include "resource_types.h"

#include <string.h>

#include "engine/base_types.h"
#include "engine/animation_utils.h"
#include "engine/map_load.h"

typedef void* (*LoadFunc)(const void* resource);
typedef void* (*SetupFunc)(struct game_object* gameObject, const void* resource);

u16 Load_ResourceInfo(const void* resource);
u16 Setup_ResourceInfo(struct game_object* gameObject, const void* resource);

LoadFunc ResourceManager_loadFunctions[NUM_RESOURCE_TYPES];
SetupFunc ResourceManager_setupFunctions[NUM_RESOURCE_TYPES];

OnResourceLoadedCallback ResourceManager_onResourceLoadedCallback = NULL;

void ResourceManager_Init(OnResourceLoadedCallback onResourceLoadedCallback)
{
	memset(ResourceManager_loadFunctions, 0, sizeof(ResourceManager_loadFunctions));
	memset(ResourceManager_setupFunctions, 0, sizeof(ResourceManager_setupFunctions));

	ResourceManager_loadFunctions[RESOURCE_INFO_RESOURCE_TYPE] = (LoadFunc)Load_ResourceInfo;
	ResourceManager_loadFunctions[REGULAR_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_AnimationResource;
	ResourceManager_loadFunctions[STREAMED_REGULAR_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_StreamedAnimationResource;
	ResourceManager_loadFunctions[BATCHED_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_BatchedAnimationResource;
	ResourceManager_loadFunctions[STREAMED_BATCHED_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_StreamedBatchedAnimationResource;
	ResourceManager_loadFunctions[PLANE_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_PlaneAnimationResource;
	ResourceManager_loadFunctions[TILE_ANIMATION_RESOURCE_TYPE] = (LoadFunc)Load_TileAnimationResource;


	ResourceManager_loadFunctions[MAP_RESOURCE_TYPE] = (LoadFunc)Load_MapResource;
	ResourceManager_loadFunctions[TILESET_RESOURCE_TYPE] = (LoadFunc)Load_TilesetResource;
	ResourceManager_loadFunctions[ANIMATED_TILESET_RESOURCE_TYPE] = (LoadFunc)Load_AnimatedTilesetResource;

	ResourceManager_setupFunctions[RESOURCE_INFO_RESOURCE_TYPE] = (SetupFunc)Setup_ResourceInfo;
	ResourceManager_setupFunctions[REGULAR_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_AnimationResource;
	ResourceManager_setupFunctions[STREAMED_REGULAR_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_StreamedAnimationResource;
	ResourceManager_setupFunctions[BATCHED_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_BatchedAnimationResource;
	ResourceManager_setupFunctions[STREAMED_BATCHED_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_StreamedBatchedAnimationResource;
	ResourceManager_setupFunctions[PLANE_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_PlaneAnimationResource;
	ResourceManager_setupFunctions[TILE_ANIMATION_RESOURCE_TYPE] = (SetupFunc)Setup_TileAnimationResource;

	ResourceManager_SetOnResourceLoadedCallback(onResourceLoadedCallback);
}

u16 Load_ResourceInfo(const void* resource)
{
	u8 currentBank = SMS_getROMBank();

	// Resource Info has information about which bank the inner resource is stored
	// in rom.
	
	const ResourceInfo* resourceInfo = (const ResourceInfo*)resource;
	u8 bankNumber = resourceInfo->bankNumber;

	// switch to the bank in the resource info before
	// doing the load

	if (currentBank != bankNumber)
	{
		SMS_mapROMBank(bankNumber);
	}

	SMS_debugPrintf("Loading from Bank: %d\n", bankNumber);

	u16 result = (u16)ResourceManager_LoadResource((void*)resourceInfo->resource);

	if (currentBank != bankNumber)
	{
		SMS_mapROMBank(currentBank);
	}

	return result;
}

u16 Setup_ResourceInfo(struct game_object* gameObject, const void* resource)
{
	u8 currentBank = SMS_getROMBank();

	// Resource Info has information about which bank the inner resource is stored
	// in rom.
	
	const ResourceInfo* resourceInfo = (const ResourceInfo*)resource;
	u8 bankNumber = resourceInfo->bankNumber;

	// switch to the bank in the resource info before
	// doing the load

	if (currentBank != bankNumber)
	{
		SMS_mapROMBank(bankNumber);
	}

	SMS_debugPrintf("Setting up resource from Bank: %d\n", bankNumber);

	u16 result = (u16)ResourceManager_SetupResource(gameObject, (void*)resourceInfo->resource);

	if (currentBank != bankNumber)
	{
		SMS_mapROMBank(currentBank);
	}

	return result;
}


void* ResourceManager_LoadResource(void* resource)
{
	u8 resourceType = *(const u8*)resource;

	SMS_debugPrintf("ResourceManager_LoadResource\n");
	SMS_debugPrintf("Load Resource 0x%x of type %d\n", resource, resourceType);

	if (ResourceManager_loadFunctions[resourceType] == 0)
	{
		while (1) {}
	}

	void* value = ResourceManager_loadFunctions[resourceType](resource);

	if (ResourceManager_onResourceLoadedCallback != NULL)
		ResourceManager_onResourceLoadedCallback(resource);

	SMS_debugPrintf("Finished with Bank: %d\n", SMS_getROMBank());

	return value;
}

void* ResourceManager_SetupResource(struct game_object* gameObject, const void* resource)
{
	u8 resourceType = *(const u8*)resource;

	SMS_debugPrintf("ResourceManager_SetupResource\n");
	SMS_debugPrintf("Setup Resource 0x%x of type %d\n", resource, resourceType);

	if (ResourceManager_setupFunctions[resourceType] == 0)
	{
		while (1) {}
	}

	void* result = ResourceManager_setupFunctions[resourceType](gameObject, resource);

	SMS_debugPrintf("Finished with Bank: %d\n", SMS_getROMBank());

	return result;
}

void ResourceManager_SetOnResourceLoadedCallback(OnResourceLoadedCallback callback)
{
	ResourceManager_onResourceLoadedCallback = callback;
}