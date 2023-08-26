#include "enemy.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"


void Enemy_Update(GameObject* object);
void Enemy_Draw(GameObject* object);

GameObject* Enemy_Create(const SpawnInfo* spawnInfo)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_ENEMY);
	if (!object)
		return NULL;

	object->x = spawnInfo->startX;
	object->y = spawnInfo->startY;
	object->Update = Enemy_Update;
	object->Draw = Enemy_Draw;

	AnimationUtils_setupAnimation(object, (const Animation*)spawnInfo->payload, *((u8*)spawnInfo->additionalPayload));

	return object;
}

#define LEFT 0
#define TOP 1
#define RIGHT 2
#define BOTTOM 3

void Enemy_Update(GameObject* object)
{
	AnimationUtils_updateAnimation(object);

	ObjectManagerUtils_updateObjectScreenRect(object);

	/*
	// player collision
	if (ObjectManager_playerLeft < ObjectManager_objectRight &&
		ObjectManager_playerRight > ObjectManager_objectLeft &&
		ObjectManager_playerTop < ObjectManager_objectBottom &&
		ObjectManager_playerBottom > ObjectManager_objectTop)
	{
		goto destroy_object;
	}

	// if offscreen die
	if (ObjectManager_objectRight < SCREEN_LEFT)
	{z
		goto destroy_object;
	}
	*/

	// projectile collisions
	s16* ObjectManager_projectileRectRunner = ObjectManager_projectileRect;

	//if (ObjectManager_objectLeft > ObjectManager_projectileRectRunner[RIGHT] &&
	//	ObjectManager_objectTop > ObjectManager_projectileRectRunner[BOTTOM] &&
	//	ObjectManager_objectRight < ObjectManager_projectileRectRunner[LEFT] &&
	//	ObjectManager_objectBottom < ObjectManager_projectileRectRunner[TOP])


	if (ObjectManager_objectLeft < ObjectManager_projectileRectRunner[RIGHT] &&
		ObjectManager_objectRight > ObjectManager_projectileRectRunner[LEFT] &&
		ObjectManager_objectTop < ObjectManager_projectileRectRunner[BOTTOM] &&
		ObjectManager_objectBottom > ObjectManager_projectileRectRunner[TOP])
	{
		goto destroy_object;
	}

	ObjectManager_projectileRectRunner += 4;
		
	if (ObjectManager_objectLeft < ObjectManager_projectileRectRunner[RIGHT] &&
		ObjectManager_objectRight > ObjectManager_projectileRectRunner[LEFT] &&
		ObjectManager_objectTop < ObjectManager_projectileRectRunner[BOTTOM] &&
		ObjectManager_objectBottom > ObjectManager_projectileRectRunner[TOP])
	{
		goto destroy_object;
	}

	ObjectManager_projectileRectRunner += 4;

	if (ObjectManager_objectLeft > ObjectManager_projectileRectRunner[RIGHT] ||
		ObjectManager_objectRight < ObjectManager_projectileRectRunner[LEFT] ||
		ObjectManager_objectTop > ObjectManager_projectileRectRunner[BOTTOM] ||
		ObjectManager_objectBottom < ObjectManager_projectileRectRunner[TOP])
	{
		return;
	}

destroy_object:
	ObjectManager_DestroyObject(object);
}

void Enemy_Draw(GameObject* object)
{
	DRAWUTILS_SETUP(ObjectManager_objectLeft,
					ObjectManager_objectTop,
					object->currentAnimationFrame->numSprites, 
					object->currentAnimationFrame->sprites,
					object->animationVdpTileIndex);

	if (ObjectManager_objectLeft < SCREEN_LEFT || 
		ObjectManager_objectRight > SCREEN_RIGHT)
	{
		DrawUtils_DrawClippedSides();
	}
	else
	{
		DrawUtils_Draw();
	}
}

