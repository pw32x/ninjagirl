#include "tile_animator.h"
#include "SMSlib.h"

#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"
#include "engine/resource_manager.h"
#include "engine/map_types.h"

#include <stdio.h>

void TileAnimator_Update(GameObject* object);

GameObject* TileAnimator_Create(const ResourceInfo* resourceInfo)
{
	GameObject* object = ObjectManager_CreateObject(OBJECTTYPE_EFFECT);
	if (!object)
		return NULL;

	object->Update = TileAnimator_Update;
	object->Draw = ObjectUtils_drawNothing;

	ResourceManager_SetupResource(object, resourceInfo);

	return object;
}

void UpdateTiles(GameObject* object)
{
	SMS_setBackdropColor(COLOR_PINK);

	// update for tiles at once
	const u8* sourceTileRunner = object->tileAnimation->tileData + 
								(object->currentTileAnimationFrame->tileIndex << 5);

	switch (object->tileAnimation->tilesPerFrame)
	{
	case 4:
		UNSAFE_SMS_load4Tiles(sourceTileRunner, *object->tileAnimation->vdpLocation);
	}

	SMS_setBackdropColor(COLOR_RED);
}

void TileAnimator_Update(GameObject* object)
{
	//if (object->UpdateAnimation(object))
	object->UpdateAnimation(object);
	{
		ObjectManager_QueueVDPDraw(object, UpdateTiles);
	}
}
