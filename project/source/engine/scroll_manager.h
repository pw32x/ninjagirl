#ifndef SCROLL_MANAGER_INCLUDE_H
#define SCROLL_MANAGER_INCLUDE_H

#include "engine/base_types.h"
#include "engine/object_types.h"

extern void (*ScrollManager_Update)(GameObject* target);
extern void (*ScrollManager_UpdateVDP)(void);

extern u16 ScrollManager_horizontalScroll;
extern u8 ScrollManager_vdpHorizontalScroll;

extern u16 ScrollManager_horizontalScrollLimit;

extern u16 ScrollManager_verticalScroll;

extern GameObject* ScrollManager_TrackedObject;

#define SCROLLMANAGER_BUFFER_HEIGHT 24
extern u16 ScrollManager_columnBuffer[SCROLLMANAGER_BUFFER_HEIGHT];

extern u8 ScrollManager_updateMapVDP;

//extern u8 ScrollManager_speedX;
//extern u8 ScrollManager_speedY;



#endif