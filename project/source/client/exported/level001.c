#include "level001.h"

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
#include "client/objects/right_scroller.h"
#include "client/objects/everything_spawner.h"

// resources
#include "client/exported/global_palette.h"
#include "client/exported/ninja_girl.h"
#include "client/exported/background.h"

void Level001_Init(void)
{
	// load sprite resources
	ninja_girl_spriteVdpLocation = VDPTileManager_LoadAnimationTiles(&ninja_girl);
}

const SpawnInfo level001_spawns[] = 
{
	{ 0, 0, (const void*)&background_map, NULL, RightScroller_Create },
	{ 122, 88, (const void*)&ninja_girl, (u32)&ninja_girl_spriteVdpLocation, Player_Create }
};

const SpawnInfo level001BootStrapSpawnInfo =
{
	0, 
	0, 
	level001_spawns, 
	2, 
	EverythingSpawner_Create
};

const Level level001 =
{
	Level001_Init,
	globalPalette,
	globalPalette,
	&level001BootStrapSpawnInfo,
};