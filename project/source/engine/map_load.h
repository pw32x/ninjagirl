#ifndef MAP_LOAD_INCLUDE_H
#define MAP_LOAD_INCLUDE_H

#include "engine/map_types.h"

u16 Load_MapResource(const ResourceInfo* resourceInfo);
u16 Load_StripMapResource(const ResourceInfo* resourceInfo);
u16 Load_TilesetResource(const ResourceInfo* resourceInfo);
u16 Load_TilesetResourceSimple(const ResourceInfo* resourceInfo);
u16 Load_AnimatedTilesetResource(const ResourceInfo* resourceInfo);

#endif