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
#include "engine/terrain_manager.h"

#include "client/generated/gameobjecttemplates/gameobject_templates.h"
#include "client/objects/particle_effect.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

#include "client/exported/animations/enemies/wheeler.h"

void Wheeler_Update(WheelerObjectType* object);

void Wheeler_Roll(WheelerObjectType* object);
void Wheeler_Fall(WheelerObjectType* object);

BOOL Wheeler_Draw(GameObject* object);
void Wheeler_HandleCollision(GameObject* gameObject, GameObject* other);

#define SPEEDX 12

GameObject* Wheeler_Init(WheelerObjectType* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->x = P2V(object->x);
	object->y = P2V(object->y);
	object->Update = (ObjectFunctionType)Wheeler_Update;
	object->Draw = Wheeler_Draw;
	object->UpdatePhysics = Wheeler_Roll;
	object->HandleCollision = Wheeler_HandleCollision;

	if (ObjectManager_player.x < object->x)
	{
		AnimationUtils_setBatchedAnimationFrame((GameObject*)object, WHEELER_RUN_LEFT_FRAME_INDEX);
		object->speedx = -SPEEDX;
	}
	else
	{
		object->speedx = 12;
	}	

	return (GameObject*)object;
}

void Wheeler_Update(WheelerObjectType* object)
{
	object->UpdateAnimation((GameObject*)object);

	object->UpdatePhysics(object);

	// world to screen transformation
	object->screenx = V2P(object->x) - ScrollManager_horizontalScroll;
	object->screeny = V2P(object->y) - ScrollManager_verticalScroll;

	// if offscreen destroy
	if (object->screenx + object->rectLeft < SCREEN_LEFT_EDGE)
	{
		ObjectManager_DestroyObject((GameObject*)object);
		return;
	}

	/*
	// if hits the sides of the screen, turn around
	if (object->screenx + object->rectLeft < SCREEN_LEFT_EDGE)
	{
		object->speedx = -object->speedx;
		AnimationUtils_setBatchedAnimationFrame((GameObject*)object, WHEELER_RUN_RIGHT_FRAME_INDEX);
	}
	else if (object->screenx + object->rectRight > SCREEN_RIGHT)
	{
		object->speedx = -object->speedx;
		AnimationUtils_setBatchedAnimationFrame((GameObject*)object, WHEELER_RUN_LEFT_FRAME_INDEX);
	}
	*/
}

void Wheeler_Roll(WheelerObjectType* object)
{
	object->x += object->speedx;

	s16 blockX = V2B(object->x);

	s16 ySensor = object->y + P2V(object->rectBottom);
	s16 blockY = V2B(ySensor);

	u16 bottomTileType = GET_TERRAIN(blockX, blockY);

	if (bottomTileType == TERRAIN_EMPTY)
	{
		object->speedy = 0;
		object->UpdatePhysics = Wheeler_Fall;
	}
}

#define GRAVITY	3

void Wheeler_Fall(WheelerObjectType* object)
{
	object->speedy += GRAVITY;

	object->x += object->speedx;
	object->y += object->speedy;

	s16 blockX = V2B(object->x);

	s16 ySensor = object->y + P2V(object->rectBottom);
	s16 blockY = V2B(ySensor);

	u16 bottomTileType = GET_TERRAIN(blockX, blockY);

	if (bottomTileType != TERRAIN_EMPTY)
	{
		object->y = B2V(blockY) - P2V(object->rectBottom);
		object->speedy = 0;

		object->UpdatePhysics = Wheeler_Roll;
	}

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
			V2P(gameObject->x), 
			V2P(gameObject->y)
		};
		
		ObjectManager_CreateObjectByCreateInfo(&createInfo);

		PSGSFXPlay(explosion_psg, SFX_CHANNELS2AND3);

		GameObjectTemplate effectGameTemplate;
		effectGameTemplate.objectType = OBJECTTYPE_EFFECT;
		effectGameTemplate.resourceInfo = gameObject->resourceInfo;
		effectGameTemplate.initFunction = ParticleEffect_Init;


		createInfo.gameObjectTemplate = &effectGameTemplate;
		createInfo.startX = V2P(gameObject->x);
		createInfo.startY = V2P(gameObject->y);

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