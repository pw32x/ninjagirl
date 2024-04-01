#include "animation_utils.h"
#include "engine/base_defines.h"
#include "engine/object_types.h"
#include "engine/vdptile_manager.h"
#include "engine/draw_utils.h"

void AnimationUtils_updateBatchedAnimation(struct game_object* gameObject)
{
	if (!gameObject->animationTime)
	{
		gameObject->currentBatchedAnimationFrame = gameObject->currentBatchedAnimationFrame->nextFrame;
		gameObject->animationTime = gameObject->currentBatchedAnimationFrame->frameTime;
	}

	gameObject->animationTime--;
}

void AnimationUtils_updateMetaSpriteAnimation(struct game_object* gameObject)
{
	if (!gameObject->animationTime)
	{
		gameObject->currentMetaSpriteAnimationFrame = gameObject->currentMetaSpriteAnimationFrame->nextFrame;
		gameObject->animationTime = gameObject->currentMetaSpriteAnimationFrame->frameTime;
	}

	gameObject->animationTime--;
}



u8 AnimationUtils_updateBatchedAnimation_noLoop(GameObject* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentAnimationFrameIndex++;

		if (gameObject->currentAnimationFrameIndex == gameObject->batchedAnimation->numFrames)
		{
			return ANIMATION_FINISHED;
		}

		gameObject->currentBatchedAnimationFrame = gameObject->batchedAnimation->frames[gameObject->currentAnimationFrameIndex];
		gameObject->animationTime = gameObject->currentBatchedAnimationFrame->frameTime;
		return ANIMATION_CHANGED_FRAME;
	}

	return ANIMATION_NO_CHANGE;
}

// streamed
u8 AnimationUtils_updateStreamedBatchedAnimation(struct game_object* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentBatchedAnimationFrame = gameObject->currentBatchedAnimationFrame->nextFrame;

		if (gameObject->currentBatchedAnimationFrame == NULL)
		{
			return ANIMATION_FINISHED;
		}

		gameObject->animationTime = gameObject->currentBatchedAnimationFrame->frameTime;
		return ANIMATION_CHANGED_FRAME;
	}

	return ANIMATION_NO_CHANGE;
}

// plane

u8 AnimationUtils_updatePlaneAnimation(GameObject* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentPlaneAnimationFrame = gameObject->currentPlaneAnimationFrame->nextFrame;
		gameObject->animationTime = gameObject->currentPlaneAnimationFrame->frameTime;
		return ANIMATION_CHANGED_FRAME;
	}

	return ANIMATION_NO_CHANGE;
}

u8 AnimationUtils_updateTileAnimation(GameObject* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentTileAnimationFrame = gameObject->currentTileAnimationFrame->nextFrame;
		gameObject->animationTime = gameObject->currentTileAnimationFrame->frameTime;
		return ANIMATION_CHANGED_FRAME;
	}

	return ANIMATION_NO_CHANGE;
}

void AnimationUtils_setBatchedAnimationFrame(struct game_object* gameObject, u8 animationFrameIndex)
{
	gameObject->currentAnimationFrameIndex = animationFrameIndex;
	gameObject->currentBatchedAnimationFrame = gameObject->batchedAnimation->frames[animationFrameIndex]; 
	gameObject->animationTime = gameObject->currentBatchedAnimationFrame->frameTime;
}

u16 Load_BatchedAnimationResource(const ResourceInfo* resourceInfo)
{
	const BatchedAnimation* batchedAnimation = (const BatchedAnimation*)resourceInfo->resource;

	return VDPTileManager_LoadSpriteTiles(batchedAnimation->tileData, 
										  batchedAnimation->totalTileCount,
										  batchedAnimation->vdpLocation);
}



u16 Load_MetaSpriteBatchedAnimationResource(const ResourceInfo* resourceInfo)
{
	const MetaSpriteAnimation* metaSpriteAnimation = (const MetaSpriteAnimation*)resourceInfo->resource;

	return VDPTileManager_LoadSpriteTiles(metaSpriteAnimation->tileData, 
										  metaSpriteAnimation->totalTileCount,
										  metaSpriteAnimation->vdpLocation);
}

u16 Load_StreamedBatchedAnimationResource(const ResourceInfo* resourceInfo)
{
	const BatchedAnimation* batchedAnimation = (const BatchedAnimation*)resourceInfo->resource;

	return VDPTileManager_ReserveSpriteTilesArea(batchedAnimation->maxTilesPerFrame,
												 batchedAnimation->vdpLocation);
}

u16 Load_PlaneAnimationResource(const ResourceInfo* resourceInfo)
{
	const PlaneAnimation* planeAnimation = (const PlaneAnimation*)resourceInfo->resource;

	return VDPTileManager_LoadBackgroundTileset(planeAnimation->tileData, 
												planeAnimation->totalTileCount,
												planeAnimation->vdpLocation);
}

u16 Load_TileAnimationResource(const ResourceInfo* resourceInfo)
{
	const TileAnimation* tileAnimation = (const TileAnimation*)resourceInfo->resource;

	return VDPTileManager_LoadBackgroundTileset(tileAnimation->tileData, 
												tileAnimation->tilesPerFrame,
												tileAnimation->vdpLocation);
}


