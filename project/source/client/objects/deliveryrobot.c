#include "deliveryrobot.h"
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
#include "client/motion_sequence.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

#include "client/exported/animations/weapons/deliveryrobot.h"

void DeliveryRobot_Update(DeliveryRobotObjectType* object);
void DeliveryRobot_HandleCollision(GameObject* gameObject, GameObject* other);

#define SPEEDX 6


const MotionSequenceNode deliveryRobotMotionSequenceNodes[] =
{
	{0, 0, 5},
	{0, -1, 5},
	{0, -2, 5},
	{0, -1, 5},
	{0, 0, 5},
	{0, 1, 5},
	{0, 2, 5},
	{0, 1, 5},
	{0, 0, (u8)-1},
};

const MotionSequence deliveryRobotMotionSequence = 
{
	deliveryRobotMotionSequenceNodes,
	9,
	TRUE
};

GameObject* DeliveryRobot_Init(DeliveryRobotObjectType* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->Update = (ObjectFunctionType)DeliveryRobot_Update;
	object->HandleCollision = DeliveryRobot_HandleCollision;

	SMS_mapROMBank(object->resourceInfo->bankNumber);
	if (ObjectManager_player.x < object->x)
	{
		AnimationUtils_setMetaSpriteAnimationFrame((GameObject*)object, DELIVERYROBOT_LEFT_FRAME_INDEX);
		object->speedx = -SPEEDX;
	}
	else
	{
		object->speedx = SPEEDX;
	}	

	object->motionSequenceRunner.motionSequence = &deliveryRobotMotionSequence;
	object->motionSequenceRunner.currentMotionSequenceNode = deliveryRobotMotionSequence.motionSequenceNodes;
	object->motionSequenceRunner.currentMotionSequenceNodeTime = deliveryRobotMotionSequence.motionSequenceNodes->time;

	return (GameObject*)object;
}


void DeliveryRobot_Update(DeliveryRobotObjectType* object)
{
	SMS_mapROMBank(object->resourceInfo->bankNumber);
	object->UpdateAnimation((GameObject*)object);

	MotionUtils_updateMotion(&object->motionSequenceRunner);

	object->x += object->speedx;

	// world to screen transformation

	// world to screen transformation
	s16 screenX = V2P(object->x) + object->motionSequenceRunner.currentMotionSequenceNode->x - ScrollManager_horizontalScroll;
	s16 screenY = V2P(object->y) + object->motionSequenceRunner.currentMotionSequenceNode->y - ScrollManager_verticalScroll;

	object->screenx = screenX;
	object->screeny = screenY;
	
	object->screenRectLeft = screenX + object->rectLeft;
	object->screenRectTop = screenY + object->rectTop;
	object->screenRectRight = screenX + object->rectRight;
	object->screenRectBottom = screenY + object->rectBottom;

	// if offscreen destroy
	if (object->screenRectLeft < SCREEN_LEFT_EDGE)
	{
		ObjectManager_DestroyObject((GameObject*)object);
		return;
	}
}

void DeliveryRobot_HandleCollision(GameObject* gameObject, GameObject* other)
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
		/*
		// drop item
		CreateInfo createInfo = 
		{ 
			&shotgun_item_template,
			gameObject->x, 
			gameObject->y
		};

		ObjectManager_CreateEnemy(&createInfo);
		*/


		/*
		// debris 
		GameObjectTemplate effectGameTemplate;
		effectGameTemplate.objectType = OBJECTTYPE_EFFECT;
		effectGameTemplate.resourceInfo = gameObject->resourceInfo;
		effectGameTemplate.initFunction = (InitObjectFunctionType)ParticleEffect_Init;
		*/

		/*asdf
		createInfo.gameObjectTemplate = &effectGameTemplate;
		createInfo.startX = gameObject->x;
		createInfo.startY = gameObject->y;
		createInfo.speedx = 0;
		createInfo.speedy = -90;
		createInfo.startFrameIndex = DELIVERYROBOT_PARTS_HEAD_FRAME_INDEX;

		SMS_mapROMBank(gameObject->resourceInfo->bankNumber);
		ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setMetaSpriteAnimationFrame(effect, );

		*/

		/*
		SMS_mapROMBank(gameObject->resourceInfo->bankNumber);

		createInfoEx.gameObjectTemplate = &effectGameTemplate;
		createInfoEx.speedX = 0,
		createInfoEx.speedY = -90,
		createInfoEx.startFrameNumber = DELIVERYROBOT_PARTS1_FRAME_INDEX;

		ObjectManager_CreateEffect(&createInfoEx);

		createInfoEx.startY += 8;
		createInfoEx.speedX = 10;
		createInfoEx.speedY = -70;
		createInfoEx.startFrameNumber = DELIVERYROBOT_PARTS2_FRAME_INDEX;
		ObjectManager_CreateEffect(&createInfoEx);

		createInfoEx.startX -= 8;
		createInfoEx.speedX = -10;
		createInfoEx.speedY = -70;
		createInfoEx.startFrameNumber = DELIVERYROBOT_PARTS2_FRAME_INDEX;
		ObjectManager_CreateEffect(&createInfoEx);
		*/
	}
	else
	{
		PSGSFXPlay(hit_psg, SFX_CHANNELS2AND3);
	}
}