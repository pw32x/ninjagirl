#include "on_resource_loaded_callback.h"
#include "resource_types.h"

#include "tile_animator.h"

void* OnResourceLoaded(const ResourceInfo* resourceInfo)
{
	u8 resourceType = resourceInfo->resource->resourceType;

	switch (resourceType)
	{
	case TILE_ANIMATION_RESOURCE_TYPE:
		TileAnimator_Init(resourceInfo);
		break;
	}

	return NULL;
}