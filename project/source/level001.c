#include "level001.h"

#include "SMSlib.h"
#include "object_manager.h"
#include "scroll_manager.h"
#include "vdptile_manager.h"
#include "object_types.h"
#include "animation_types.h"

// game objects
#include "player.h"

// resources
#include "global_palette.h"
#include "ninja_girl.h"
#include "background.h"
#include "background_tileset.h"

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