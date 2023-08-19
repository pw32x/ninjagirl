#include "object_manager.h"
#include <string.h>
#include "SMSlib.h"
#include "scroll_manager.h"
#include "spawn_manager.h"

GameObject ObjectManager_player;

#define NUM_OBJECT_SLOTS 5
GameObject ObjectManager_slots[NUM_OBJECT_SLOTS];

void ObjectManager_Init(void)
{
	memset(ObjectManager_slots, 0, sizeof(ObjectManager_slots));
}

void ObjectManager_Update(void)
{
	ObjectManager_player.Update(&ObjectManager_player);
	ScrollManager_Update(&ObjectManager_player);
	SpawnManager_Update();

	// update objects
	GameObject* objectSlotRunner = ObjectManager_slots;

	u8 counter = NUM_OBJECT_SLOTS;

	while (counter--)
	{
		if (objectSlotRunner->isAlive)
			objectSlotRunner->Update(objectSlotRunner);

		objectSlotRunner++;
	}
}

void ObjectManager_Draw(void)
{
	SMS_initSprites();

	ObjectManager_player.Draw(&ObjectManager_player);

	// draw objects
	GameObject* objectSlotRunner = ObjectManager_slots;

	u8 counter = NUM_OBJECT_SLOTS;

	while (counter--)
	{
		if (objectSlotRunner->isAlive)
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
		if (!objectSlotRunner->isAlive)
		{
			objectSlotRunner->isAlive = TRUE;
			return objectSlotRunner;
		}

		objectSlotRunner++;
	}

	return NULL;
}