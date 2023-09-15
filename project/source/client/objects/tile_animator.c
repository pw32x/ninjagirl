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


void TileAnimator_Update(GameObject* object);
void TileAnimator_Draw(GameObject* object);

GameObject* TileAnimator_Create(const Animation* animation)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_EFFECT);
	if (!object)
		return NULL;

	object->Update = TileAnimator_Update;
	object->Draw = TileAnimator_Draw;

	ResourceManager_SetupResource(object, animation);

	return object;
}

void UpdateTiles(GameObject* object)
{
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
}

void TileAnimator_Update(GameObject* object)
{
	/*
	s16 screenLeft = object->x - ScrollManager_horizontalScroll;

	if (screenLeft < SCREEN_LEFT)
	{
		ObjectManager_DestroyObject(object);
		return;
	}
	*/

	if (object->UpdateAnimation(object))
		ObjectManager_QueueVDPDraw(object, UpdateTiles);
}

void TileAnimator_Draw(GameObject* object)
{
	
}

