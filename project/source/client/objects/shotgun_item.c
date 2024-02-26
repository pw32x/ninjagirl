#include "shotgun_item.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"
#include "engine/resource_manager.h"
#include "engine/createinfo_types.h"

#include "client/generated/gameobjecttemplates/gameobject_templates.h"
#include "client/objects/basic_effect.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

void ShotgunItem_Update(GameObject* object);
BOOL ShotgunItem_Draw(GameObject* object);
void ShotgunItem_HandleCollision(GameObject* gameObject, GameObject* other);

GameObject* ShotgunItem_Init(GameObject* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->Update = ShotgunItem_Update;
	object->Draw = ShotgunItem_Draw;
	object->HandleCollision = ShotgunItem_HandleCollision;

	return object;
}

void ShotgunItem_Update(GameObject* object)
{
	SMS_mapROMBank(object->resourceInfo->bankNumber);
	object->UpdateAnimation(object);

	object->screenx = object->x - ScrollManager_horizontalScroll;
	object->screeny = object->y - ScrollManager_verticalScroll;

	// if offscreen die
	if (object->screenx + object->rectLeft < SCREEN_LEFT)
	{
		SMS_debugPrintf("object->screenx: %d\n", object->screenx);
		goto destroy_object;
	}
	
	return;

destroy_object:
	SMS_debugPrintf("Destroy Object\n");
	ObjectManager_DestroyObject(object);
}

BOOL ShotgunItem_Draw(GameObject* object)
{
	SMS_mapROMBank(object->resourceInfo->bankNumber);
	DRAWUTILS_SETUP_BATCH(object->screenx,
						  object->screeny,
						  object->currentBatchedAnimationFrame->spriteStrips,
						  *object->batchedAnimation->vdpLocation);

	DrawUtils_DrawBatched();

	return TRUE;
}

void ShotgunItem_HandleCollision(GameObject* gameObject, GameObject* other)
{
	ObjectManager_DestroyObject(gameObject);
}