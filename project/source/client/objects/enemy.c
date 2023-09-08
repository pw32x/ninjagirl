#include "enemy.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"
#include "engine/resource_manager.h"


void Enemy_Update(GameObject* object);
void Enemy_Draw(GameObject* object);

GameObject* Enemy_Create(const SpawnInfo* spawnInfo)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_ENEMY);
	if (!object)
		return NULL;

	object->x = spawnInfo->startX;
	object->y = spawnInfo->startY;
	object->Update = Enemy_Update;
	object->Draw = Enemy_Draw;

	object->rectLeft = -14;
	object->rectTop = -14;
	object->rectRight = 14;
	object->rectBottom = 14;

	ResourceManager_SetupResource(object, spawnInfo->payload, spawnInfo->additionalPayload);

	return object;
}

void Enemy_Update(GameObject* object)
{
	object->UpdateAnimation(object);

	//ObjectManagerUtils_updateObjectScreenRect(object);

	/*
	// player collision
	if (ObjectManager_playerLeft < ObjectManager_objectRight &&
		ObjectManager_playerRight > ObjectManager_objectLeft &&
		ObjectManager_playerTop < ObjectManager_objectBottom &&
		ObjectManager_playerBottom > ObjectManager_objectTop)
	{
		goto destroy_object;
	}
	*/

	// if offscreen die
	if (object->x + 14 < SCREEN_LEFT)
	{
		goto destroy_object;
	}
	
	//if (ObjectManagerUtils_collidesWithProjectiles(object))
	//{
	//	goto destroy_object;
	//}


	return;

destroy_object:
	ObjectManager_DestroyObject(object);
}

void Enemy_Draw(GameObject* object)
{
	s16 screenLeft = object->x - ScrollManager_horizontalScroll;
	s16 screenRight = screenLeft + 14;//object->rectRight;

	DRAWUTILS_SETUP_BATCH(screenLeft,
						  object->y,
						  object->currentAnimationBatchedFrame->spriteBatch,
						  object->animationVdpTileIndex);

	if (screenRight < SCREEN_LEFT || 
		screenLeft > SCREEN_RIGHT)
	{
		DrawUtils_DrawClippedSides();
	}
	else
	{
		//DrawUtils_Draw();
		DrawUtils_DrawBatched();
	}
}

