#include "resource_manager.h"
#include "resource_types.h"

#include "engine/base_types.h"
#include "engine/animation_utils.h"
#include "engine/map_types.h"

typedef void* (*ResourceManagerLoaderFunction)(const void* resource);

ResourceManagerLoaderFunction ResourceManager_loadFunctions[NUM_RESOURCE_TYPES] =
{
	(ResourceManagerLoaderFunction)Load_AnimationResource,
	(ResourceManagerLoaderFunction)Load_BatchedAnimationResource,
	(ResourceManagerLoaderFunction)Load_PlaneAnimationResource,
	(ResourceManagerLoaderFunction)Load_MapResource,
};

typedef void* (*ResourceManagerSetupFunction)(struct game_object* gameObject, const void* resource);

ResourceManagerSetupFunction ResourceManager_setupFunctions[NUM_RESOURCE_TYPES] =
{
	(ResourceManagerSetupFunction)Setup_AnimationResource,
	(ResourceManagerSetupFunction)Setup_BatchedAnimationResource,
	(ResourceManagerSetupFunction)Setup_PlaneAnimationResource,
	(ResourceManagerSetupFunction)NULL,
};

void ResourceManager_Init(void)
{

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