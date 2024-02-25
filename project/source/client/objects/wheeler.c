#include "wheeler.h"
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
#include "client/objects/particle_effect.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

#include "client/exported/animations/wheeler.h"

void Wheeler_Update(GameObject* object);
BOOL Wheeler_Draw(GameObject* object);
void Wheeler_HandleCollision(GameObject* gameObject, GameObject* other);

GameObject* Wheeler_Init(GameObject* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->Update = Wheeler_Update;
	object->Draw = Wheeler_Draw;
	object->HandleCollision = Wheeler_HandleCollision;

	if (ObjectManager_player.x < object->x)
	{
		AnimationUtils_setBatchedAnimationFrame(object, WHEELER_RUN_LEFT_FRAME_INDEX);
		object->speedx = -1;
	}
	else
	{
		object->speedx = 1;
	}	

	return object;
}

void Wheeler_Update(GameObject* object)
{
	object->UpdateAnimation(object);

	object->x += object->speedx;

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
	if (object->screenx + object->rectLeft < SCREEN_LEFT_EDGE)
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

BOOL Wheeler_Draw(GameObject* object)
{
	DRAWUTILS_SETUP_BATCH(object->screenx,
						  object->screeny,
						  object->currentBatchedAnimationFrame->spriteStrips,
						  *object->batchedAnimation->vdpLocation);

	DrawUtils_DrawBatched();

	return TRUE;
}

void Wheeler_HandleCollision(GameObject* gameObject, GameObject* other)
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

		GameObjectTemplate effectGameTemplate;
		effectGameTemplate.objectType = OBJECTTYPE_EFFECT;
		effectGameTemplate.resourceInfo = gameObject->resourceInfo;
		effectGameTemplate.initFunction = ParticleEffect_Init;


		createInfo.gameObjectTemplate = &effectGameTemplate;
		createInfo.startX = gameObject->x;
		createInfo.startY = gameObject->y;

		GameObject* effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setBatchedAnimationFrame(effect, WHEELER_PARTS_HEAD_FRAME_INDEX);
		effect->speedx = 0;
		effect->speedy = -90;

		createInfo.startX += 8;
		effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setBatchedAnimationFrame(effect, WHEELER_PARTS_ARM1_FRAME_INDEX);
		effect->speedx = 15;
		effect->speedy = -60;

		createInfo.startY += 8;
		effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setBatchedAnimationFrame(effect, WHEELER_PARTS_ARM2_FRAME_INDEX);
		effect->speedx = 10;
		effect->speedy = -50;

		createInfo.startX -= 8;
		effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setBatchedAnimationFrame(effect, WHEELER_PARTS_WHEEL_FRAME_INDEX);
		effect->speedx = -10;
		effect->speedy = -50;


	}
	else
	{
		PSGSFXPlay(hit_psg, SFX_CHANNELS2AND3);
	}
}