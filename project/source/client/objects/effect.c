#include "effect.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/resource_manager.h"
#include "engine/animation_utils.h"

void Effect_Update(GameObject* object);
void Effect_Draw(GameObject* object);

GameObject* Effect_Create(const CreateInfo* createInfo)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_EFFECT);
	if (!object)
		return NULL;

	object->x = createInfo->startX;
	object->y = createInfo->startY;
	object->Update = Effect_Update;
	object->Draw = Effect_Draw;

	ResourceManager_SetupResource(object, createInfo->resource);

	return object;
}

void Effect_Update(GameObject* object)
{
	object->x += object->speedx;
	object->y += object->speedy;

	if (object->x > SCREEN_RIGHT ||
		object->y > SCREEN_BOTTOM ||
		object->x < SCREEN_LEFT ||
		object->y < SCREEN_TOP)
	{
		ObjectManager_DestroyObject(object);
	}

	if (AnimationUtils_updateAnimationBatched_noLoop(object) == ANIMATION_FINISHED)
		ObjectManager_DestroyObject(object);
}

void Effect_Draw(GameObject* object)
{
	DRAWUTILS_SETUP_BATCH(object->x - ScrollManager_horizontalScroll,
						  object->y,
						  object->currentAnimationBatchedFrame->spriteBatch,
						  *object->animationBatched->vdpLocation);


	// should never be clipped
	DrawUtils_DrawBatched();
}