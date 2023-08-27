#include "enemy.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"


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

	object->rectLeft = (s8)-4;
	object->rectTop = (s8)-4;
	object->rectRight = 4;
	object->rectBottom = 4;

	AnimationUtils_setupAnimation(object, (const Animation*)spawnInfo->payload, *((u8*)spawnInfo->additionalPayload));

	return object;
}

void Kunai_Update(GameObject* object)
{
	object->x += object->speedx;
	object->y += object->speedy;

	ObjectManagerUtils_updateObjectScreenRect(object);

	if (ObjectManager_objectLeft > SCREEN_RIGHT ||
		ObjectManager_objectTop > SCREEN_BOTTOM ||
		ObjectManager_objectRight < SCREEN_LEFT ||
		ObjectManager_objectBottom < SCREEN_TOP)
	{
		object->alive = FALSE;
	}

	if (!object->alive)
	{
		ObjectManager_DestroyObject(object);
	}
}

void Kunai_Draw(GameObject* object)
{
	const u8 index = object->objectId << 2;

	DRAWUTILS_SETUP(ObjectManager_objectLeft,
					ObjectManager_objectTop,
					object->currentAnimationFrame->numSprites, 
					object->currentAnimationFrame->sprites,
					object->animationVdpTileIndex);

	if (ObjectManager_objectLeft < SCREEN_LEFT || 
		ObjectManager_objectRight > SCREEN_RIGHT)
	{
		DrawUtils_DrawClippedSides();
	}
	else
	{
		DrawUtils_Draw();
	}
}

