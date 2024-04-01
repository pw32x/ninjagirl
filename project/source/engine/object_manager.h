#ifndef OBJECT_MANAGER_INCLUDE_H
#define OBJECT_MANAGER_INCLUDE_H

void ObjectManager_Init(void);
void ObjectManager_Update(void);


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

#endif