typedef BOOL (*UpdateAnimationFunctionType)(struct game_object* gameObject);

u16 Setup_BatchedAnimationResource(struct game_object* gameObject, const ResourceInfo* resourceInfo)
{
	const BatchedAnimation* batchedAnimation = (const BatchedAnimation*)resourceInfo->resource;

	gameObject->batchedAnimation = batchedAnimation;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentBatchedAnimationFrame = batchedAnimation->frames[0];
	gameObject->animationTime = gameObject->currentBatchedAnimationFrame->frameTime;
	gameObject->pixelWidth = batchedAnimation->pixelWidth;
	gameObject->pixelHeight = batchedAnimation->pixelHeight;
	gameObject->UpdateAnimation = (UpdateAnimationFunctionType)AnimationUtils_updateBatchedAnimation;

	return 0;
}

u16 Setup_MetaSpriteAnimationResource(struct game_object* gameObject, const ResourceInfo* resourceInfo)
{
	const MetaSpriteAnimation* metaSpriteAnimation = (const MetaSpriteAnimation*)resourceInfo->resource;

	gameObject->metaSpriteAnimation = metaSpriteAnimation;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentMetaSpriteAnimationFrame = metaSpriteAnimation->frames[0];
	gameObject->animationTime = gameObject->currentMetaSpriteAnimationFrame->frameTime;
	gameObject->pixelWidth = metaSpriteAnimation->pixelWidth;
	gameObject->pixelHeight = metaSpriteAnimation->pixelHeight;
	gameObject->UpdateAnimation = (UpdateAnimationFunctionType)AnimationUtils_updateMetaSpriteAnimation;
	gameObject->Draw = DrawUtils_drawMetasprite;

	return 0;
}

u16 Setup_PlaneAnimationResource(struct game_object* gameObject, const ResourceInfo* resourceInfo)
{
	const PlaneAnimation* planeAnimation = (const PlaneAnimation*)resourceInfo->resource;

	gameObject->planeAnimation = planeAnimation;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentPlaneAnimationFrame = planeAnimation->frames[0];
	gameObject->animationTime = gameObject->currentPlaneAnimationFrame->frameTime;
	gameObject->pixelWidth = planeAnimation->tileWidth * TILE_WIDTH;
	gameObject->pixelHeight = planeAnimation->tileHeight * TILE_HEIGHT;
	gameObject->UpdateAnimation = AnimationUtils_updatePlaneAnimation;

	return 0;
}

u16 Setup_TileAnimationResource(struct game_object* gameObject, const ResourceInfo* resourceInfo)
{
	const TileAnimation* tileAnimation = (const TileAnimation*)resourceInfo->resource;

	gameObject->tileAnimation = tileAnimation;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentTileAnimationFrame = tileAnimation->frames[0];
	gameObject->animationTime = gameObject->currentTileAnimationFrame->frameTime;
	gameObject->UpdateAnimation = AnimationUtils_updateTileAnimation;

	return 0;
}

// streaming

void* OUTI32(const void *src) __z88dk_fastcall;
void* OUTI64(const void *src) __z88dk_fastcall;
void* OUTI128(const void *src) __z88dk_fastcall;

__sfr __at 0xBE VDPDataPort2;
#define SETVDPDATAPORTb  __asm ld c,#_VDPDataPort2 __endasm

void UNSAFE_SMS_VRAMmemcpy192b (unsigned int dst, const void *src) {
	SMS_setAddr(0x4000|dst);
	SETVDPDATAPORTb;
	OUTI64(OUTI128(src));
}

void AnimationUtils_UpdateStreamedBatchedAnimationFrame(GameObject* gameObject)
{
	SMS_mapROMBank(gameObject->resourceInfo->bankNumber);

	//SMS_setBackdropColor(COLOR_ORANGE);
	const BatchedAnimationFrame* batchedAnimationFrame = gameObject->currentBatchedAnimationFrame;
	const BatchedAnimationSpriteStrip* runner = batchedAnimationFrame->spriteStrips;

	const BatchedAnimation* batchedAnimation = gameObject->batchedAnimation;
	const u8* tileData = batchedAnimation->tileData;
	u8 vdpIndex = *batchedAnimation->vdpLocation;



	do 
	{
		const u8* tileOffset = tileData + (runner->tileIndex << 5);

		// This is actually faster than a look-up table for some reason.
		// Unlike DrawUtils_DrawStreamedBatched which uses one, this function
		// gets slower with one. Maybe because of inlining?
		switch (runner->count)
		{
		case 1:
			UNSAFE_SMS_VRAMmemcpy64(vdpIndex << 5, (const void *)tileOffset);
			break;
		case 2:
		{
			UNSAFE_SMS_VRAMmemcpy128(vdpIndex << 5, (const void *)tileOffset);
			break;
		}
		case 3:
		{
			UNSAFE_SMS_VRAMmemcpy192b(vdpIndex << 5, (const void *)tileOffset);
			break;
		}
		case 4:
			UNSAFE_SMS_VRAMmemcpy256(vdpIndex << 5, (const void *)tileOffset);
		}

		vdpIndex += runner->count << 1;

		runner++;
	} while (runner->count);
}