#include "particle_effect.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/resource_manager.h"
#include "engine/animation_utils.h"

#include <stdio.h>

void ParticleEffect_Update(GameObject* object);
BOOL ParticleEffect_Draw(GameObject* object);

#define GRAVITY	5

GameObject* ParticleEffect_Init(GameObject* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->x = P2V(object->x);
	object->y = P2V(object->y);

	object->Update = ParticleEffect_Update;
	object->Draw = ParticleEffect_Draw;

	return object;
}

void ParticleEffect_Update(GameObject* object)
{
	object->speedy += GRAVITY;

	object->x += object->speedx;
	object->y += object->speedy;

	s16 screenx = V2P(object->x);
	s16 screeny	= V2P(object->y);


	if (screenx > SCREEN_RIGHT + ScrollManager_horizontalScroll ||
		screeny > SCREEN_BOTTOM ||
		screenx < SCREEN_LEFT + ScrollManager_horizontalScroll ||
		screeny < SCREEN_TOP)
	{
		ObjectManager_DestroyObject(object);
	}

	SMS_mapROMBank(object->resourceInfo->bankNumber);
	object->UpdateAnimation(object);
}

BOOL ParticleEffect_Draw(GameObject* object)
{
	SMS_mapROMBank(object->resourceInfo->bankNumber);
	DRAWUTILS_SETUP_BATCH(V2P(object->x) - ScrollManager_horizontalScroll,
						  V2P(object->y),
						  object->currentBatchedAnimationFrame->spriteStrips,
						  *object->batchedAnimation->vdpLocation);


	// should never be clipped
	DrawUtils_DrawBatched();

	return TRUE;
}