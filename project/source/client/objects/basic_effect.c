#include "basic_effect.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/resource_manager.h"
#include "engine/animation_utils.h"

void BasicEffect_Update(GameObject* object);
BOOL BasicEffect_Draw(GameObject* object);

GameObject* BasicEffect_Create(const CreateInfo* createInfo)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_EFFECT);
	if (!object)
		return NULL;

	object->x = createInfo->startX;
	object->y = createInfo->startY;
	object->Update = BasicEffect_Update;
	object->Draw = BasicEffect_Draw;

	ResourceManager_SetupResource(object, createInfo->resource);

	return object;
}

void BasicEffect_Update(GameObject* object)
{
	object->x += object->speedx;
	object->y += object->speedy;

	if (object->x > SCREEN_RIGHT + ScrollManager_horizontalScroll ||
		object->y > SCREEN_BOTTOM ||
		object->x < SCREEN_LEFT + ScrollManager_horizontalScroll ||
		object->y < SCREEN_TOP)
	{
		ObjectManager_DestroyObject(object);
	}

	if (AnimationUtils_updateBatchedAnimation_noLoop(object) == ANIMATION_FINISHED)
		ObjectManager_DestroyObject(object);
}

BOOL BasicEffect_Draw(GameObject* object)
{
	DRAWUTILS_SETUP_BATCH(object->x - ScrollManager_horizontalScroll,
						  object->y,
						  object->currentBatchedAnimationFrame->batchedSprite,
						  *object->batchedAnimation->vdpLocation);


	// should never be clipped
	DrawUtils_DrawBatched();

	return TRUE;
}