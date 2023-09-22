#include "kunai.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/resource_manager.h"
#include "engine/object_types.h"

#include "engine/math_utils.h"
#include "client/tile_types.h"

#include "client/exported/impact.h"
#include "client/objects/effect.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

void Kunai_Update(GameObject* object);
BOOL Kunai_Draw(GameObject* object);
void Kunai_HandleCollision(GameObject* gameObject, GameObject* target);

GameObject* Kunai_Create(const CreateInfo* createInfo)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_PROJECTILE);
	if (!object)
		return NULL;

	object->x = createInfo->startX;
	object->y = createInfo->startY;
	object->Update = Kunai_Update;
	object->Draw = Kunai_Draw;
	object->HandleCollision = Kunai_HandleCollision;

	object->rectLeft = -4;
	object->rectTop = -4;
	object->rectRight = 4;
	object->rectBottom = 4;

	object->damage = 1;

	//object->data1 = 1;

	ResourceManager_SetupResource(object, createInfo->resource);

	PSGSFXPlay(throw_psg, SFX_CHANNELS2AND3);

	return object;
}

void Kunai_Update(GameObject* object)
{
	object->x += object->speedx;
	object->y += object->speedy;

	if (object->x > SCREEN_RIGHT + ScrollManager_horizontalScroll ||
		object->y > SCREEN_BOTTOM ||
		object->x < SCREEN_LEFT + ScrollManager_horizontalScroll ||
		object->y < SCREEN_TOP)
	{
		ObjectManager_DestroyObject(object);
	}

	if (ScrollManager_terrainMap[P2B(object->x) + (P2B(object->y) * ScrollManager_mapWidth)] == TILE_SOLID)
	{
		ObjectManager_DestroyObject(object);

		CreateInfo createInfo = 
		{ 
			object->x, 
			object->y, 
			(const void*)&impact, 
		};

		GameObject* effect = Effect_Create(&createInfo);

		effect->speedx = object->speedx >> 2;
		effect->speedy = object->speedy >> 2;
	}
}

BOOL Kunai_Draw(GameObject* object)
{
	//object->data1 = !object->data1;
	//
	//if (!object->data1)
	//	return FALSE;

	DRAWUTILS_SETUP_BATCH(object->x - ScrollManager_horizontalScroll,
						  object->y,
						  object->currentAnimationBatchedFrame->spriteBatch,
						  *object->animationBatched->vdpLocation);


	// should never be clipped
	DrawUtils_DrawBatched();

	return TRUE;
}

void Kunai_HandleCollision(GameObject* gameObject, GameObject* target)
{
	target->HandleCollision(target, gameObject);

	ObjectManager_DestroyObject(gameObject);

	CreateInfo createInfo = 
	{ 
		gameObject->x, 
		gameObject->y, 
		(const void*)&impact, 
	};

	GameObject* effect = Effect_Create(&createInfo);

	effect->speedx = gameObject->speedx >> 2;
	effect->speedy = gameObject->speedy >> 2;
}