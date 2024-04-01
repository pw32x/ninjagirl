#include "shotgun.h"
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

void Shotgun_Update(GameObject* object);
void Shotgun_HandleCollision(GameObject* gameObject, GameObject* target);

GameObject* Shotgun_Init(GameObject* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);
	object->Update = Shotgun_Update;
	object->HandleCollision = Shotgun_HandleCollision;

	PSGSFXPlay(throw_psg, SFX_CHANNELS2AND3);

	return object;
}

void Shotgun_Update(GameObject* object)
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

	SMS_mapROMBank(object->resourceInfo->bankNumber);
	if (AnimationUtils_updateBatchedAnimation_noLoop(object) == ANIMATION_FINISHED)
		ObjectManager_DestroyObject(object);
}


void Shotgun_HandleCollision(GameObject* gameObject, GameObject* target)
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