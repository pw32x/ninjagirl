#include "map_types.h"
#include "engine/resource_manager.h"
#include "engine/scroll_manager.h"
#include "engine/vdptile_manager.h"

u16 Load_MapResource(const Map* map)
{
	const Tileset** tilesetRunner = map->tilesets;

	for (u8 loop = 0; loop < map->numTilesets; loop++)
	{
		ResourceManager_LoadResource((void*)*tilesetRunner);

		tilesetRunner++;
	}

	ScrollManager_numTilesets = 0;

	return NULL;
}

u16 Load_TilesetResource(const Tileset* tileset)
{
	VDPTileManager_LoadBackgroundTileset(tileset->tiles, 
										 tileset->numTiles,
										 tileset->vdpLocation);

	ScrollManager_metatileLuts[ScrollManager_numTilesets] = tileset->metatile_lut;
	ScrollManager_tilesetVdpLocations[ScrollManager_numTilesets] = *tileset->vdpLocation;
	ScrollManager_numTilesets++;

	return 0;
}

u16 Load_AnimatedTilesetResource(const AnimatedTileset* animatedTileset)
{
	ResourceManager_LoadResource((void*)animatedTileset->tileAnimation);


	ScrollManager_metatileLuts[ScrollManager_numTilesets] = animatedTileset->metatile_lut;
	ScrollManager_tilesetVdpLocations[ScrollManager_numTilesets] = *animatedTileset->tileAnimation->vdpLocation;
	ScrollManager_numTilesets++;

	return 0;
}