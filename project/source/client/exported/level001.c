#include "level001.h"

#include "SMSlib.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/vdptile_manager.h"
#include "engine/object_types.h"
#include "engine/animation_types.h"

// game objects
#include "client/objects/player.h"

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

const SpawnInfo level001_spawns[1] = 
{
	{ 122, 88, &ninja_girl, &ninja_girl_spriteVdpLocation, Player_Create }
};

const Level level001 =
{
	Level001_Init,
	level001_spawns,
	1, // spawns count
	globalPalette,
	globalPalette,
	&background_map
};