#ifndef OBJECT_MANAGER_VDP_INCLUDE_H
#define OBJECT_MANAGER_VDP_INCLUDE_H

#include "engine/object_types.h"

extern u8 ObjectManager_numVdpDrawItems;

void ObjectManager_QueueVDPDraw(GameObject* gameObject, ObjectFunctionType vdpDrawFunction);
void ObjectManager_VDPDraw(void);

#endif