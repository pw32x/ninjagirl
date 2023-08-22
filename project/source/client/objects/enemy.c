#include "enemy.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"


void Enemy_Update(GameObject* object);
void Enemy_Draw(GameObject* object);

void Enemy_Create(const SpawnInfo* spawnInfo)
{
	GameObject* object = ObjectManager_GetAvailableSlot();
	if (!object)
		return;

	object->x = spawnInfo->startX;
	object->y = spawnInfo->startY;
	object->Update = Enemy_Update;
	object->Draw = Enemy_Draw;

	AnimationUtils_setupAnimation(object, (const Animation*)spawnInfo->payload, *((u8*)spawnInfo->additionalPayload));
}

void Enemy_Update(GameObject* object)
{
	AnimationUtils_updateAnimation(object);

	ObjectManagerUtils_updateObjectScreenRect(object);

	//if (ObjectUtils_isLeftOfScreen(object))
	//{
	//	//ObjectManager_DestroyObject(object);
	//}

	//if (!(playerLeft > right ||
	//	  playerRight < left ||
	//	  playerTop > bottom ||
	//	  playerBottom < top))
	//{
	//	ObjectManager_DestroyObject(object);
	//}

	//object->Draw(object);
}

void Enemy_Draw(GameObject* object)
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

