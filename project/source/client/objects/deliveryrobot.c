#include "deliveryrobot.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"
#include "engine/resource_manager.h"
#include "engine/createinfo_types.h"
#include "engine/terrain_manager.h"

#include "client/generated/gameobjecttemplates/gameobject_templates.h"
#include "client/objects/particle_effect.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

#include "client/exported/animations/weapons/deliveryrobot.h"

void DeliveryRobot_Update(GameObject* object);

BOOL DeliveryRobot_Draw(GameObject* object);
void DeliveryRobot_HandleCollision(GameObject* gameObject, GameObject* other);

#define SPEEDX 6

GameObject* DeliveryRobot_Init(GameObject* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->x = P2V(object->x);
	object->y = P2V(object->y);
	object->Update = DeliveryRobot_Update;
	object->Draw = DeliveryRobot_Draw;
	object->HandleCollision = DeliveryRobot_HandleCollision;

	SMS_mapROMBank(object->resourceInfo->bankNumber);
	if (ObjectManager_player.x < object->x)
	{
		AnimationUtils_setBatchedAnimationFrame(object, DELIVERYROBOT_LEFT_FRAME_INDEX);
		object->speedx = -SPEEDX;
	}
	else
	{
		object->speedx = SPEEDX;
	}	

	return object;
}

void DeliveryRobot_Update(GameObject* object)
{
	SMS_mapROMBank(object->resourceInfo->bankNumber);
	object->UpdateAnimation(object);

	// world to screen transformation
	object->screenx = V2P(object->x) - ScrollManager_horizontalScroll;
	object->screeny = V2P(object->y) - ScrollManager_verticalScroll;

	// if offscreen destroy
	if (object->screenx + object->rectLeft < SCREEN_LEFT_EDGE)
	{
		ObjectManager_DestroyObject((GameObject*)object);
		return;
	}
}

BOOL DeliveryRobot_Draw(GameObject* object)
{
	SMS_mapROMBank(object->resourceInfo->bankNumber);
	DRAWUTILS_SETUP_BATCH(object->screenx,
						  object->screeny,
						  object->currentBatchedAnimationFrame->spriteStrips,
						  *object->batchedAnimation->vdpLocation);

	DrawUtils_DrawBatched();

	return TRUE;
}

void DeliveryRobot_HandleCollision(GameObject* gameObject, GameObject* other)
{
	gameObject->health -= other->damage;

	if (gameObject->health <= 0)
	{
		ObjectManager_DestroyObject(gameObject);

		CreateInfo createInfo = 
		{ 
			&explosion_template,
			V2P(gameObject->x), 
			V2P(gameObject->y)
		};
		
		ObjectManager_CreateObjectByCreateInfo(&createInfo);

		PSGSFXPlay(explosion_psg, SFX_CHANNELS2AND3);

		// drop item
		createInfo.gameObjectTemplate = &shotgun_item_template;
		ObjectManager_CreateObjectByCreateInfo(&createInfo);

		// debris 
		GameObjectTemplate effectGameTemplate;
		effectGameTemplate.objectType = OBJECTTYPE_EFFECT;
		effectGameTemplate.resourceInfo = gameObject->resourceInfo;
		effectGameTemplate.initFunction = ParticleEffect_Init;

		/*
		createInfo.gameObjectTemplate = &effectGameTemplate;
		createInfo.startX = V2P(gameObject->x);
		createInfo.startY = V2P(gameObject->y);

		SMS_mapROMBank(gameObject->resourceInfo->bankNumber);
		GameObject* effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setBatchedAnimationFrame(effect, DELIVERYROBOT_PARTS_HEAD_FRAME_INDEX);
		effect->speedx = 0;
		effect->speedy = -90;

		*/


		createInfo.gameObjectTemplate = &effectGameTemplate;
		createInfo.startX = V2P(gameObject->x);
		createInfo.startY = V2P(gameObject->y);

		SMS_mapROMBank(gameObject->resourceInfo->bankNumber);
		GameObject* effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setBatchedAnimationFrame(effect, DELIVERYROBOT_PARTS1_FRAME_INDEX);
		effect->speedx = 0;
		effect->speedy = -90;

		createInfo.startY += 8;
		effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setBatchedAnimationFrame(effect, DELIVERYROBOT_PARTS2_FRAME_INDEX);
		effect->speedx = 10;
		effect->speedy = -70;

		createInfo.startX -= 8;
		effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setBatchedAnimationFrame(effect, DELIVERYROBOT_PARTS2_FRAME_INDEX);
		effect->speedx = -10;
		effect->speedy = -70;

	}
	else
	{
		PSGSFXPlay(hit_psg, SFX_CHANNELS2AND3);
	}
}