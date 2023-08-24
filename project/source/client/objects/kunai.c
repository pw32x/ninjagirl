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

void Kunai_Create(const SpawnInfo* spawnInfo)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_PROJECTILE);
	if (!object)
		return;

	object->x = spawnInfo->startX;
	object->y = spawnInfo->startY;
	object->Update = Kunai_Update;
	object->Draw = Kunai_Draw;

	AnimationUtils_setupAnimation(object, (const Animation*)spawnInfo->payload, *((u8*)spawnInfo->additionalPayload));
}

void Kunai_Update(GameObject* object)
{
	AnimationUtils_updateAnimation(object);

	ObjectManagerUtils_updateObjectScreenRect(object);

	if (ObjectManager_objectRight < SCREEN_LEFT ||
		ObjectManager_objectLeft > SCREEN_RIGHT)
	{
		ObjectManager_DestroyObject(object);
	}
}

void Kunai_Draw(GameObject* object)
{
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

