#include "scroll_manager.h"
#include "scroll_utils.h"
#include "SMSLib.h"

#include "engine/map_types.h"
#include "engine/object_utils.h"
#include "engine/resource_manager.h"

void (*ScrollManager_Update)(GameObject* target) = ObjectUtils_gameObjectDoNothing;
void (*ScrollManager_UpdateVDP)(void) = ObjectUtils_doNothing;

//u8 ScrollManager_speedX = 0;
//u8 ScrollManager_speedY = 0;

u16 ScrollManager_horizontalScroll = 0;
u8 ScrollManager_vdpHorizontalScroll = 0;

u16 ScrollManager_horizontalScrollLimit;

u16 ScrollManager_verticalScroll = 0;

// hard-coded column when we need to show more of the map. Replace
// this with an actual larger map.
u16 ScrollManager_columnBuffer[SCROLLMANAGER_COLUMNBUFFER_HEIGHT];
const u16* ScrollManager_currentMapStrip;

u8 ScrollManager_updateMapVDP = FALSE;