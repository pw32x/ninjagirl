#include "map_types.h"
#include "resource_manager.h"

#include "engine/vdptile_manager.h"

u16 Load_MapResource(const Map* map)
{
	const Tileset** tilesetRunner = map->tilesets;

	for (u8 loop = 0; loop < map->numTilesets; loop++)
	{
		ResourceManager_LoadResource((void*)*tilesetRunner);

		tilesetRunner++;
	}

	return NULL;
}

u16 Load_TilesetResource(const Tileset* tileset)
{
	VDPTileManager_LoadBackgroundTileset(tileset->tiles, 
										 tileset->numTiles,
										 tileset->vdpLocation);

	return 0;
}

u16 Load_AnimatedTilesetResource(const AnimatedTileset* animatedTileset)
{
	ResourceManager_LoadResource((void*)animatedTileset->tileAnimation);

	return 0;
}