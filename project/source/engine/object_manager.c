#include "object_manager.h"
#include <string.h>
#include "SMSlib.h"
#include "engine/scroll_manager.h"
#include "engine/spawn_manager.h"
#include "engine/object_utils.h"

GameObject ObjectManager_player;

s16 ObjectManager_objectLeft;
s16 ObjectManager_objectTop;
s16 ObjectManager_objectRight;
s16 ObjectManager_objectBottom;

s16 ObjectManager_playerLeft;
s16 ObjectManager_playerTop;
s16 ObjectManager_playerRight;
s16 ObjectManager_playerBottom;


#define NUM_OBJECT_SLOTS 5
GameObject ObjectManager_slots[NUM_OBJECT_SLOTS];

void ObjectManager_Init(void)
{
	memset(ObjectManager_slots, 0, sizeof(ObjectManager_slots));

	// update objects
	GameObject* objectSlotRunner = ObjectManager_slots;
	u8 counter = NUM_OBJECT_SLOTS;

	while (counter--)
	{
		ObjectManager_DestroyObject(objectSlotRunner);
		objectSlotRunner++;
	}
}

void ObjectManagerUtils_updatePlayerScreenRect(void)
{
	ObjectManager_playerLeft = ObjectManager_player.x - ScrollManager_horizontalScroll;
	ObjectManager_playerTop = ObjectManager_player.y;
	ObjectManager_playerRight = ObjectManager_playerLeft + ObjectManager_player.animation->pixelWidth;
	ObjectManager_playerBottom = ObjectManager_playerTop + ObjectManager_player.animation->pixelWidth;
}


void ObjectManagerUtils_updateObjectScreenRect(GameObject* gameObject)
{
	ObjectManager_objectLeft = gameObject->x - ScrollManager_horizontalScroll;
	ObjectManager_objectTop = gameObject->y;
	ObjectManager_objectRight = ObjectManager_objectLeft + gameObject->animation->pixelWidth;
	ObjectManager_objectBottom = ObjectManager_objectTop + gameObject->animation->pixelWidth;
}


void ObjectManager_Update(void)
{
	ObjectManager_player.Update(&ObjectManager_player);
	ScrollManager_Update(&ObjectManager_player);
	SpawnManager_Update();

	ObjectManagerUtils_updatePlayerScreenRect();

	SMS_initSprites();

	// update objects
	GameObject* objectSlotRunner = ObjectManager_slots;

	u8 counter = NUM_OBJECT_SLOTS;

	ObjectManager_player.Draw(&ObjectManager_player);

	while (counter--)
	{
		objectSlotRunner->Update(objectSlotRunner);
		objectSlotRunner->Draw(objectSlotRunner);
		objectSlotRunner++;
	}
}

void ObjectManager_Draw(void)
{
	// draw objects
	GameObject* objectSlotRunner = ObjectManager_slots;

	u8 counter = NUM_OBJECT_SLOTS;

	while (counter--)
	{
		objectSlotRunner->Draw(objectSlotRunner);
		objectSlotRunner++;
	}
}

GameObject* ObjectManager_GetAvailableSlot(void)
{
	GameObject* objectSlotRunner = ObjectManager_slots;

	u8 counter = NUM_OBJECT_SLOTS;

	while (counter--)
	{
		if (objectSlotRunner->Update == ObjectUtils_gameObjectDoNothing)
		{
			return objectSlotRunner;
		}

		objectSlotRunner++;
	}

	return NULL;
}

void ObjectManager_DestroyObject(GameObject* gameObject)
{
	gameObject->Update = ObjectUtils_gameObjectDoNothing;
	gameObject->Draw = ObjectUtils_gameObjectDoNothing;
}