#include "animation_utils.h"
#include "engine/object_types.h"

void AnimationUtils_setupAnimation(GameObject* gameObject, const Animation* animation, u8 vdpTileIndex)
{
	gameObject->animation = animation;
	gameObject->animationVdpTileIndex = vdpTileIndex;
	gameObject->currentAnimationFrameIndex = 0;
	gameObject->currentAnimationFrame = animation->frames[0];
	gameObject->animationTime = gameObject->currentAnimationFrame->frameTime;
	gameObject->pixelWidth = animation->pixelWidth;
	gameObject->pixelHeight = animation->pixelHeight;
}

void AnimationUtils_updateAnimation(GameObject* gameObject)
{
	return;

	if (!gameObject->animationTime--)
	{
		gameObject->currentAnimationFrameIndex++;

		if (gameObject->currentAnimationFrameIndex == gameObject->animation->numFrames)
			gameObject->currentAnimationFrameIndex = 0;

		gameObject->currentAnimationFrame = gameObject->animation->frames[gameObject->currentAnimationFrameIndex];
		gameObject->animationTime = gameObject->currentAnimationFrame->frameTime;
	}

	//gameObject->animationTime++;
}