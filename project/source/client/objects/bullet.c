#include "bullet.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager_create.h"
#include "engine/scroll_manager.h"
#include "engine/map_manager.h"
#include "engine/object_utils.h"
#include "engine/resource_manager.h"
#include "engine/object_types.h"
#include "engine/animation_utils.h"
#include "engine/terrain_manager.h"

#include "engine/math_utils.h"

//#include "client/exported/animations/impact.h"
#include "client/generated/gameobjecttemplates/gameobject_templates.h"
#include "client/objects/basic_effect.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

void Bullet_UpdateLeft(GameObject* object);
void Bullet_UpdateRight(GameObject* object);
void Bullet_UpdateUp(GameObject* object);
void Bullet_UpdateDown(GameObject* object);
void Bullet_HandleCollision(GameObject* gameObject, GameObject* target);

GameObject* Bullet_Init(GameObject* object, const CreateInfo* createInfo)
{
	// 708/708/708.0
	// 80/80/80.0  without sound
	UNUSED(createInfo);

	s8 speedx = createInfo->speedX;
	s8 speedy = createInfo->speedY;

	u8 speedxNegative = speedx < 0;
	u8 speedyNegative = speedy < 0;

	s8 absSpeedX = speedxNegative ? -speedx : speedx;
	s8 absSpeedY = speedyNegative ? -speedy : speedy;

	if (absSpeedY > absSpeedX)
	{
		object->Update = speedyNegative ? Bullet_UpdateUp : Bullet_UpdateDown;
	}
	else
	{
		object->Update = speedxNegative ? Bullet_UpdateLeft : Bullet_UpdateRight;
	}

	object->HandleCollision = Bullet_HandleCollision;

	//MSG("%d\n", object->speedx);
	//MSG("%d\n", object->speedy);
	//
	//MSG("%d\n", createInfo->speedX);
	//MSG("%d\n", createInfo->speedY);

	//PSGSFXPlay(throw_psg, SFX_CHANNELS2AND3);

	return object;
}

void Bullet_UpdateLeft(GameObject* object)
{
	object->x += object->speedx;
	object->y += object->speedy;

	// world to screen transformation
	object->screenx = object->x - ScrollManager_horizontalScroll;
	object->screeny = object->y - ScrollManager_verticalScroll;

	if (object->screenx < SCREEN_LEFT)
	{
		ObjectManager_DestroyObject(object);
	}
}

void Bullet_UpdateRight(GameObject* object)
{
	// 1046/1188/1048.9
	// 1040/1182/1042.9

	object->x += object->speedx;
	object->y += object->speedy;

	// world to screen transformation
	object->screenx = object->x - ScrollManager_horizontalScroll;
	object->screeny = object->y - ScrollManager_verticalScroll;

	if (object->screenx > SCREEN_RIGHT)
	{
		ObjectManager_DestroyObject(object);
	}
}


void Bullet_UpdateUp(GameObject* object)
{
	object->x += object->speedx;
	object->y += object->speedy;

	// world to screen transformation
	object->screenx = object->x - ScrollManager_horizontalScroll;
	object->screeny = object->y - ScrollManager_verticalScroll;

	if (object->screeny < SCREEN_TOP)
	{
		ObjectManager_DestroyObject(object);
	}
}

void Bullet_UpdateDown(GameObject* object)
{
	object->x += object->speedx;
	object->y += object->speedy;

	// world to screen transformation
	object->screenx = object->x - ScrollManager_horizontalScroll;
	object->screeny = object->y - ScrollManager_verticalScroll;

	if (object->screeny > SCREEN_BOTTOM)
	{
		ObjectManager_DestroyObject(object);
	}
}

void Bullet_HandleCollision(GameObject* gameObject, GameObject* target)
{
	target->HandleCollision(target, gameObject);

	ObjectManager_DestroyObject(gameObject);

	EffectCreateInfo effectCreateInfo = 
	{ 
		&impact_template, 
		gameObject->x, 
		gameObject->y,
		gameObject->speedx >> 2,
		gameObject->speedy >> 2,
		0
	};

	ObjectManager_CreateEffect(&effectCreateInfo);
}