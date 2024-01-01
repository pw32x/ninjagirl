#include "scene001.h"

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

#include "engine/commandrunner_runall.h"

/*
#include "engine/resource_manager.h"
#include "engine/command_types.h"
#include "client/generated/resource_infos.h"
#include "client/generated/gameobjecttemplates/gameobject_templates.h"
#include "engine\createinfo_types.h"


#include "client/objects/commandrunner_rightscroll.h"
#include "client/objects/player.h"
#include "client/objects/kunai.h"
#include "client/objects/enemy.h"
#include "client/objects/right_scroller.h"
//#include "client/objects/bird.h"
#include "client/objects/tile_animator.h"
*/


// game objects
#include "client/objects/commandrunner_rightscroll.h"
#include "client/objects/right_scroller.h"

#include "client/tileset_functions.h"

// resources
#include "client/exported/global_palette.h"
#include "client/generated/resource_infos.h"
#include "client/generated/gameobjecttemplates/gameobject_templates.h"

// generated
#include "client/generated/bank2.h" // music

//const CreateInfo scene001_createInfo003 = { 122, 110, (const void*)&ninja_girlResourceInfo };
//const CreateInfo scene001_createInfo004 = { 64, 128, (const void*)&walkerResourceInfo };
//const CreateInfo scene001_createInfo005 = { 144, 32, (const void*)&walker_bigResourceInfo };
//const CreateInfo scene001_createInfo006 = { 96, 88, (const void*)&walker_smallResourceInfo  };
//const CreateInfo scene001_createInfo007 = { 180, 32, (const void*)&robotrunnerResourceInfo };
//const CreateInfo scene001_createInfo008 = { 128, 8, (const void*)&robotspringResourceInfo };

const CommandRunnerCreateInfo scene001_createInfoBootstrapper = { &commandrunner_runall_template, 0, 0, NULL };
const CreateInfo scene001_createInfo002 = { &commandrunner_rightscroll_template, 122, 110 };
const CreateInfo scene001_createInfo003 = { &ninja_girl_template, 122, 110 };
const CreateInfo scene001_createInfo004 = { &walker_template, 64, 128 };
const CreateInfo scene001_createInfo005 = { &walker_big_template, 144, 32 };
const CreateInfo scene001_createInfo006 = { &walker_small_template, 96, 88 };
const CreateInfo scene001_createInfo007 = { &robotrunner_template, 180, 32 };
const CreateInfo scene001_createInfo008 = { &robotspring_template , 128, 8 };


//const CreateInfo scene001_createInfo009 = { 234, 112, (const void*)&evil_eye };
//const CreateInfo scene001_createInfo010 = { 234, 144, (const void*)&evil_eye };
//const CreateInfo scene001_createInfo011 = { 234, 176, (const void*)&evil_eye };
//const CreateInfo scene001_createInfo012 = { 254, 102, (const void*)&birdidle };

const SetTilesetProperties_Params setTilesetPropertiesParams = 
{ 
	1, 
	breakable_rock_tileset_TilesetFunction, 
	&rock_particle_template
};

Command scene001_commands[] = 
{
	
	{ 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene001_createInfoBootstrapper },
	//{ 0, (CommandFunction)PSGPlay, song_psg },
	{ 0, (CommandFunction)SMS_loadBGPalette, globalPalette },
	{ 0, (CommandFunction)SMS_loadSpritePalette, globalPalette },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &background3_mapResourceInfo },
	{ 0, (CommandFunction)MapManager_SetTilesetProperties_Command, &setTilesetPropertiesParams },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &ninja_girlResourceInfo },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &kunaiResourceInfo },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &impactResourceInfo },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &explosionResourceInfo },

	{ 0, (CommandFunction)ResourceManager_LoadResource, &robotrunnerResourceInfo },
	//{ 0, (CommandFunction)ResourceManager_LoadResource, &robotcannonResourceInfo },	
	//{ 0, (CommandFunction)ResourceManager_LoadResource, &robotflyingResourceInfo },	
	{ 0, (CommandFunction)ResourceManager_LoadResource, &robotspringResourceInfo },			
	{ 0, (CommandFunction)ResourceManager_LoadResource, &walkerResourceInfo },			
	//{ 0, (CommandFunction)ResourceManager_LoadResource, &walker_bigResourceInfo },			
	{ 0, (CommandFunction)ResourceManager_LoadResource, &walker_smallResourceInfo },			
	//{ 0, (CommandFunction)ResourceManager_LoadResource, &birdidle },
		{ 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene001_createInfo002 },
	{ 0, (CommandFunction)RightScroller_Init, &background3_mapResourceInfo },
	{ 24, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene001_createInfo004 },
	//{ 24, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene001_createInfo005 },
	{ 122, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene001_createInfo003 }, 
	
	
	{ 24, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene001_createInfo006 },
	{ 64, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene001_createInfo007 },
	{ 128, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene001_createInfo008 },
	//{ 234, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene001_createInfo009 },
	//{ 234, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene001_createInfo010 },
	//{ 234, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene001_createInfo011 },
	//{ 654, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene001_createInfo012 },
	{ 0, (CommandFunction)NULL, NULL}
};

const Scene scene001 =
{
	scene001_commands
};