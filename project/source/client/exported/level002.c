#include "level002.h"

#include "SMSlib.h"
#include "PSGlib.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/vdptile_manager.h"
#include "engine/object_types.h"
#include "engine/animation_types.h"
#include "engine/resource_manager.h"
#include "engine/command_types.h"

// game objects
#include "client/objects/command_runner.h"
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
#include "client/generated/bank2.h" // music

const CreateInfo level002_createInfo003 = { 122, 88, (const void*)&ninja_girl };
const CreateInfo level002_createInfo004 = { 24, 16, (const void*)&evil_eye };
const CreateInfo level002_createInfo005 = { 24, 48, (const void*)&evil_eye };
const CreateInfo level002_createInfo006 = { 24, 80, (const void*)&evil_eye };
const CreateInfo level002_createInfo007 = { 142, 8, (const void*)&birdidle };
const CreateInfo level002_createInfo008 = { 176, 8, (const void*)&birdidle };
const CreateInfo level002_createInfo009 = { 354, 112, (const void*)&evil_eye };
const CreateInfo level002_createInfo010 = { 454, 144, (const void*)&evil_eye };
const CreateInfo level002_createInfo011 = { 554, 176, (const void*)&evil_eye };
const CreateInfo level002_createInfo012 = { 654, 102, (const void*)&birdidle };

Command level002_commands[] = 
{
	{ 0, (CommandFunction)CommandRunner_Create, NULL },
	{ 0, (CommandFunction)PSGPlay, song_psg },
	{ 0, (CommandFunction)SMS_loadBGPalette, globalPalette },
	{ 0, (CommandFunction)SMS_loadSpritePalette, globalPalette },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &background_map },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &ninja_girl },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &kunai },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &evil_eye },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &birdidle },
	{ 0, (CommandFunction)ResourceManager_LoadResource, &water_tiles },
	{ 0, (CommandFunction)RightScroller_Create, &background_map },
	{ 0, (CommandFunction)TileAnimator_Create, &water_tiles },
	{ 122, (CommandFunction)Player_Create, &level002_createInfo003 }, 
	{ 24, (CommandFunction)Enemy_Create, &level002_createInfo004 },
	{ 24, (CommandFunction)Enemy_Create, &level002_createInfo005 },
	{ 24, (CommandFunction)Enemy_Create, &level002_createInfo006 },
	{ 142, (CommandFunction)Bird_Create, &level002_createInfo007 },
	{ 176, (CommandFunction)Bird_Create, &level002_createInfo008 },
	{ 354, (CommandFunction)Enemy_Create, &level002_createInfo009 },
	{ 454, (CommandFunction)Enemy_Create, &level002_createInfo010 },
	{ 554, (CommandFunction)Enemy_Create, &level002_createInfo011 },
	{ 654, (CommandFunction)Bird_Create, &level002_createInfo012 },
	{ 0, NO_DATA, NO_DATA}
};

const Level level002 =
{
	level002_commands
};