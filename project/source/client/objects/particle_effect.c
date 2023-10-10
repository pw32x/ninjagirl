#include "particle_effect.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/resource_manager.h"
#include "engine/animation_utils.h"

void ParticleEffect_Update(GameObject* object);
BOOL ParticleEffect_Draw(GameObject* object);

#define GRAVITY	5

GameObject* ParticleEffect_Create(const CreateInfo* createInfo)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_EFFECT);
	if (!object)
		return NULL;

	object->x = P2V(createInfo->startX);
	object->y = P2V(createInfo->startY);
	object->Update = ParticleEffect_Update;
	object->Draw = ParticleEffect_Draw;

	ResourceManager_SetupResource(object, createInfo->resource);

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

	object->UpdateAnimation(object);
}

BOOL ParticleEffect_Draw(GameObject* object)
{
	DRAWUTILS_SETUP_BATCH(V2P(object->x) - ScrollManager_horizontalScroll,
						  V2P(object->y),
						  object->currentBatchedAnimationFrame->batchedSprite,
						  *object->batchedAnimation->vdpLocation);


	// should never be clipped
	DrawUtils_DrawBatched();

	return TRUE;
}