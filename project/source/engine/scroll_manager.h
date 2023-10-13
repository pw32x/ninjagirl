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

#define MAX_TILESETS 4
extern const u16* ScrollManager_metatileLuts[MAX_TILESETS];
extern const Tileset* ScrollManager_tilesets[MAX_TILESETS];
extern u16 ScrollManager_tilesetVdpLocations[MAX_TILESETS];
extern u8 ScrollManager_numTilesets;

extern u16 ScrollManager_mapWidth;
extern u16 ScrollManager_mapWidthLimit;
extern u16 ScrollManager_mapHeight;

extern const u16* ScrollManager_map;

extern const Resource* MapManager_tilesetResources[MAX_TILESETS];
extern TilesetFunction MapManager_tilesetFunctions[MAX_TILESETS];

typedef struct
{
	u8 tilesetIndex;
	TilesetFunction tilesetFunction;
	const Resource* resource;
} SetTilesetProperties_Params;

void MapManager_SetTilesetProperties_Command(SetTilesetProperties_Params* params);

#endif