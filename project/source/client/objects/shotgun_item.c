#include "shotgun_item.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"
#include "engine/resource_manager.h"
#include "engine/createinfo_types.h"
#include "engine/terrain_manager.h"

#include "client/generated/gameobjecttemplates/gameobject_templates.h"
#include "client/objects/basic_effect.h"
#include "client/managers/weapon_manager.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

void ShotgunItem_Update(ShotgunItemObjectType* object);

void ShotgunItem_Sit(ShotgunItemObjectType* object);
void ShotgunItem_Fall(ShotgunItemObjectType* object);

void ShotgunItem_HandleCollision(GameObject* gameObject, GameObject* other);

GameObject* ShotgunItem_Init(ShotgunItemObjectType* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->x = P2V(object->x);
	object->y = P2V(object->y);
	object->Update = (ObjectFunctionType)ShotgunItem_Update;
	object->UpdatePhysics = ShotgunItem_Fall;
	object->HandleCollision = ShotgunItem_HandleCollision;

	return (GameObject*)object;
}

void ShotgunItem_Update(ShotgunItemObjectType* object)
{
	SMS_mapROMBank(object->resourceInfo->bankNumber);
	object->UpdateAnimation((GameObject*)object);
	object->UpdatePhysics(object);

	// world to screen transformation
	object->screenx = V2P(object->x) - ScrollManager_horizontalScroll;
	object->screeny = V2P(object->y) - ScrollManager_verticalScroll;

	// if offscreen die
	if (object->screenx + object->rectLeft < SCREEN_LEFT)
	{
		//SMS_debugPrintf("object->screenx: %d\n", object->screenx);
		goto destroy_object;
	}
	
	return;

destroy_object:
	//SMS_debugPrintf("Destroy Object\n");
	ObjectManager_DestroyObject((GameObject*)object);
}


void ShotgunItem_Sit(ShotgunItemObjectType* object)
{
	/*
	object->x += object->speedx;

	s16 blockX = V2B(object->x);

	s16 ySensor = object->y + P2V(object->rectBottom);
	s16 blockY = V2B(ySensor);

	u16 bottomTileType = GET_TERRAIN(blockX, blockY);

	if (bottomTileType == TERRAIN_EMPTY)
	{
		object->speedy = 0;
		object->UpdatePhysics = ShotgunItem_Fall;
	}
	*/
}

#define GRAVITY	3

void ShotgunItem_Fall(ShotgunItemObjectType* object)
{
	object->speedy += GRAVITY;

	object->x += object->speedx;
	object->y += object->speedy;

	s16 blockX = V2B(object->x);

	s16 ySensor = object->y + P2V(object->rectBottom);
	s16 blockY = V2B(ySensor);

	u16 bottomTileType = GET_TERRAIN(blockX, blockY);

	if (bottomTileType != TERRAIN_EMPTY)
	{
		object->y = B2V(blockY) - P2V(object->rectBottom);
		object->speedy = 0;

		object->UpdatePhysics = ShotgunItem_Sit;
	}

}

void ShotgunItem_HandleCollision(GameObject* gameObject, GameObject* other)
{
	ObjectManager_DestroyObject(gameObject);

	WeaponManager_SwitchWeapon(WEAPON_SHOTGUN);
}