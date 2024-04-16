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

void Bullet_Update(GameObject* object);
void Bullet_HandleCollision(GameObject* gameObject, GameObject* target);

GameObject* Bullet_Init(GameObject* object, const CreateInfo* createInfo)
{
	// 708/708/708.0
	// 80/80/80.0  without sound
	UNUSED(createInfo);
	object->Update = Bullet_Update;
	object->HandleCollision = Bullet_HandleCollision;

	//MSG("%d\n", object->speedx);
	//MSG("%d\n", object->speedy);
	//
	//MSG("%d\n", createInfo->speedX);
	//MSG("%d\n", createInfo->speedY);

	PSGSFXPlay(throw_psg, SFX_CHANNELS2AND3);

	return object;
}

/*
void EraseTiles(GameObject* object)
{
	u16 tileX = object->x << 1;
	u16 tileY = object->y << 1;

	SMS_setTileatXY(tileX	    & 31, tileY, 0);
	SMS_setTileatXY((tileX + 1) & 31, tileY, 0);
	SMS_setTileatXY(tileX	    & 31, tileY + 1, 0);
	SMS_setTileatXY((tileX + 1) & 31, tileY + 1, 0);

	ObjectManager_DestroyObject(object);
}

*/


void Bullet_Update(GameObject* object)
{
	// 1859/1879/1859.4
	// 2859/2879/2859.4
	// 2757/2814/2758.2
	// 2667/2724/2668.2

	object->x += object->speedx;
	object->y += object->speedy;

	//MSG("%d\n", object->speedx);
	//MSG("%d\n", object->speedy);

	// world to screen transformation
	s16 screenX = object->x - ScrollManager_horizontalScroll;
	s16 screenY = object->y - ScrollManager_verticalScroll;

	if (screenX > SCREEN_RIGHT ||
		screenY > SCREEN_BOTTOM ||
		screenX < SCREEN_LEFT ||
		screenY < SCREEN_TOP)
	{
		/*
		EffectCreateInfo effectCreateInfo = 
		{ 
			&impact_template, 
			object->x - 16, 
			object->y,
			object->speedx >> 2,
			object->speedy >> 2,
			0
		};

		ObjectManager_CreateEffect(&effectCreateInfo);
		*/

		ObjectManager_DestroyObject(object);
	}

	object->screenx = screenX;
	object->screeny = screenY;

	object->screenRectLeft = screenX + object->rectLeft;
	object->screenRectTop = screenY + object->rectTop;
	object->screenRectRight = screenX + object->rectRight;
	object->screenRectBottom = screenY + object->rectBottom;

	s16 blockX = P2B(object->x);

	if (GET_TERRAIN(blockX, P2B(object->y)) == TERRAIN_SOLID &&
		// don't get affected by terrain at the edge of the screen if the block isn't
		// completely visible on screen. otherwise we might hit the terrain of the other
		// of the screen because of the wrapping.
		blockX - (ScrollManager_horizontalScroll >> 4) < TERRAIN_SIDE)
	{
		EffectCreateInfo effectCreateInfo = 
		{ 
			&impact_template, 
			object->x, 
			object->y,
			0,
			0
		};

		ObjectManager_CreateEffect(&effectCreateInfo);

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