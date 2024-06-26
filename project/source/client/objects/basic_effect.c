#include "basic_effect.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager_create.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/resource_manager.h"
#include "engine/animation_utils.h"

void BasicEffect_Update(GameObject* object);

GameObject* BasicEffect_Init(GameObject* object, const CreateInfo* createInfo)
{
	// 36/36/36.0

	UNUSED(createInfo);
	object->Update = BasicEffect_Update;

	return object;
}

void BasicEffect_Update(GameObject* object)
{
	//SMS_setBackdropColor(COLOR_PINK);

	object->x += object->speedx;
	object->y += object->speedy;

	object->screenx = object->x - ScrollManager_horizontalScroll;
	object->screeny = object->y;
	if (object->screenx > SCREEN_RIGHT ||
		object->screeny > SCREEN_BOTTOM ||
		object->screenx < SCREEN_LEFT ||
		object->screeny < SCREEN_TOP)
	{
		ObjectManager_DestroyObject(object);
	}

	SMS_mapROMBank(object->resourceInfo->bankNumber);
	if (AnimationUtils_updateBatchedAnimation_noLoop(object) == ANIMATION_FINISHED)
		ObjectManager_DestroyObject(object);

	//SMS_setBackdropColor(COLOR_DARK_GREEN);
}