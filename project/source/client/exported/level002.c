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
	ninja_girl_spriteVdpLocation = VDPTileManager_LoadAnimationTiles(&ninja_girl);
	kunai_spriteVdpLocation = VDPTileManager_LoadAnimationTiles(&kunai);	
	evil_eye_spriteVdpLocation = VDPTileManager_LoadAnimationTiles(&evil_eye);
}

const SpawnInfo level002_spawns[] = 
{
	{ 0, 0, (const void*)&background_map, NULL, RightScroller_Create },
	{ 122, 88, (const void*)&ninja_girl, (u32)&ninja_girl_spriteVdpLocation, Player_Create },
	{ 150, 88, (const void*)&kunai, (u32)&kunai_spriteVdpLocation, Kunai_Create },
	{ 176, 88, (const void*)&kunai, (u32)&kunai_spriteVdpLocation, Kunai_Create },
	//{ 192, 88, (const void*)&kunai, (u32)&kunai_spriteVdpLocation, Kunai_Create },
	{ 8, 16, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 120, 38, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 220, 108, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 420, 128, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 470, 148, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 500, 168, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
};

const SpawnInfo level002BootStrapSpawnInfo =
{
	0, 
	0, 
	level002_spawns, 
	10, 
	StreamingSpawner_Create
};

const Level level002 =
{
	Level002_Init,
	globalPalette,
	globalPalette,
	&level002BootStrapSpawnInfo,
};