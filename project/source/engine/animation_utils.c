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

u8 AnimationUtils_updateAnimationBatched(struct game_object* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentAnimationBatchedFrame = gameObject->currentAnimationBatchedFrame->nextFrame;

		if (gameObject->currentAnimationBatchedFrame == NULL)
		{
			return ANIMATION_FINISHED;
		}

		gameObject->animationTime = gameObject->currentAnimationBatchedFrame->frameTime;
		return ANIMATION_CHANGED_FRAME;
	}

	return ANIMATION_NO_CHANGE;
}

u8 AnimationUtils_updateAnimationBatched_noLoop(GameObject* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentAnimationFrameIndex++;

		if (gameObject->currentAnimationFrameIndex == gameObject->animationBatched->numFrames)
		{
			return ANIMATION_FINISHED;
		}

		gameObject->currentAnimationBatchedFrame = gameObject->animationBatched->frames[gameObject->currentAnimationFrameIndex];
		gameObject->animationTime = gameObject->currentAnimationBatchedFrame->frameTime;
		return ANIMATION_CHANGED_FRAME;
	}

	return ANIMATION_NO_CHANGE;
}

// streamed



u8 AnimationUtils_updateAnimationStreamed(GameObject* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentAnimationStreamedFrame = gameObject->currentAnimationStreamedFrame->nextFrame;

		if (gameObject->currentAnimationStreamedFrame == NULL)
		{
			return ANIMATION_FINISHED;
		}

		gameObject->animationTime = gameObject->currentAnimationStreamedFrame->frameTime;
		return ANIMATION_CHANGED_FRAME;
	}

	return ANIMATION_NO_CHANGE;
}

u8 AnimationUtils_updateAnimationBatchedStreamed(struct game_object* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentAnimationBatchedStreamedFrame = gameObject->currentAnimationBatchedStreamedFrame->nextFrame;

		if (gameObject->currentAnimationBatchedStreamedFrame == NULL)
		{
			return ANIMATION_FINISHED;
		}

		gameObject->animationTime = gameObject->currentAnimationBatchedStreamedFrame->frameTime;
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

void AnimationUtils_setAnimationFrameBatched(struct game_object* gameObject, u8 animationFrameIndex)
{
	gameObject->currentAnimationFrameIndex = animationFrameIndex;
	gameObject->currentAnimationBatchedFrame = gameObject->animationBatched->frames[animationFrameIndex]; 
	gameObject->animationTime = gameObject->currentAnimationBatchedFrame->frameTime;
}

u16 Load_AnimationResource(const Animation* animation)
{
	return VDPTileManager_LoadSpriteTiles(animation->tileData, 
										  animation->totalTileCount,
										  animation->vdpLocation);
}

u16 Load_BatchedAnimationResource(const AnimationBatched* animationBatched)
{
	return VDPTileManager_LoadSpriteTiles(animationBatched->tileData, 
										  animationBatched->totalTileCount,
										  animationBatched->vdpLocation);
}

u16 Load_AnimationStreamedResource(const AnimationStreamed* animationStreamed)
{
	return VDPTileManager_LoadSpriteTiles(animationStreamed->tileData, 
										  animationStreamed->totalTileCount,
										  animationStreamed->vdpLocation);
}

u16 Load_BatchedStreamedAnimationResource(const AnimationBatchedStreamed* animationBatchedStreamed)
{
	return VDPTileManager_LoadSpriteTiles(animationBatchedStreamed->tileData, 
										  animationBatchedStreamed->totalTileCount,
										  animationBatchedStreamed->vdpLocation);
}

u16 Load_PlaneAnimationResource(const PlaneAnimation* planeAnimation)
{
	return VDPTileManager_LoadBackgroundTileset(planeAnimation->tileData, 
												planeAnimation->totalTileCount,
												planeAnimation->vdpLocation);
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

u16 Setup_BatchedAnimationResource(struct game_object* gameObject, const AnimationBatched* animationBatched)
{
	gameObject->animationBatched = animationBatched;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentAnimationBatchedFrame = animationBatched->frames[0];
	gameObject->animationTime = gameObject->currentAnimationBatchedFrame->frameTime;
	gameObject->pixelWidth = animationBatched->pixelWidth;
	gameObject->pixelHeight = animationBatched->pixelHeight;
	gameObject->UpdateAnimation = AnimationUtils_updateAnimationBatched;

	return 0;
}

u16 Setup_StreamedAnimationResource(struct game_object* gameObject, const AnimationStreamed* animationStreamed)
{
	gameObject->animationStreamed = animationStreamed;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentAnimationStreamedFrame = animationStreamed->frames[0];
	gameObject->animationTime = gameObject->currentAnimationFrame->frameTime;
	gameObject->pixelWidth = animationStreamed->pixelWidth;
	gameObject->pixelHeight = animationStreamed->pixelHeight;
	gameObject->UpdateAnimation = AnimationUtils_updateAnimationStreamed;

	return 0;
}

u16 Setup_StreamedBatchedAnimationResource(struct game_object* gameObject, const AnimationBatchedStreamed* animationBatchedStreamed)
{
	gameObject->animationBatchedStreamed = animationBatchedStreamed;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentAnimationBatchedStreamedFrame = animationBatchedStreamed->frames[0];
	gameObject->animationTime = gameObject->currentAnimationBatchedStreamedFrame->frameTime;
	gameObject->pixelWidth = animationBatchedStreamed->pixelWidth;
	gameObject->pixelHeight = animationBatchedStreamed->pixelHeight;
	gameObject->UpdateAnimation = AnimationUtils_updateAnimationBatchedStreamed;

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