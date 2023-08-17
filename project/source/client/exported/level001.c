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

// resources
#include "client/exported/global_palette.h"
#include "client/exported/ninja_girl.h"
#include "client/exported/background.h"

u8 ninja_girl_spriteVdpLocation; // move this to a better place. with the animation ?

void Level001_Init(void)
{
	// load sprite resources
	ninja_girl_spriteVdpLocation = VDPTileManager_LoadAnimationTiles(&ninja_girl);
}

const SpawnInfo level001_spawns[] = 
{
	//{ 0, 0, NULL, NULL, SpawnManager_Create },
	{ 0, 0, (const void*)&background_map, (u8*)NULL, RightScroller_Create },
	{ 122, 88, (const void*)&ninja_girl, &ninja_girl_spriteVdpLocation, Player_Create }
};

//u16 level001_spawnsCount = sizeof(level001_spawns) / sizeof(level001_spawns[0]);

const Level level001 =
{
	Level001_Init,
	level001_spawns,
	2,
	globalPalette,
	globalPalette
};