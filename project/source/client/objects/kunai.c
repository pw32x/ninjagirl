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

	AnimationUtils_setupAnimation(object, (const Animation*)spawnInfo->payload, *((u8*)spawnInfo->additionalPayload));

	return object;
}

#define LEFT index
#define TOP index + 1
#define RIGHT index + 2
#define BOTTOM index + 3

s16 left;
s16 top;
s16 right;
s16 bottom;

void Kunai_Update(GameObject* object)
{
	const u8 index = object->objectId << 2;

	object->x += object->speedx;
	object->y += object->speedy;

	left = object->x - ScrollManager_horizontalScroll;
	top = object->y;
	right = left + object->animation->pixelWidth;
	bottom = top + object->animation->pixelHeight;

	if (left > SCREEN_RIGHT ||
		top > SCREEN_BOTTOM ||
		right < SCREEN_LEFT ||
		bottom < SCREEN_TOP)
	{
		left = 1000;
		top = 1000;
		right = 1000;
		bottom = 1000;

		object->alive = FALSE;
	}

	ObjectManager_projectileRect[LEFT] = left;
	ObjectManager_projectileRect[TOP] = top;
	ObjectManager_projectileRect[RIGHT] = right;
	ObjectManager_projectileRect[BOTTOM] = bottom;

	if (!object->alive)
	{
		ObjectManager_DestroyObject(object);
	}
}

void Kunai_Draw(GameObject* object)
{
	const u8 index = object->objectId << 2;

	DRAWUTILS_SETUP(ObjectManager_projectileRect[LEFT],
					ObjectManager_projectileRect[TOP],
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

