#include "animation_utils.h"
#include "engine/base_defines.h"
#include "engine/object_types.h"
#include "engine/vdptile_manager.h"

u8 AnimationUtils_updateAnimation(GameObject* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentAnimationFrame = gameObject->currentAnimationFrame->nextFrame;

		if (gameObject->currentAnimationFrame == NULL)
		{
			return ANIMATION_FINISHED;
		}

		gameObject->animationTime = gameObject->currentAnimationFrame->frameTime;
		return ANIMATION_CHANGED_FRAME;
	}

	return ANIMATION_NO_CHANGE;
}

u8 AnimationUtils_updateBatchedAnimation(struct game_object* gameObject)
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



u8 AnimationUtils_updateStreamedAnimation(GameObject* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentStreamedAnimationFrame = gameObject->currentStreamedAnimationFrame->nextFrame;

		if (gameObject->currentStreamedAnimationFrame == NULL)
		{
			return ANIMATION_FINISHED;
		}

		gameObject->animationTime = gameObject->currentStreamedAnimationFrame->frameTime;
		return ANIMATION_CHANGED_FRAME;
	}

	return ANIMATION_NO_CHANGE;
}

u8 AnimationUtils_updateStreamedBatchedAnimation(struct game_object* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentStreamedBatchedAnimationFrame = gameObject->currentStreamedBatchedAnimationFrame->nextFrame;

		if (gameObject->currentStreamedBatchedAnimationFrame == NULL)
		{
			return ANIMATION_FINISHED;
		}

		gameObject->animationTime = gameObject->currentStreamedBatchedAnimationFrame->frameTime;
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

void AnimationUtils_setStreamedBatchedAnimationFrame(struct game_object* gameObject, u8 animationFrameIndex)
{
	gameObject->currentAnimationFrameIndex = animationFrameIndex;
	gameObject->currentStreamedBatchedAnimationFrame = gameObject->streamedBatchedAnimation->frames[animationFrameIndex]; 
	gameObject->animationTime = gameObject->currentStreamedBatchedAnimationFrame->frameTime;
}

u16 Load_AnimationResource(const Animation* animation)
{
	return VDPTileManager_LoadSpriteTiles(animation->tileData, 
										  animation->totalTileCount,
										  animation->vdpLocation);
}

u16 Load_BatchedAnimationResource(const BatchedAnimation* batchedAnimation)
{
	return VDPTileManager_LoadSpriteTiles(batchedAnimation->tileData, 
										  batchedAnimation->totalTileCount,
										  batchedAnimation->vdpLocation);
}

u16 Load_StreamedAnimationResource(const StreamedAnimation* streamedAnimation)
{
	return VDPTileManager_ReserveSpriteTilesArea(streamedAnimation->maxTilesInFrame,
												 streamedAnimation->vdpLocation);
}

u16 Load_StreamedBatchedAnimationResource(const StreamedBatchedAnimation* streamedBatchedAnimation)
{
	return VDPTileManager_ReserveSpriteTilesArea(streamedBatchedAnimation->maxTilesInFrame,
												 streamedBatchedAnimation->vdpLocation);
}

u16 Load_PlaneAnimationResource(const PlaneAnimation* planeAnimation)
{
	return VDPTileManager_LoadBackgroundTileset(planeAnimation->tileData, 
												planeAnimation->totalTileCount,
												planeAnimation->vdpLocation);
}

u16 Load_TileAnimationResource(const TileAnimation* tileAnimation)
{
	return VDPTileManager_LoadBackgroundTileset(tileAnimation->tileData, 
												tileAnimation->tilesPerFrame,
												tileAnimation->vdpLocation);
}

u16 Setup_AnimationResource(struct game_object* gameObject, const Animation* animation)
{
	gameObject->animation = animation;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentAnimationFrame = animation->frames[0];
	gameObject->animationTime = gameObject->currentAnimationFrame->frameTime;
	gameObject->pixelWidth = animation->pixelWidth;
	gameObject->pixelHeight = animation->pixelHeight;
	gameObject->UpdateAnimation = AnimationUtils_updateAnimation;

	return 0;
}

u16 Setup_BatchedAnimationResource(struct game_object* gameObject, const BatchedAnimation* batchedAnimation)
{
	gameObject->batchedAnimation = batchedAnimation;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentBatchedAnimationFrame = batchedAnimation->frames[0];
	gameObject->animationTime = gameObject->currentBatchedAnimationFrame->frameTime;
	gameObject->pixelWidth = batchedAnimation->pixelWidth;
	gameObject->pixelHeight = batchedAnimation->pixelHeight;
	gameObject->UpdateAnimation = AnimationUtils_updateBatchedAnimation;

	return 0;
}

u16 Setup_StreamedAnimationResource(struct game_object* gameObject, const StreamedAnimation* streamedAnimation)
{
	gameObject->streamedAnimation = streamedAnimation;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentStreamedAnimationFrame = streamedAnimation->frames[0];
	gameObject->animationTime = gameObject->currentAnimationFrame->frameTime;
	gameObject->pixelWidth = streamedAnimation->pixelWidth;
	gameObject->pixelHeight = streamedAnimation->pixelHeight;
	gameObject->UpdateAnimation = AnimationUtils_updateStreamedAnimation;

	return 0;
}

u16 Setup_StreamedBatchedAnimationResource(struct game_object* gameObject, const StreamedBatchedAnimation* streamedBatchedAnimation)
{
	gameObject->streamedBatchedAnimation = streamedBatchedAnimation;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentStreamedBatchedAnimationFrame = streamedBatchedAnimation->frames[0];
	gameObject->animationTime = gameObject->currentStreamedBatchedAnimationFrame->frameTime;
	gameObject->pixelWidth = streamedBatchedAnimation->pixelWidth;
	gameObject->pixelHeight = streamedBatchedAnimation->pixelHeight;
	gameObject->UpdateAnimation = AnimationUtils_updateStreamedBatchedAnimation;

	return 0;
}

u16 Setup_PlaneAnimationResource(struct game_object* gameObject, const PlaneAnimation* planeAnimation)
{
	gameObject->planeAnimation = planeAnimation;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentPlaneAnimationFrame = planeAnimation->frames[0];
	gameObject->animationTime = gameObject->currentPlaneAnimationFrame->frameTime;
	gameObject->pixelWidth = planeAnimation->tileWidth * TILE_WIDTH;
	gameObject->pixelHeight = planeAnimation->tileHeight * TILE_HEIGHT;
	gameObject->UpdateAnimation = AnimationUtils_updatePlaneAnimation;

	return 0;
}

u16 Setup_TileAnimationResource(struct game_object* gameObject, const TileAnimation* tileAnimation)
{
	gameObject->tileAnimation = tileAnimation;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentTileAnimationFrame = tileAnimation->frames[0];
	gameObject->animationTime = gameObject->currentTileAnimationFrame->frameTime;
	gameObject->UpdateAnimation = AnimationUtils_updateTileAnimation;

	return 0;
}

// streaming

void AnimationUtils_UpdateStreamedBatchedAnimationFrame(GameObject* gameObject)
{
	SMS_setBackdropColor(COLOR_ORANGE);

	const StreamedBatchedAnimationFrame* streamedBatchedAnimationFrame = gameObject->currentStreamedBatchedAnimationFrame;
	const u8* tileData = gameObject->streamedBatchedAnimation->tileData;
	u16 vdpIndex = *gameObject->streamedBatchedAnimation->vdpLocation + 256;

	const BatchedAnimationSprite* runner = streamedBatchedAnimationFrame->batchedSprites;
	u16 tileIndex = streamedBatchedAnimationFrame->tileIndex;

	// assumes tiles are stored linearly, with no deduplication to make copying
	// to vdp as simple as possible.

	while (runner->count)
	{
		const AnimationSprite* sprite = &runner->sprite;

		u8 tileCount = runner->count << 1;

		u16 tileOffset = tileData + ((tileIndex + runner->sprite.tileIndex) << 5);

		switch (tileCount)
		{
		case 0:
			return;
		case 2:
			UNSAFE_SMS_load2Tiles(tileOffset, vdpIndex);
			break;
		case 4:
			UNSAFE_SMS_load4Tiles(tileOffset, vdpIndex);
			break;
		case 6:
			UNSAFE_SMS_load2Tiles(tileOffset, vdpIndex);
			UNSAFE_SMS_load4Tiles(tileOffset + 64, vdpIndex + 2);
			break;
		case 8:
			UNSAFE_SMS_load4Tiles(tileOffset, vdpIndex);
			UNSAFE_SMS_load4Tiles(tileOffset + 128, vdpIndex + 4);
		}

		vdpIndex += tileCount;

		runner++;
	}
}