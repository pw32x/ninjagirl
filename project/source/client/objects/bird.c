#include "bird.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/draw_utils.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"
#include "engine/resource_manager.h"

void Bird_Update(GameObject* object);
void Bird_Draw(GameObject* object);

GameObject* Bird_Create(const SpawnInfo* spawnInfo)
{
	GameObject* object = ObjectManager_GetAvailableSlot(OBJECTTYPE_ENEMY);
	if (!object)
		return NULL;

	object->x = spawnInfo->startX;
	object->y = spawnInfo->startY;
	object->Update = Bird_Update;
	object->Draw = Bird_Draw;


	ResourceManager_SetupResource(object, spawnInfo->payload);

	object->rectLeft = 0;
	object->rectTop = 0;
	object->rectRight = object->pixelWidth;
	object->rectBottom = object->pixelHeight;


	return object;
}

void Bird_Update(GameObject* object)
{
	s16 screenLeft = object->x - ScrollManager_horizontalScroll;

	if (screenLeft < SCREEN_LEFT)
	{
		ObjectManager_DestroyObject(object);
		return;
	}

	if (object->UpdateAnimation(object))
		ObjectManager_QueueVDPDraw(object, DrawUtils_DrawPlaneAnimationFrame);
}

void Bird_Draw(GameObject* object)
{
	
}

