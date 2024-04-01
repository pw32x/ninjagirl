#include "object_manager_vdp.h"
#include "SMSlib.h"
#include "engine/base_defines.h"

#define NUM_VDP_DRAW_ITEMS 4
GameObject* ObjectManager_vdpDrawGameObjects[NUM_VDP_DRAW_ITEMS];
ObjectFunctionType ObjectManager_vdpDrawFunctions[NUM_VDP_DRAW_ITEMS];
u8 ObjectManager_numVdpDrawItems;



void ObjectManager_QueueVDPDraw(GameObject* gameObject, ObjectFunctionType vdpDrawFunction)
{
	//if (ObjectManager_numVdpDrawItems == NUM_VDP_DRAW_ITEMS)
	//	while (1) {}

	ObjectManager_vdpDrawGameObjects[ObjectManager_numVdpDrawItems] = gameObject;
	ObjectManager_vdpDrawFunctions[ObjectManager_numVdpDrawItems] = vdpDrawFunction;

	ObjectManager_numVdpDrawItems++;
}

void ObjectManager_VDPDraw(void)
{
	//SMS_setBackdropColor(COLOR_RED);

	switch (ObjectManager_numVdpDrawItems)
	{
	case 4: ObjectManager_vdpDrawFunctions[3](ObjectManager_vdpDrawGameObjects[3]);
	case 3: ObjectManager_vdpDrawFunctions[2](ObjectManager_vdpDrawGameObjects[2]);
	case 2: ObjectManager_vdpDrawFunctions[1](ObjectManager_vdpDrawGameObjects[1]);
	case 1: ObjectManager_vdpDrawFunctions[0](ObjectManager_vdpDrawGameObjects[0]);
	}

	//SMS_setBackdropColor(COLOR_BLACK);
}