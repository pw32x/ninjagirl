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
	object->x = P2V(object->x);
	object->y = P2V(object->y);
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
	object->screenx = V2P(object->x) + object->motionSequenceRunner.currentMotionSequenceNode->x - ScrollManager_horizontalScroll;
	object->screeny = V2P(object->y) + object->motionSequenceRunner.currentMotionSequenceNode->y - ScrollManager_verticalScroll;

	// if offscreen destroy
	if (object->screenx + object->rectLeft < SCREEN_LEFT_EDGE)
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

		// drop item
		CreateInfo createInfo = 
		{ 
			&shotgun_item_template,
			V2P(gameObject->x), 
			V2P(gameObject->y),
			0,
			0
		};

		ObjectManager_CreateObjectByCreateInfo(&createInfo);

		// debris 
		GameObjectTemplate effectGameTemplate;
		effectGameTemplate.objectType = OBJECTTYPE_EFFECT;
		effectGameTemplate.resourceInfo = gameObject->resourceInfo;
		effectGameTemplate.initFunction = ParticleEffect_Init;


		/*asdf
		createInfo.gameObjectTemplate = &effectGameTemplate;
		createInfo.startX = V2P(gameObject->x);
		createInfo.startY = V2P(gameObject->y);
		createInfo.speedx = 0;
		createInfo.speedy = -90;
		createInfo.startFrameIndex = DELIVERYROBOT_PARTS_HEAD_FRAME_INDEX;

		SMS_mapROMBank(gameObject->resourceInfo->bankNumber);
		ObjectManager_CreateObjectByCreateInfo(&createInfo);
		AnimationUtils_setMetaSpriteAnimationFrame(effect, );

		*/

		SMS_mapROMBank(gameObject->resourceInfo->bankNumber);

		effectCreateInfo.gameObjectTemplate = &effectGameTemplate;
		effectCreateInfo.speedX = 0,
		effectCreateInfo.speedY = -90,
		effectCreateInfo.startFrameNumber = DELIVERYROBOT_PARTS1_FRAME_INDEX;

		ObjectManager_CreateEffect(&effectCreateInfo);

		effectCreateInfo.startY += 8;
		effectCreateInfo.speedX = 10;
		effectCreateInfo.speedY = -70;
		effectCreateInfo.startFrameNumber = DELIVERYROBOT_PARTS2_FRAME_INDEX;
		ObjectManager_CreateEffect(&effectCreateInfo);

		effectCreateInfo.startX -= 8;
		effectCreateInfo.speedX = -10;
		effectCreateInfo.speedY = -70;
		effectCreateInfo.startFrameNumber = DELIVERYROBOT_PARTS2_FRAME_INDEX;
		ObjectManager_CreateEffect(&effectCreateInfo);
	}
	else
	{
		PSGSFXPlay(hit_psg, SFX_CHANNELS2AND3);
	}
}