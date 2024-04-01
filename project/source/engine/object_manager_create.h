#ifndef OBJECT_MANAGER_CREATE_INCLUDE_H
#define OBJECT_MANAGER_CREATE_INCLUDE_H

#include "engine/createinfo_types.h"

void ObjectManager_InitCreate(void);

GameObject* ObjectManager_CreateObject(u8 objectType);
GameObject* ObjectManager_CreateObjectByCreateInfo(const CreateInfo* createInfo);
void ObjectManager_DestroyObject(GameObject* gameObject);

extern u8 ObjectManager_numEnemies;
extern u8 ObjectManager_numEffects;

#endif