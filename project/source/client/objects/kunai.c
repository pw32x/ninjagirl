#include "kunai.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/resource_manager.h"
#include "engine/object_types.h"
#include "engine/animation_utils.h"
#include "engine/terrain_manager.h"

#include "engine/math_utils.h"

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

	if (object->x > SCREEN_RIGHT + ScrollManager_horizontalScroll ||
		object->y > SCREEN_BOTTOM ||
		object->x < SCREEN_LEFT + ScrollManager_horizontalScroll ||
		object->y < SCREEN_TOP)
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
			object->x, 
			object->y, 
			(const void*)&impact, 
		};

		GameObject* effect = Effect_Create(&createInfo);

		// destroy or setup erasing a block for later.
		u8 tilesetIndex = GET_TILESET_INDEX(blockX, blockY);

		if (ScrollManager_tilesets[tilesetIndex]->breakable)
		{
			SET_TERRAIN_VALUE(blockX, blockY, TERRAIN_EMPTY);
			object->x = blockX;
			object->y = blockY;
			ObjectManager_QueueVDPDraw(object, EraseTiles);
			object->Draw = ObjectUtils_drawNothing;
		}
		else
		{
			ObjectManager_DestroyObject(object);
		}

		//effect->speedx = object->speedx >> 2;
		//effect->speedy = object->speedy >> 2;
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
						  object->currentBatchedAnimationFrame->batchedSprite,
						  *object->batchedAnimation->vdpLocation);


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