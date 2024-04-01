#include "particle_effect.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager_create.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/resource_manager.h"
#include "engine/animation_utils.h"

#include <stdio.h>

void ParticleEffect_Update(GameObject* object);

#define GRAVITY	5

GameObject* ParticleEffect_Init(GameObject* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->x = P2V(object->x);
	object->y = P2V(object->y);

	object->Update = ParticleEffect_Update;

	return object;
}

void ParticleEffect_Update(GameObject* object)
{
	object->speedy += GRAVITY;

	object->x += object->speedx;
	object->y += object->speedy;

	object->screenx = V2P(object->x) - ScrollManager_horizontalScroll;
	object->screeny	= V2P(object->y);


	if (object->screenx > SCREEN_RIGHT ||
		object->screeny > SCREEN_BOTTOM ||
		object->screenx < SCREEN_LEFT ||
		object->screeny < SCREEN_TOP)
	{
		ObjectManager_DestroyObject(object);
	}

	SMS_mapROMBank(object->resourceInfo->bankNumber);
	object->UpdateAnimation(object);
}
