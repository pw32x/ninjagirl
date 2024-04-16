#ifndef OBJECT_MANAGER_CREATE_INCLUDE_H
#define OBJECT_MANAGER_CREATE_INCLUDE_H

#include "engine/createinfo_types.h"

void ObjectManager_InitCreate(void);

GameObject* ObjectManager_CreateObject(u8 objectType);
GameObject* ObjectManager_CreateObjectByCreateInfo(const CreateInfo* createInfo);
void ObjectManager_DestroyObject(GameObject* gameObject);

GameObject* ObjectManager_CreatePlayerProjectile(const CreateInfo* createInfo);
GameObject* ObjectManager_CreateEnemyProjectile(const CreateInfo* createInfo);
GameObject* ObjectManager_CreateEffect(const EffectCreateInfo* effectCcreateInfo);


void ObjectManager_processEnemyDeletes(void);
void ObjectManager_processEffectDeletes(void);
void ObjectManager_processProjectileDeletes(void);
void ObjectManager_processEnemyProjectileDeletes(void);

void ObjectManager_processNewObjects(void);

#endif