#ifndef MAP_LOAD_INCLUDE_H
#define MAP_LOAD_INCLUDE_H

#include "engine/map_types.h"

u16 Load_MapResource(const Map* map);
u16 Load_TilesetResource(const Tileset* tileset);
u16 Load_AnimatedTilesetResource(const AnimatedTileset* animatedTileset);

#endif