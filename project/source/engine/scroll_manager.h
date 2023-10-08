#ifndef SCROLL_MANAGER_INCLUDE_H
#define SCROLL_MANAGER_INCLUDE_H

#include "engine/base_types.h"
#include "engine/map_types.h"
#include "engine/object_types.h"


extern void (*ScrollManager_Update)(GameObject* target);
extern void (*ScrollManager_UpdateVDP)(void);

extern u16 ScrollManager_horizontalScroll;
extern u8 ScrollManager_vdpHorizontalScroll;

extern GameObject* ScrollManager_TrackedObject;

#define SCROLLMANAGER_BUFFER_HEIGHT 24
extern u16 ScrollManager_columnBuffer[SCROLLMANAGER_BUFFER_HEIGHT];

extern u8 ScrollManager_updateMapVDP;

extern u8 ScrollManager_speedX;
extern u8 ScrollManager_speedY;

extern const Map* ScrollManager_backgroundMap;

extern const Tileset* ScrollManager_backgroundTileset;

#define MAX_TILESETS 4
extern const u16* ScrollManager_metatileLuts[MAX_TILESETS];
extern u16 ScrollManager_tilesetVdpLocations[MAX_TILESETS];
extern u8 ScrollManager_numTilesets;

extern u16 ScrollManager_mapWidth;
extern u16 ScrollManager_mapWidthLimit;
extern u16 ScrollManager_mapHeight;

extern const u16* ScrollManager_metatileMap;
extern const u16* ScrollManager_metatileLut;
extern const u8*  ScrollManager_terrainMap;

extern u16 ScrollManager_tilesetVdpLocation;

#endif