#include "object_utils.h"
#include "engine/base_defines.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"

void ObjectUtils_gameObjectDoNothing(GameObject* gameObject) { UNUSED(gameObject); }
void ObjectUtils_doNothing(void) {}
void ObjectUtils_HandleCollisionDoNothing(GameObject* gameObject, GameObject* other) { UNUSED(gameObject); UNUSED(other); }

/*
BOOL ObjectUtils_alwaysVisible(GameObject* gameObject)
{
	UNUSED(gameObject);

	return TRUE;
}

BOOL ObjectUtils_isOnScreen(GameObject* gameObject)
{
	return !(gameObject->screenLeft > SCREEN_WIDTH || 
			 gameObject->screenTop > SCREEN_HEIGHT ||
			 gameObject->screenRight < 0 ||
			 gameObject->screenBottom < 0);
}

BOOL ObjectUtils_isRightOfLeftScreenEdge(GameObject* gameObject)
{
	return (gameObject->screenRight >= SCREEN_LEFT);
}

BOOL ObjectUtils_isLeftOfScreen(GameObject* gameObject)
{
	return (gameObject->screenRight < SCREEN_LEFT);
}*/