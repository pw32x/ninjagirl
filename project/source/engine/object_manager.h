#ifndef OBJECT_MANAGER_INCLUDE_H
#define OBJECT_MANAGER_INCLUDE_H

#include "engine/object_types.h"
#include "engine/gameobject_template_types.h"

void ObjectManager_Init(void);

void ObjectManager_Update(void);

GameObject* ObjectManager_CreateObject(u8 objectType);
GameObject* ObjectManager_CreateObjectByTemplate(const GameObjectTemplate* gameObjectTemplate);
void ObjectManager_DestroyObject(GameObject* gameObject);

extern GameObject ObjectManager_player;

// per-frame player screen position
//extern s16 ObjectManager_playerLeft;
//extern s16 ObjectManager_playerTop;
//extern s16 ObjectManager_playerRight;
//extern s16 ObjectManager_playerBottom;

//void ObjectManagerUtils_updatePlayerScreenRect(void);

// when one object is being processed, these values are updated to perform
// drawing and collisions.
//extern s16 ObjectManager_objectLeft;
//extern s16 ObjectManager_objectTop;
//extern s16 ObjectManager_objectRight;
//extern s16 ObjectManager_objectBottom;

//void ObjectManagerUtils_updateObjectScreenRect(GameObject* gameObject);

void ObjectManager_QueueVDPDraw(GameObject* gameObject, ObjectFunctionType vdpDrawFunction);
void ObjectManager_VDPDraw(void);

#endif