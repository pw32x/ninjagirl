#include "object_utils.h"
#include "engine/base_defines.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"

void ObjectUtils_gameObjectDoNothing(GameObject* gameObject) { UNUSED(gameObject); }
void ObjectUtils_doNothing(void) {}

void ObjectUtils_UpdateAnimation(GameObject* gameObject)
{
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

/*
BOOL ObjectUtils_alwaysVisible(GameObject* gameObject)
{
	UNUSED(gameObject);

	return TRUE;
}

BOOL ObjectUtils_isOnScreen(GameObject* gameObject)
{
	return !(gameObject->screenLeft > SCREEN_WIDTH || 
			 gameObject->screenTop > SCREEN_HEIGHT ||
			 gameObject->screenRight < 0 ||
			 gameObject->screenBottom < 0);
}

BOOL ObjectUtils_isRightOfLeftScreenEdge(GameObject* gameObject)
{
	return (gameObject->screenRight >= SCREEN_LEFT);
}

BOOL ObjectUtils_isLeftOfScreen(GameObject* gameObject)
{
	return (gameObject->screenRight < SCREEN_LEFT);
}*/