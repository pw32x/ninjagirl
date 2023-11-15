#include "map_load.h"
#include "engine/resource_manager.h"
#include "engine/map_manager.h"
#include "engine/vdptile_manager.h"

#include <string.h>

#include "smslib.h"

u16 Load_MapResource(const Map* map)
{
	MapManager_mapWidth = map->mapWidth;
	MapManager_mapHeight = map->mapHeight;
	MapManager_mapData = map->mapData;
	MapManager_numTilesets = 0; // we'll leave it to the tile loading to take care of this
	MapManager_metatileLutsDataSize = 0;

	for (u16 loop = 0; loop < METATILE_LUT_DATA_SIZE; loop++)
	{
		MapManager_metatileLutsData[loop] = 0xcc;
	}

	const ResourceInfo** tilesetRunner = map->tilesetResourceInfos;

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

	MapManager_metatileLuts[MapManager_numTilesets] = (u16*)(MapManager_metatileLutsData + MapManager_metatileLutsDataSize);

	u16 metatileLutDataSize = tileset->numMetatiles * 2 * 4;

	memcpy(MapManager_metatileLuts[MapManager_numTilesets], tileset->metatile_lut, metatileLutDataSize);

	MapManager_metatileLutsDataSize += metatileLutDataSize;

	memcpy(&MapManager_tilesets[MapManager_numTilesets], tileset, sizeof(Tileset));

	MapManager_tilesetVdpLocations[MapManager_numTilesets] = *tileset->vdpLocation;
	MapManager_numTilesets++;

	return 0;
}

u16 Load_AnimatedTilesetResource(const AnimatedTileset* animatedTileset)
{
	u16 vdpLocation = ResourceManager_LoadResource((void*)animatedTileset->tileAnimationResourceInfo);


	MapManager_metatileLuts[MapManager_numTilesets] = (u16*)(MapManager_metatileLutsData + MapManager_metatileLutsDataSize);

	u16 metatileLutDataSize = animatedTileset->numMetatiles * 2 * 4;

	memcpy(MapManager_metatileLuts[MapManager_numTilesets], animatedTileset->metatile_lut, metatileLutDataSize);

	MapManager_metatileLutsDataSize += metatileLutDataSize;

	memcpy(&MapManager_tilesets[MapManager_numTilesets], animatedTileset, sizeof(AnimatedTileset));

	const ResourceInfo* resourceInfo = animatedTileset->tileAnimationResourceInfo;
	const TileAnimation* tileAnimation = (const TileAnimation*)resourceInfo->resource;

	MapManager_tilesetVdpLocations[MapManager_numTilesets] = vdpLocation;//*tileAnimation->vdpLocation;
	MapManager_numTilesets++;
	
	return 0;
}