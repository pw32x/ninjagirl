#include "kunai.h"
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

void Kunai_Update(GameObject* object);
void Kunai_HandleCollision(GameObject* gameObject, GameObject* target);

GameObject* Kunai_Init(GameObject* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->Update = Kunai_Update;
	object->HandleCollision = Kunai_HandleCollision;

	PSGSFXPlay(throw_psg, SFX_CHANNELS2AND3);

	return object;
}


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


void Kunai_Update(GameObject* object)
{
	object->x += object->speedx;
	object->y += object->speedy;

	object->screenx = object->x - ScrollManager_horizontalScroll;
	object->screeny = object->y;

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
		blockX - (ScrollManager_horizontalScroll >> 4) < TERRAIN_SIDE)
	{
		EffectCreateInfo effectCreateInfo = 
		{ 
			&impact_template, 
			object->x, 
			object->y,
			0,
			0,
			0
		};

		ObjectManager_CreateEffect(&effectCreateInfo);

		ObjectManager_DestroyObject(object);
	}
}

void Kunai_HandleCollision(GameObject* gameObject, GameObject* target)
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
		0,
	};

	ObjectManager_CreateEffect(&effectCreateInfo);
}