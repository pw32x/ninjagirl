#include "map_types.h"
#include "engine/vdptile_manager.h"

u16 Load_MapResource(const Map* map)
{
	const Tileset* tileset = map->tileset;

	VDPTileManager_LoadBackgroundTileset(tileset->tiles, 
										 tileset->numTiles,
										 tileset->vdpLocation);

	return *tileset->vdpLocation;
}

