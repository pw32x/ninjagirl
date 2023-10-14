#include "map_load.h"
#include "engine/resource_manager.h"
#include "engine/map_manager.h"
#include "engine/vdptile_manager.h"

u16 Load_MapResource(const Map* map)
{
	MapManager_mapWidth = map->mapWidth;
	MapManager_mapHeight = map->mapHeight;
	MapManager_mapData = map->mapData;
	MapManager_numTilesets = 0; // we'll leave it to the tile loading to take care of this

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

	MapManager_metatileLuts[MapManager_numTilesets] = tileset->metatile_lut;
	MapManager_tilesets[MapManager_numTilesets] = tileset;
	MapManager_tilesetVdpLocations[MapManager_numTilesets] = *tileset->vdpLocation;
	MapManager_numTilesets++;

	return 0;
}

u16 Load_AnimatedTilesetResource(const AnimatedTileset* animatedTileset)
{
	ResourceManager_LoadResource((void*)animatedTileset->tileAnimation);

	MapManager_metatileLuts[MapManager_numTilesets] = animatedTileset->metatile_lut;
	MapManager_tilesets[MapManager_numTilesets] = (Tileset*)animatedTileset;
	MapManager_tilesetVdpLocations[MapManager_numTilesets] = *animatedTileset->tileAnimation->vdpLocation;
	MapManager_numTilesets++;

	return 0;
}