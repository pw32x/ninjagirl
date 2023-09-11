#include "level001.h"

#include "SMSlib.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/vdptile_manager.h"
#include "engine/object_types.h"
#include "engine/animation_types.h"


// game objects
#include "client/objects/player.h"
#include "client/objects/right_scroller.h"
#include "client/objects/commandrunner_runall.h"

// resources
#include "client/exported/global_palette.h"
#include "client/exported/ninja_girl.h"
#include "client/exported/background.h"
/*

void Level001_Init(void)
{
	// load sprite resources
	VDPTileManager_LoadSpriteTiles(ninja_girl.tileData, 
								   ninja_girl.totalTileCount,
								   ninja_girl.vdpLocation);
}

const SpawnInfo level001_spawns[] = 
{
	{ 0, 0, (const void*)&background_map, NULL, RightScroller_Create },
	{ 122, 88, (const void*)&ninja_girl, NULL, Player_Create }
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
*/