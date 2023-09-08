#include "animation_utils.h"
#include "engine/base_defines.h"
#include "engine/object_types.h"
#include "engine/vdptile_manager.h"

BOOL AnimationUtils_updateAnimationBatched(GameObject* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentAnimationFrameIndex++;

		if (gameObject->currentAnimationFrameIndex == gameObject->animationBatched->numFrames)
			gameObject->currentAnimationFrameIndex = 0;

		gameObject->currentAnimationBatchedFrame = gameObject->animationBatched->frames[gameObject->currentAnimationFrameIndex];
		gameObject->animationTime = gameObject->currentAnimationBatchedFrame->frameTime;
		return TRUE;
	}

	return FALSE;
}

BOOL AnimationUtils_updatePlaneAnimation(struct game_object* gameObject)
{
	if (!gameObject->animationTime--)
	{
		gameObject->currentPlaneAnimationFrame = gameObject->currentPlaneAnimationFrame->nextFrame;
		gameObject->animationTime = gameObject->currentPlaneAnimationFrame->frameTime;
		return TRUE;
	}

	return FALSE;
}

u16 Load_AnimationResource(const Animation* animation)
{
	return VDPTileManager_LoadSpriteTiles(animation->tileData, animation->totalTileCount);
}

u16 Load_BatchedAnimationResource(const AnimationBatched* animationBatched)
{
	return VDPTileManager_LoadSpriteTiles(animationBatched->tileData, animationBatched->totalTileCount);
}

u16 Load_PlaneAnimationResource(const PlaneAnimation* planeAnimation)
{
	return VDPTileManager_LoadBackgroundTileset(planeAnimation->tileData, planeAnimation->totalTileCount);
}

u16 Setup_AnimationResource(struct game_object* gameObject, const Animation* animation, u16 vdpTileIndex)
{
	return 0;
}

u16 Setup_BatchedAnimationResource(struct game_object* gameObject, const AnimationBatched* animationBatched, u16 data)
{
	gameObject->animationBatched = animationBatched;
	gameObject->animationVdpTileIndex = *((u8*)data);
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentAnimationBatchedFrame = animationBatched->frames[0];
	gameObject->animationTime = gameObject->currentAnimationBatchedFrame->frameTime;
	gameObject->pixelWidth = animationBatched->pixelWidth;
	gameObject->pixelHeight = animationBatched->pixelHeight;
	gameObject->UpdateAnimation = AnimationUtils_updateAnimationBatched;

	return 0;
}

u16 Setup_PlaneAnimationResource(struct game_object* gameObject, const PlaneAnimation* planeAnimation, u16 data)
{
	gameObject->planeAnimation = planeAnimation;
	gameObject->animationVdpTileIndex = *((u8*)data);
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentPlaneAnimationFrame = planeAnimation->frames[0];
	gameObject->animationTime = gameObject->currentPlaneAnimationFrame->frameTime;
	gameObject->pixelWidth = planeAnimation->tileWidth * TILE_WIDTH;
	gameObject->pixelHeight = planeAnimation->tileHeight * TILE_HEIGHT;
	gameObject->UpdateAnimation = AnimationUtils_updatePlaneAnimation;

	return 0;
}