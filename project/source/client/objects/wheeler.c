#include "wheeler.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager_create.h"
#include "engine/object_manager_slots.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"
#include "engine/resource_manager.h"
#include "engine/createinfo_types.h"
#include "engine/terrain_manager.h"

#include "client/generated/gameobjecttemplates/gameobject_templates.h"
#include "client/objects/particle_effect.h"
#include "client/managers/physics_manager.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

#include "client/exported/animations/enemies/wheeler.h"

void Wheeler_Update(WheelerObjectType* object);

void Wheeler_Roll(WheelerObjectType* object);
void Wheeler_Fall(WheelerObjectType* object);

void Wheeler_HandleCollision(GameObject* gameObject, GameObject* other);

#define SPEEDX 0 //12

// update x
// update y
// update visibility
// update wall collisions
// update projectile collisions

// queue for drawing

GameObject* Wheeler_Init(WheelerObjectType* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->x = P2V(object->x);
	object->y = P2V(object->y);
	object->Update = (ObjectFunctionType)Wheeler_Update;
	object->UpdatePhysics = Wheeler_Roll;
	object->HandleCollision = Wheeler_HandleCollision;

	SMS_mapROMBank(object->resourceInfo->bankNumber);
	if (ObjectManager_player.x < V2P(object->x))
	{
		AnimationUtils_setMetaSpriteAnimationFrame((GameObject*)object, WHEELER_RUN_LEFT_FRAME_INDEX);
		object->speedx = -SPEEDX;
	}
	else
	{
		AnimationUtils_setMetaSpriteAnimationFrame((GameObject*)object, WHEELER_RUN_RIGHT_FRAME_INDEX);
		object->speedx = 28;
	}	

	return (GameObject*)object;
}

void Wheeler_Update(WheelerObjectType* object)
{
	SMS_mapROMBank(object->resourceInfo->bankNumber);
	object->UpdateAnimation((GameObject*)object);

	// init physics work variables
	PhysicsVars_X = object->x + object->speedx;
	PhysicsVars_Y = object->y + object->speedy;
	
	PhysicsVars_GroundBlockX = V2B(PhysicsVars_X);
	PhysicsVars_GroundBlockY = V2B(PhysicsVars_Y + P2V(object->rectBottom));

	// update x position. 
	//

	// turn around if hit a wall
	if (GET_TERRAIN(PhysicsVars_GroundBlockX, PhysicsVars_GroundBlockY - 1) != TERRAIN_EMPTY)
	{
		object->speedx = -object->speedx;

		if (object->speedx > 0)
		{
			AnimationUtils_setMetaSpriteAnimationFrame((GameObject*)object, WHEELER_RUN_RIGHT_FRAME_INDEX);
		}
		else
		{
			AnimationUtils_setMetaSpriteAnimationFrame((GameObject*)object, WHEELER_RUN_LEFT_FRAME_INDEX);
		}	
	}

	// update Y position
	object->UpdatePhysics(object);

	// update object 
	//
	

	// world to screen transformation
	object->screenx = V2P(PhysicsVars_X) - ScrollManager_horizontalScroll;
	object->screeny = V2P(PhysicsVars_Y) - ScrollManager_verticalScroll;

	// update position
	object->x = PhysicsVars_X;
	object->y = PhysicsVars_Y;

	// destroy if hitting the side edges of the screen
	if (object->screenx + object->rectLeft < SCREEN_LEFT_EDGE ||
		object->screenx + object->rectRight > SCREEN_WIDTH)
	{
		ObjectManager_DestroyObject((GameObject*)object);
		return;
	}
}

#define GRAVITY	3

void Wheeler_Roll(WheelerObjectType* object)
{
	if (GET_TERRAIN(PhysicsVars_GroundBlockX, PhysicsVars_GroundBlockY) == TERRAIN_EMPTY)
	{
		object->speedy = -30;
		object->UpdatePhysics = Wheeler_Fall;
	}
}


void Wheeler_Fall(WheelerObjectType* object)
{
	object->speedy += GRAVITY;

	if (GET_TERRAIN(PhysicsVars_GroundBlockX, PhysicsVars_GroundBlockY) != TERRAIN_EMPTY)
	{
		object->y = B2V(PhysicsVars_GroundBlockY) - P2V(object->rectBottom);
		object->speedy = 0;

		object->UpdatePhysics = Wheeler_Roll;
	}
}



void Wheeler_HandleCollision(GameObject* gameObject, GameObject* other)
{
	gameObject->health -= other->damage;

	if (gameObject->health <= 0)
	{
		//ObjectManager_DestroyObject(gameObject);

		EffectCreateInfo effectCreateInfo = 
		{ 
			&explosion_template,
			V2P(gameObject->x), 
			V2P(gameObject->y),
			0,
			0,
			0
		};
		
		ObjectManager_CreateEffect(&effectCreateInfo);

		PSGSFXPlay(explosion_psg, SFX_CHANNELS2AND3);
		/*
		GameObjectTemplate effectGameTemplate;
		effectGameTemplate.objectType = OBJECTTYPE_EFFECT;
		effectGameTemplate.resourceInfo = gameObject->resourceInfo;
		effectGameTemplate.initFunction = ParticleEffect_Init;


		createInfo.gameObjectTemplate = &effectGameTemplate;
		createInfo.startX = V2P(gameObject->x);
		createInfo.startY = V2P(gameObject->y);

		SMS_mapROMBank(gameObject->resourceInfo->bankNumber);
		GameObject* effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setMetaSpriteAnimationFrame(effect, WHEELER_PARTS_HEAD_FRAME_INDEX);
		effect->speedx = 0;
		effect->speedy = -90;

		createInfo.startX += 8;
		effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setMetaSpriteAnimationFrame(effect, WHEELER_PARTS_ARM1_FRAME_INDEX);
		effect->speedx = 15;
		effect->speedy = -60;

		createInfo.startY += 8;
		effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setMetaSpriteAnimationFrame(effect, WHEELER_PARTS_ARM2_FRAME_INDEX);
		effect->speedx = 10;
		effect->speedy = -50;

		createInfo.startX -= 8;
		effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setMetaSpriteAnimationFrame(effect, WHEELER_PARTS_WHEEL_FRAME_INDEX);
		effect->speedx = -10;
		effect->speedy = -50;
		*/


	}
	else
	{
		PSGSFXPlay(hit_psg, SFX_CHANNELS2AND3);
	}
}