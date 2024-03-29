#include "bullet.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
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
	UNUSED(createInfo);
	object->Update = Bullet_Update;
	object->HandleCollision = Bullet_HandleCollision;

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
	object->x += object->speedx;
	object->y += object->speedy;

	// world to screen transformation
	object->screenx = object->x - ScrollManager_horizontalScroll;
	object->screeny = object->y - ScrollManager_verticalScroll;

	if (object->screenx > SCREEN_RIGHT ||
		object->screeny > SCREEN_BOTTOM ||
		object->screenx < SCREEN_LEFT ||
		object->screeny < SCREEN_TOP)
	{
		ObjectManager_DestroyObject(object);
	}

	s16 blockX = P2B(object->x);
	s16 blockY = P2B(object->y);

	if (GET_TERRAIN(blockX, blockY) == TERRAIN_SOLID &&
		// don't get affected by terrain at the edge of the screen if the block isn't
		// completely visible on screen. otherwise we might hit the terrain of the other
		// of the screen because of the wrapping.
		blockX - (ScrollManager_horizontalScroll >> 4) < TERRAIN_WIDTH)
	{
		CreateInfo createInfo = 
		{ 
			&impact_template, 
			object->x, 
			object->y
		};

		GameObject* effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);

		ObjectManager_DestroyObject(object);
	}
}

void Bullet_HandleCollision(GameObject* gameObject, GameObject* target)
{
	target->HandleCollision(target, gameObject);

	ObjectManager_DestroyObject(gameObject);

	CreateInfo createInfo = 
	{ 
		&impact_template, 
		gameObject->x, 
		gameObject->y		
	};

	GameObject* effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);

	effect->speedx = gameObject->speedx >> 2;
	effect->speedy = gameObject->speedy >> 2;
}