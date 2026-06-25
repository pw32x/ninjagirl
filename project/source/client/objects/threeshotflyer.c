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
	{(AICommand)AI_COMMAND_WAIT, (void*)10},
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
	object->Update = (ObjectFunctionType)ThreeShotFlyer_Update;
	object->HandleCollision = ThreeShotFlyer_HandleCollision;

	object->aiCommandsRunner.currentAICommandItem = threeShotFlyerAICommandItems_Simple;
	object->aiCommandsRunner.waitTime = 1;

	//object->speedx = 3;

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
	s16 screenX = V2P(PhysicsVars_X) - ScrollManager_horizontalScroll;
	s16 screenY = V2P(PhysicsVars_Y) - ScrollManager_verticalScroll;

	object->screenx = screenX;
	object->screeny = screenY;

	// update position
	object->x = PhysicsVars_X;
	object->y = PhysicsVars_Y;

	object->screenRectLeft = screenX + object->rectLeft;
	object->screenRectTop = screenY + object->rectTop;
	object->screenRectRight = screenX + object->rectRight;
	object->screenRectBottom = screenY + object->rectBottom;

	// destroy if hitting the side edges of the screen
	if (object->screenRectLeft < SCREEN_LEFT_EDGE ||
		object->screenRectRight > SCREEN_WIDTH)
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

		CreateInfoEx createInfoEx = 
		{ 
			&explosion_template,
			gameObject->x,
			gameObject->y,
			0,
			0,
			0
		};
		
		ObjectManager_CreateEffect(&createInfoEx);

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
	CreateInfoEx createInfo = 
	{ 
		&enemy_bullet_template, 
		object->x,
		object->y,
	};

	switch (whichShot)
	{
	case 0:
		createInfo.speedX = P2V(-2);
		createInfo.speedY = P2V(2);
		break;
	case 1:
		createInfo.speedX = P2V(0);
		createInfo.speedY = P2V(2);
		break;
	case 2:
		createInfo.speedX = P2V(2);
		createInfo.speedY = P2V(2);
		break;
	}

	//MSG("FIRE\n");

	ObjectManager_CreateEnemyProjectile(&createInfo);
}