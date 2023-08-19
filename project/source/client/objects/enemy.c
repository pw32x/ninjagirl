#include "enemy.h"
#include "SMSlib.h"
#include "engine/animation_helpers.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"

void Enemy_Update(GameObject* object);
void Enemy_Draw(GameObject* object);

void Enemy_Create(const SpawnInfo* spawnInfo)
{
	GameObject* object = ObjectManager_GetAvailableSlot();
	if (!object)
		return;

	object->x = spawnInfo->startX;
	object->y = spawnInfo->startY;
	object->animation = (const Animation*)spawnInfo->payload;
	object->animationVdpTileIndex = *((u8*)spawnInfo->additionalPayload);
	object->currentAnimationFrameIndex = 0;
	object->currentAnimationFrame = object->animation->frames[object->currentAnimationFrameIndex];
	object->animationTime = 0;
	object->Update = Enemy_Update;
	object->Draw = Enemy_Draw;
}

void Enemy_Update(GameObject* object)
{
	if (object->animationTime == object->currentAnimationFrame->frameTime)
	{
		object->currentAnimationFrameIndex++;

		if (object->currentAnimationFrameIndex == object->animation->numFrames)
			object->currentAnimationFrameIndex = 0;

		object->currentAnimationFrame = object->animation->frames[object->currentAnimationFrameIndex];
		object->animationTime = 0;
	}

	object->animationTime++;
}

void Enemy_Draw(GameObject* object)
{
	Animation_DrawFrame(object->currentAnimationFrame, 
						object->animationVdpTileIndex,
						object->x - ScrollManager_horizontalScroll, 
						object->y);
}

