#include "level002.h"

#include "SMSlib.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/vdptile_manager.h"
#include "engine/object_types.h"
#include "engine/animation_types.h"

// exported
#include "client/generated/sprite_vdp_locations.h"

// game objects
#include "client/objects/player.h"
#include "client/objects/kunai.h"
#include "client/objects/enemy.h"
#include "client/objects/right_scroller.h"
#include "client/objects/streaming_spawner.h"

// resources
#include "client/exported/global_palette.h"
#include "client/exported/ninja_girl.h"
#include "client/exported/kunai.h"
#include "client/exported/evil_eye.h"
#include "client/exported/background.h"

void Level002_Init(void)
{
	// load sprite resources
	ninja_girl_spriteVdpLocation = VDPTileManager_LoadSpriteTiles(ninja_girl.tileData, ninja_girl.totalTileCount);
	kunai_spriteVdpLocation = VDPTileManager_LoadSpriteTiles(kunai.tileData, kunai.totalTileCount);	
	evil_eye_spriteVdpLocation = VDPTileManager_LoadSpriteTiles(evil_eye.tileData, evil_eye.totalTileCount);
}

const SpawnInfo level002_spawns[] = 
{
	{ 0, 0, (const void*)&background_map, NULL, RightScroller_Create },
	{ 122, 88, (const void*)&ninja_girl, (u32)&ninja_girl_spriteVdpLocation, Player_Create },
	{ 24, 16, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 24, 48, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 24, 80, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 218, 112, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 218, 144, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 218, 176, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
};

const SpawnInfo level002BootStrapSpawnInfo =
{
	0, 
	0, 
	level002_spawns, 
	8, 
	StreamingSpawner_Create
};

const Level level002 =
{
	Level002_Init,
	globalPalette,
	globalPalette,
	&level002BootStrapSpawnInfo,
};