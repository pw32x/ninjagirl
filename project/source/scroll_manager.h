#ifndef SCROLL_MANAGER_INCLUDE_H
#define SCROLL_MANAGER_INCLUDE_H

#include "types.h"
#include "map_types.h"
#include "object_types.h"

void ScrollManager_Init(const Map* backgroundMap);
void ScrollManager_Update(GameObject* gameObject);
void ScrollManager_UpdateVDP(void);

extern u16 ScrollManager_horizontalScroll;

#endif