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

GameObject* TileAnimator_Create(const SpawnInfo* spawnInfo)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_ENEMY);
	if (!object)
		return NULL;
	/*
	object->x = spawnInfo->startX;
	object->y = spawnInfo->startY;
	*/
	object->Update = TileAnimator_Update;
	object->Draw = TileAnimator_Draw;


	ResourceManager_SetupResource(object, spawnInfo->payload, spawnInfo->additionalPayload);
	/*
	object->rectLeft = 0;
	object->rectTop = 0;
	object->rectRight = object->pixelWidth;
	object->rectBottom = object->pixelHeight;
	*/

	object->animationTime = 8;

	return object;
}

extern const Animation water_tiles;
extern unsigned char const water_tilesTileData[];

extern unsigned char const ninja_girlTileData[];

void UpdateTiles(GameObject* object)
{
	//UNSAFE_SMS_load4Tiles(water_tilesTileData, 16);

	u8 numTilesToUpdate = ScrollManager_backgroundTileset->animatedTileIndexesCount;
	const u16* animatedTileIndexRunner = ScrollManager_backgroundTileset->animatedTileIndexes;
	const u8* sourceTileRunner = water_tilesTileData + (object->currentAnimationFrameIndex * 32 * 4);

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

	if (object->UpdateAnimation(object))
		ObjectManager_QueueVDPDraw(object, DrawUtils_DrawPlaneAnimationFrame);
	*/

	object->animationTime--;
	if (!object->animationTime)
	{
		object->currentAnimationFrameIndex++;

		if (object->currentAnimationFrameIndex == object->animationBatched->numFrames)
			object->currentAnimationFrameIndex = 0;

		ObjectManager_QueueVDPDraw(object, UpdateTiles);
		object->animationTime = 8;
	}
}

void TileAnimator_Draw(GameObject* object)
{
	
}

