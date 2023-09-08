#include "enemy.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/resource_manager.h"


void Kunai_Update(GameObject* object);
void Kunai_Draw(GameObject* object);


GameObject* Kunai_Create(const SpawnInfo* spawnInfo)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_PROJECTILE);
	if (!object)
		return NULL;

	object->x = spawnInfo->startX;
	object->y = spawnInfo->startY;
	object->Update = Kunai_Update;
	object->Draw = Kunai_Draw;

	object->rectLeft = -4;
	object->rectTop = -4;
	object->rectRight = 4;
	object->rectBottom = 4;

	ResourceManager_SetupResource(object, spawnInfo->payload, spawnInfo->additionalPayload);

	return object;
}

void Kunai_Update(GameObject* object)
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
}

void Kunai_Draw(GameObject* object)
{
	DRAWUTILS_SETUP_BATCH(object->x - ScrollManager_horizontalScroll,
						  object->y,
						  object->currentAnimationBatchedFrame->spriteBatch,
						  object->animationVdpTileIndex);


	// should never be clipped
	DrawUtils_DrawBatched();
}

