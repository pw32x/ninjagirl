#include "enemy.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"
#include "engine/resource_manager.h"

#include "client/exported/animations/explosion.h"
#include "client/objects/basic_effect.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

void Enemy_Update(GameObject* object);
BOOL Enemy_Draw(GameObject* object);
void Enemy_HandleCollision(GameObject* gameObject, GameObject* other);

GameObject* Enemy_Create(const CreateInfo* createInfo)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_ENEMY);
	if (!object)
		return NULL;

	object->x = createInfo->startX;
	object->y = createInfo->startY;
	object->Update = Enemy_Update;
	object->Draw = Enemy_Draw;
	object->HandleCollision = Enemy_HandleCollision;

	object->rectLeft = -14;
	object->rectTop = -14;
	object->rectRight = 14;
	object->rectBottom = 14;

	object->health = 8;

	//ObjectManager_enemyIndex = (ObjectManager_enemyIndex++) & 7;

	//object->data1 = object - ObjectManager_enemySlots;
	//
	//object->x = object->data1 * 32;

	ResourceManager_SetupResource(object, createInfo->resourceInfo);

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

BOOL Enemy_Draw(GameObject* object)
{
	//if (object->data1 == ObjectManager_enemyCounter)
	//{
	//	return FALSE;
	//}

	s16 screenLeft = object->x - ScrollManager_horizontalScroll;
	s16 screenRight = screenLeft + 14;//object->rectRight;

	DRAWUTILS_SETUP_BATCH(screenLeft,
						  object->y,
						  object->currentBatchedAnimationFrame->batchedSprite,
						  *object->batchedAnimation->vdpLocation);

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

	return TRUE;
}

void Enemy_HandleCollision(GameObject* gameObject, GameObject* other)
{
	gameObject->health -= other->damage;

	if (gameObject->health <= 0)
	{
		ObjectManager_DestroyObject(gameObject);
		
		CreateInfo createInfo = 
		{ 
			gameObject->x, 
			gameObject->y, 
			(const void*)&explosion, 
		};
		
		GameObject* effect = BasicEffect_Create(&createInfo);

		PSGSFXPlay(explosion_psg, SFX_CHANNELS2AND3);
	}
	else
	{
		PSGSFXPlay(hit_psg, SFX_CHANNELS2AND3);
	}
}