#include "enemy.h"
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

void Enemy_Update(GameObject* object);
BOOL Enemy_Draw(GameObject* object);
void Enemy_HandleCollision(GameObject* gameObject, GameObject* other);

GameObject* Enemy_Init(GameObject* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->Update = Enemy_Update;
	object->Draw = Enemy_Draw;
	object->HandleCollision = Enemy_HandleCollision;

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

	object->screenx = object->x - ScrollManager_horizontalScroll;
	object->screeny = object->y - ScrollManager_verticalScroll;

	// if offscreen die
	if (object->screenx + object->rectLeft < SCREEN_LEFT)
	{
		SMS_debugPrintf("object->screenx: %d\n", object->screenx);
		goto destroy_object;
	}
	
	//if (ObjectManagerUtils_collidesWithProjectiles(object))
	//{
	//	goto destroy_object;
	//}


	return;

destroy_object:
	SMS_debugPrintf("Destroy Object\n");
	ObjectManager_DestroyObject(object);
}

BOOL Enemy_Draw(GameObject* object)
{
	DRAWUTILS_SETUP_BATCH(object->screenx,
						  object->screeny,
						  object->currentBatchedAnimationFrame->spriteStrips,
						  *object->batchedAnimation->vdpLocation);

	DrawUtils_DrawBatched();

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
			&explosion_template,
			gameObject->x, 
			gameObject->y
		};
		
		ObjectManager_CreateObjectByCreateInfo(&createInfo);

		PSGSFXPlay(explosion_psg, SFX_CHANNELS2AND3);
	}
	else
	{
		PSGSFXPlay(hit_psg, SFX_CHANNELS2AND3);
	}
}