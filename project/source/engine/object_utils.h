#ifndef OBJECT_UTILS_INCLUDE_H
#define OBJECT_UTILS_INCLUDE_H

#include "object_types.h"

void ObjectUtils_gameObjectDoNothing(GameObject* gameObject);
void ObjectUtils_doNothing(void);
void ObjectUtils_HandleCollisionDoNothing(GameObject* gameObject, GameObject* other);


//void ObjectUtils_updateObjectScreenRect(GameObject* gameObject);
//void ObjectUtils_updatePlayerScreenRect(GameObject* gameObject);

/*
BOOL ObjectUtils_alwaysVisible(GameObject* gameObject);
BOOL ObjectUtils_isOnScreen(GameObject* gameObject);
BOOL ObjectUtils_isRightOfLeftScreenEdge(GameObject* gameObject);
BOOL ObjectUtils_isLeftOfScreen(GameObject* gameObject);
*/

#endif