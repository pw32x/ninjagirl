#include "threeshotflyer.h"
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
#include "client/managers/physics_manager.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

#include "client/exported/animations/enemies/threeshotflyer.h"

void ThreeShotFlyer_Update(ThreeShotFlyerObjectType* object);

void ThreeShotFlyer_Roll(ThreeShotFlyerObjectType* object);
void ThreeShotFlyer_Fall(ThreeShotFlyerObjectType* object);

BOOL ThreeShotFlyer_Draw(GameObject* object);
void ThreeShotFlyer_HandleCollision(GameObject* gameObject, GameObject* other);

#define SPEEDX 12

// update x
// update y
// update visibility
// update wall collisions
// update projectile collisions

// queue for drawing

GameObject* ThreeShotFlyer_Init(ThreeShotFlyerObjectType* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->x = P2V(object->x);
	object->y = P2V(object->y);
	object->Update = (ObjectFunctionType)ThreeShotFlyer_Update;
	object->Draw = ThreeShotFlyer_Draw;
	//object->UpdatePhysics = ThreeShotFlyer_Roll;
	object->HandleCollision = ThreeShotFlyer_HandleCollision;

	/*
	SMS_mapROMBank(object->resourceInfo->bankNumber);
	if (ObjectManager_player.x < V2P(object->x))
	{
		AnimationUtils_setBatchedAnimationFrame((GameObject*)object, THREESHOTFLYER_RUN_LEFT_FRAME_INDEX);
		object->speedx = -SPEEDX;
	}
	else
	{
		AnimationUtils_setBatchedAnimationFrame((GameObject*)object, THREESHOTFLYER_RUN_RIGHT_FRAME_INDEX);
		object->speedx = 28;
	}
	*/

	return (GameObject*)object;
}

void ThreeShotFlyer_Update(ThreeShotFlyerObjectType* object)
{
	SMS_mapROMBank(object->resourceInfo->bankNumber);
	object->UpdateAnimation((GameObject*)object);

	// init physics work variables
	PhysicsVars_X = object->x + object->speedx;
	PhysicsVars_Y = object->y + object->speedy;

	//PhysicsVars_GroundBlockX = V2B(PhysicsVars_X);

/*	//PhysicsVars_GroundBlockY = V2B(PhysicsVars_Y + P2V(object->rectBottom));

	/*
	// update x position. 
	//

	// turn around if hit a wall
	if (GET_TERRAIN(PhysicsVars_GroundBlockX, PhysicsVars_GroundBlockY - 1) != TERRAIN_EMPTY)
	{
		object->speedx = -object->speedx;

		if (object->speedx > 0)
		{
			AnimationUtils_setBatchedAnimationFrame((GameObject*)object, THREESHOTFLYER_RUN_RIGHT_FRAME_INDEX);
		}
		else
		{
			AnimationUtils_setBatchedAnimationFrame((GameObject*)object, THREESHOTFLYER_RUN_LEFT_FRAME_INDEX);
		}	
	}

	// update Y position
	object->UpdatePhysics(object);
	*/

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

/*
#define GRAVITY	3

void ThreeShotFlyer_Roll(ThreeShotFlyerObjectType* object)
{
	if (GET_TERRAIN(PhysicsVars_GroundBlockX, PhysicsVars_GroundBlockY) == TERRAIN_EMPTY)
	{
		object->speedy = -30;
		object->UpdatePhysics = ThreeShotFlyer_Fall;
	}
}


void ThreeShotFlyer_Fall(ThreeShotFlyerObjectType* object)
{
	object->speedy += GRAVITY;

	if (GET_TERRAIN(PhysicsVars_GroundBlockX, PhysicsVars_GroundBlockY) != TERRAIN_EMPTY)
	{
		object->y = B2V(PhysicsVars_GroundBlockY) - P2V(object->rectBottom);
		object->speedy = 0;

		object->UpdatePhysics = ThreeShotFlyer_Roll;
	}
}
*/


BOOL ThreeShotFlyer_Draw(GameObject* object)
{
	SMS_mapROMBank(object->resourceInfo->bankNumber);
	DRAWUTILS_SETUP_BATCH(object->screenx,
						  object->screeny,
						  object->currentBatchedAnimationFrame->spriteStrips,
						  *object->batchedAnimation->vdpLocation);

	DrawUtils_DrawBatched();

	return TRUE;
}

void ThreeShotFlyer_HandleCollision(GameObject* gameObject, GameObject* other)
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
	}
	else
	{
		PSGSFXPlay(hit_psg, SFX_CHANNELS2AND3);
	}
}