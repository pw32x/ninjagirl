#ifndef OBJECT_MANAGER_CREATE_INCLUDE_H
#define OBJECT_MANAGER_CREATE_INCLUDE_H

#include "engine/createinfo_types.h"

void ObjectManager_InitCreate(void);

//GameObject* ObjectManager_CreateObject(u8 objectType);

GameObject* ObjectManager_CreateCommandRunner(const CommandRunnerCreateInfo* createInfo);
GameObject* ObjectManager_CreatePlayer(const CreateInfo* createInfo);
GameObject* ObjectManager_CreateEnemy(const CreateInfo* createInfo);
GameObject* ObjectManager_CreatePlayerProjectile(const CreateInfoEx* createInfo);
GameObject* ObjectManager_CreateEnemyProjectile(const CreateInfoEx* createInfo);
GameObject* ObjectManager_CreateEffect(const CreateInfoEx* effectCcreateInfo);
GameObject* ObjectManager_CreateItem(const CreateInfo* createInfo);

void ObjectManager_DestroyObject(GameObject* gameObject);

void ObjectManager_refreshActiveEnemies(void);
void ObjectManager_refreshActiveEffects(void);
void ObjectManager_refreshActiveProjectiles(void);
void ObjectManager_refreshActiveEnemyProjectiles(void);

#endif