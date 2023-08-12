#ifndef SCROLL_MANAGER_INCLUDE_H
#define SCROLL_MANAGER_INCLUDE_H

#include "types.h"
#include "maptypes.h"
#include "objecttypes.h"

void ScrollManager_Init(const Map* background, const Tileset* backgroundTileset);
void ScrollManager_Update(GameObject* gameObject);
void ScrollManager_UpdateVDP(void);

extern u16 ScrollManager_horizontalScroll;

#endif