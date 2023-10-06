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

GameObject* TileAnimator_Create(const TileAnimation* tileAnimation)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_EFFECT);
	if (!object)
		return NULL;

	object->Update = TileAnimator_Update;
	object->Draw = ObjectUtils_drawNothing;

	ResourceManager_SetupResource(object, tileAnimation);

	return object;
}

void UpdateTiles(GameObject* object)
{
	SMS_setBackdropColor(COLOR_PINK);
	/*
	
	u8 numTilesToUpdate = ScrollManager_backgroundTileset->animatedTileIndexesCount;
	const u16* animatedTileIndexRunner = ScrollManager_backgroundTileset->animatedTileIndexes;

	const u8* sourceTileRunner = object->animation->tileData + 
								(object->currentAnimationFrame->sprites->tileIndex << 5);

	for (u8 loop = 0; loop < numTilesToUpdate; loop++)
	{
		UNSAFE_SMS_load1Tile(sourceTileRunner, *animatedTileIndexRunner);

		sourceTileRunner += 32;
		animatedTileIndexRunner++;
	}
	*/

/*
	u8 numTilesToUpdate = 4;//ScrollManager_backgroundTileset->animatedTileIndexesCount;

	u16 animatedTileIndexes[4];
	animatedTileIndexes[0] = 0;
	animatedTileIndexes[1] = 1;
	animatedTileIndexes[2] = 2;
	animatedTileIndexes[3] = 3;

	const u16* animatedTileIndexRunner = animatedTileIndexes;

	const u8* sourceTileRunner = object->animation->tileData;

	for (u8 loop = 0; loop < numTilesToUpdate; loop++)
	{
		UNSAFE_SMS_load1Tile(sourceTileRunner, *animatedTileIndexRunner);

		//sourceTileRunner += 32;
		animatedTileIndexRunner++;
	}
	*/

	/*
	// update for tiles at once
	const u8* sourceTileRunner = object->animation->tileData + 
								(object->currentAnimationFrame->sprites->tileIndex << 5);

	UNSAFE_SMS_load4Tiles(sourceTileRunner, *ScrollManager_backgroundTileset->animatedTileIndexes);
	*/
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
