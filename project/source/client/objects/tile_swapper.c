#include "tile_swapper.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"
#include "engine/resource_manager.h"
#include "engine/map_types.h"


void TileSwapper_Update(GameObject* object);
BOOL TileSwapper_Draw(GameObject* object);

GameObject* TileSwapper_Create(const Animation* animation)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_EFFECT);
	if (!object)
		return NULL;

	object->Update = TileSwapper_Update;
	object->Draw = TileSwapper_Draw;

	ResourceManager_SetupResource(object, animation);

	return object;
}

void TileSwapper_UpdateTiles(GameObject* object)
{
	/*
	u8 numTilesToUpdate = ScrollManager_backgroundTileset->animatedTileIndexesCount;
	const u16* animatedTileIndexRunner = ScrollManager_backgroundTileset->animatedTileIndexes;

	const u8* sourceTileRunner = object->animation->tileData + 
								((object->currentAnimationFrameIndex << 5) * object->currentAnimationFrame->numSprites);

	for (u8 loop = 0; loop < numTilesToUpdate; loop++)
	{
		UNSAFE_SMS_load1Tile(sourceTileRunner, *animatedTileIndexRunner);

		sourceTileRunner += 32;
		animatedTileIndexRunner++;
	}
	*/
}

void TileSwapper_Update(GameObject* object)
{
	if (object->UpdateAnimation(object))
		ObjectManager_QueueVDPDraw(object, TileSwapper_UpdateTiles);
}

BOOL TileSwapper_Draw(GameObject* object)
{
	return TRUE;
}

