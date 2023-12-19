#include "level002.h"

#include "SMSlib.h"
#include "PSGlib.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/map_manager.h"
#include "engine/vdptile_manager.h"
#include "engine/object_types.h"
#include "engine/animation_types.h"
#include "engine/resource_manager.h"
#include "engine/command_types.h"

// game objects
#include "client/objects/commandrunner_rightscroll.h"
#include "client/objects/player.h"
#include "client/objects/kunai.h"
#include "client/objects/enemy.h"
#include "client/objects/right_scroller.h"
//#include "client/objects/bird.h"
#include "client/objects/tile_animator.h"

#include "client/tileset_functions.h"

// resources
#include "client/exported/global_palette.h"
#include "client/generated/resource_infos.h"
//#include "client/exported/animations/ninja_girl.h"
//#include "client/exported/animations/kunai.h"
//#include "client/exported/evil_eye.h"
//#include "client/exported/birdidle.h"
//#include "client/exported/maps/background3.h"
//#include "client/exported/animations/explosion.h"
//#include "client/exported/animations/impact.h"
//#include "client/exported/animations/rock_particle.h"

// generated
#include "client/generated/bank2.h" // music

const CreateInfo level002_createInfo003 = { 122, 110, (const void*)&ninja_girlResourceInfo };
const CreateInfo level002_createInfo004 = { 64, 128, (const void*)&walkerResourceInfo };
const CreateInfo level002_createInfo005 = { 144, 32, (const void*)&walker_bigResourceInfo };
const CreateInfo level002_createInfo006 = { 96, 88, (const void*)&walker_smallResourceInfo  };
const CreateInfo level002_createInfo007 = { 180, 32, (const void*)&robotrunnerResourceInfo };
const CreateInfo level002_createInfo008 = { 128, 8, (const void*)&robotspringResourceInfo };
//const CreateInfo level002_createInfo009 = { 234, 112, (const void*)&evil_eye };
//const CreateInfo level002_createInfo010 = { 234, 144, (const void*)&evil_eye };
//const CreateInfo level002_createInfo011 = { 234, 176, (const void*)&evil_eye };
//const CreateInfo level002_createInfo012 = { 254, 102, (const void*)&birdidle };

const SetTilesetProperties_Params setTilesetPropertiesParams = 
{ 
	1, 
	breakable_rock_tileset_TilesetFunction, 
	&rock_particleResourceInfo 
};

Command level002_commands[] = 
{
	{ 0, (CommandFunction)CommandRunner_RightScroll_Create, NULL },
	//{ 0, (CommandFunction)PSGPlay, song_psg },
	{ 0, (CommandFunction)SMS_loadBGPalette, globalPalette },
	{ 0, (CommandFunction)SMS_loadSpritePalette, globalPalette },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &background3_mapResourceInfo },
	//z{ 0, (CommandFunction)MapManager_SetTilesetProperties_Command, &setTilesetPropertiesParams },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &ninja_girlResourceInfo },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &kunaiResourceInfo },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &robotrunnerResourceInfo },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &explosionResourceInfo },
	//{ 0, (CommandFunction)ResourceManager_LoadResource, &robotcannonResourceInfo },	
	//{ 0, (CommandFunction)ResourceManager_LoadResource, &robotflyingResourceInfo },	
	{ 0, (CommandFunction)ResourceManager_LoadResource, &robotspringResourceInfo },			
	{ 0, (CommandFunction)ResourceManager_LoadResource, &walkerResourceInfo },			
	{ 0, (CommandFunction)ResourceManager_LoadResource, &walker_bigResourceInfo },			
	{ 0, (CommandFunction)ResourceManager_LoadResource, &walker_smallResourceInfo },			
	//{ 0, (CommandFunction)ResourceManager_LoadResource, &birdidle },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &impactResourceInfo },
	{ 0, (CommandFunction)RightScroller_Create, &background3_mapResourceInfo },
	{ 24, (CommandFunction)Enemy_Create, &level002_createInfo004 },
	{ 24, (CommandFunction)Enemy_Create, &level002_createInfo005 },
	{ 122, (CommandFunction)Player_Create, &level002_createInfo003 }, 
	
	
	{ 24, (CommandFunction)Enemy_Create, &level002_createInfo006 },
	{ 64, (CommandFunction)Enemy_Create, &level002_createInfo007 },
	{ 128, (CommandFunction)Enemy_Create, &level002_createInfo008 },
	//{ 234, (CommandFunction)Enemy_Create, &level002_createInfo009 },
	//{ 234, (CommandFunction)Enemy_Create, &level002_createInfo010 },
	//{ 234, (CommandFunction)Enemy_Create, &level002_createInfo011 },
	//{ 654, (CommandFunction)Bird_Create, &level002_createInfo012 },
	{ 0, (CommandFunction)NULL, NULL}
};

const Level level002 =
{
	level002_commands
};