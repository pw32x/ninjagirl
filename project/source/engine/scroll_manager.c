#include "scroll_manager.h"
#include "scroll_utils.h"
#include "SMSLib.h"
#include "engine/map_types.h"
#include "engine/object_utils.h"

void (*ScrollManager_Update)(GameObject* target) = ObjectUtils_gameObjectDoNothing;
void (*ScrollManager_UpdateVDP)(void) = ObjectUtils_doNothing;

const Map* ScrollManager_backgroundMap;

const u16* ScrollManager_metatileLuts[MAX_TILESETS];
const Tileset* ScrollManager_tilesets[MAX_TILESETS];
u16 ScrollManager_tilesetVdpLocations[MAX_TILESETS];
u8 ScrollManager_numTilesets;

u16 ScrollManager_mapWidth;
u16 ScrollManager_mapWidthLimit;
u16 ScrollManager_mapHeight;

const u16* ScrollManager_map;

u16 ScrollManager_tilesetVdpLocation;

u8 ScrollManager_speedX = 0;
u8 ScrollManager_speedY = 0;

u16 ScrollManager_horizontalScroll = 0;
u8 ScrollManager_vdpHorizontalScroll = 0;

// hard-coded column when we need to show more of the map. Replace
// this with an actual larger map.
#define SCROLLMANAGER_COLUMNBUFFER_HEIGHT 24
u16 ScrollManager_columnBuffer[SCROLLMANAGER_COLUMNBUFFER_HEIGHT];

u8 ScrollManager_updateMapVDP = FALSE;


