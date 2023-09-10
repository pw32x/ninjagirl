#include "level002.h"

#include "SMSlib.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/vdptile_manager.h"
#include "engine/object_types.h"
#include "engine/animation_types.h"
#include "engine/resource_manager.h"

// exported
#include "client/generated/sprite_vdp_locations.h"

// game objects
#include "client/objects/player.h"
#include "client/objects/kunai.h"
#include "client/objects/enemy.h"
#include "client/objects/right_scroller.h"
#include "client/objects/streaming_spawner.h"
#include "client/objects/bird.h"
#include "client/objects/tile_animator.h"

// resources
#include "client/exported/global_palette.h"
#include "client/exported/ninja_girl.h"
#include "client/exported/kunai.h"
#include "client/exported/evil_eye.h"
#include "client/exported/birdidle.h"
#include "client/exported/background.h"
#include "client/exported/water_tiles.h"

void Level002_Init(void)
{
	// load sprite resources
	ninja_girl_spriteVdpLocation = (u8)ResourceManager_LoadResource(&ninja_girl);
	kunai_spriteVdpLocation = (u8)ResourceManager_LoadResource(&kunai);	
	evil_eye_spriteVdpLocation = (u8)ResourceManager_LoadResource(&evil_eye);
	//birdidle_spriteVdpLocation = (u8)ResourceManager_LoadResource(&birdidle);
	//water_tiles_spriteVdpLocation = (u8)ResourceManager_LoadResource(&water_tiles);
}

const SpawnInfo level002_spawns[] = 
{
	{ 0, 0, (const void*)&background_map, NULL, RightScroller_Create },
	{ 0, 0, (const void*)&water_tiles, (u32)&water_tiles_spriteVdpLocation, TileAnimator_Create },
	{ 122, 88, (const void*)&ninja_girl, (u32)&ninja_girl_spriteVdpLocation, Player_Create },
	{ 24, 16, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 24, 48, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 24, 80, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	//{ 142, 8, (const void*)&birdidle, (u32)&birdidle_spriteVdpLocation, Bird_Create },
	//{ 176, 8, (const void*)&birdidle, (u32)&birdidle_spriteVdpLocation, Bird_Create },
	{ 254, 112, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 254, 144, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	{ 254, 176, (const void*)&evil_eye, (u32)&evil_eye_spriteVdpLocation, Enemy_Create },
	//{ 254, 102, (const void*)&birdidle, (u32)&birdidle_spriteVdpLocation, Bird_Create },
};

const SpawnInfo level002BootStrapSpawnInfo =
{
	0, 
	0, 
	level002_spawns, 
	9, 
	StreamingSpawner_Create
};

const Level level002 =
{
	Level002_Init,
	globalPalette,
	globalPalette,
	&level002BootStrapSpawnInfo,
};