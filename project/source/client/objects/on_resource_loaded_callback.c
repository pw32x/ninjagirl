#include "on_resource_loaded_callback.h"
#include "resource_types.h"

#include "tile_animator.h"

void* OnResourceLoaded(u8* resource)
{
	u8 resourceType = *resource;

	switch (resourceType)
	{
	case TILE_ANIMATION_RESOURCE_TYPE:
		TileAnimator_Create((TileAnimation*)resource);
		break;
	}

	return NULL;
}