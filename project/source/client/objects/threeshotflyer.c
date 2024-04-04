#include "threeshotflyer.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager_create.h"
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

void ThreeShotFlyer_Fire(ThreeShotFlyerObjectType* object, u16 whichShot);

const AICommandItem threeShotFlyerAICommandItems[] =
{
	{(AICommand)AI_COMMAND_SET_SPEEDX, (void*)0},
	{(AICommand)AI_COMMAND_SET_SPEEDY, (void*)5},
	{(AICommand)AI_COMMAND_WAIT, (void*)60},
	{(AICommand)AI_COMMAND_SET_SPEEDX, (void*)-5},
	{(AICommand)AI_COMMAND_SET_SPEEDY, (void*)0},
	{(AICommand)AI_COMMAND_WAIT, (void*)60},
	{(AICommand)AI_COMMAND_SET_SPEEDX, (void*)0},
	{(AICommand)AI_COMMAND_SET_SPEEDY, (void*)-5},
	{(AICommand)AI_COMMAND_WAIT, (void*)60},
	{(AICommand)AI_COMMAND_SET_SPEEDX, (void*)5},
	{(AICommand)AI_COMMAND_SET_SPEEDY, (void*)0},
	{(AICommand)AI_COMMAND_WAIT, (void*)60},
	{(AICommand)AI_COMMAND_SET_SPEEDX, (void*)0},
	{(AICommand)AI_COMMAND_SET_SPEEDY, (void*)0},
	{(AICommand)ThreeShotFlyer_Fire, (void*)0},
	{(AICommand)AI_COMMAND_WAIT, (void*)20},
	{(AICommand)ThreeShotFlyer_Fire, (void*)1},
	{(AICommand)AI_COMMAND_WAIT, (void*)20},
	{(AICommand)ThreeShotFlyer_Fire, (void*)2},
	{(AICommand)AI_COMMAND_WAIT, (void*)20},	
	{(AICommand)AI_COMMAND_JUMP, (void*)-21},
};

const AICommandItem threeShotFlyerAICommandItems_Simple[] =
{
	{(AICommand)AI_COMMAND_WAIT, (void*)120},
	{(AICommand)ThreeShotFlyer_Fire, (void*)1},
	{(AICommand)AI_COMMAND_JUMP, (void*)-3},
};


void ThreeShotFlyer_Update(ThreeShotFlyerObjectType* object);

void ThreeShotFlyer_Roll(ThreeShotFlyerObjectType* object);
void ThreeShotFlyer_Fall(ThreeShotFlyerObjectType* object);

void ThreeShotFlyer_HandleCollision(GameObject* gameObject, GameObject* other);

GameObject* ThreeShotFlyer_Init(ThreeShotFlyerObjectType* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->x = P2V(object->x);
	object->y = P2V(object->y);
	object->Update = (ObjectFunctionType)ThreeShotFlyer_Update;
	object->HandleCollision = ThreeShotFlyer_HandleCollision;

	object->aiCommandsRunner.currentAICommandItem = threeShotFlyerAICommandItems_Simple;
	object->aiCommandsRunner.waitTime = 1;

	return (GameObject*)object;
}

void ThreeShotFlyer_Update(ThreeShotFlyerObjectType* object)
{
	SMS_mapROMBank(object->resourceInfo->bankNumber);
	object->UpdateAnimation((GameObject*)object);

	// init physics work variables
	PhysicsVars_X = object->x + object->speedx;
	PhysicsVars_Y = object->y + object->speedy;


	// update Y position
	AICommandUtils_updateAICommandsRunner((GameObject*)object, &object->aiCommandsRunner);

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


void ThreeShotFlyer_HandleCollision(GameObject* gameObject, GameObject* other)
{
	gameObject->health -= other->damage;

	if (gameObject->health <= 0)
	{
		ObjectManager_DestroyObject(gameObject);

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
	}
	else
	{
		PSGSFXPlay(hit_psg, SFX_CHANNELS2AND3);
	}
}

void ThreeShotFlyer_Fire(ThreeShotFlyerObjectType* object, u16 whichShot)
{
	//SMS_debugPrintf("Default");
	CreateInfo createInfo = 
	{ 
		&enemy_bullet_template, 
		V2P(object->x),
		V2P(object->y),
		0,
		0
	};

	switch (whichShot)
	{
	case 0:
		createInfo.speedX = -2;
		createInfo.speedY = 2;
		break;
	case 1:
		createInfo.speedX = 0;
		createInfo.speedY = 2;
		break;
	case 2:
		createInfo.speedX = 2;
		createInfo.speedY = 2;
		break;
	}

	ObjectManager_CreateObjectByCreateInfo(&createInfo);
}