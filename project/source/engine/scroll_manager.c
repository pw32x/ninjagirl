#include "scroll_manager.h"
#include "scroll_utils.h"
#include "SMSLib.h"
#include "engine/map_types.h"
#include "engine/object_utils.h"

void (*ScrollManager_Update)(GameObject* gameObject) = ObjectUtils_gameObjectDoNothing;
void (*ScrollManager_UpdateVDP)(void) = ObjectUtils_doNothing;

const Map* ScrollManager_backgroundMap;
const Tileset* ScrollManager_backgroundTileset;

u8 ScrollManager_speedX = 0;
u8 ScrollManager_speedY = 0;

u16 ScrollManager_horizontalScroll = 0;
u8 ScrollManager_vdpHorizontalScroll = 0;

// hard-coded column when we need to show more of the map. Replace
// this with an actual larger map.
#define SCROLLMANAGER_COLUMNBUFFER_HEIGHT 24
u16 ScrollManager_buffer[SCROLLMANAGER_COLUMNBUFFER_HEIGHT];

u8 ScrollManager_updateMapVDP = FALSE;


