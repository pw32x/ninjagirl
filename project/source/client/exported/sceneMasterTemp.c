#include "sceneMasterTemp.h"
#include "client\generated\gameobjecttemplates\gameobject_templates.h"
#include "client\generated\resource_infos.h"
#include "engine\object_manager.h"
#include "engine\resource_manager.h"
#include "engine\createinfo_types.h"
#include "engine\commandrunner_runall.h"

#include "engine\map_manager.h"
#include "client\objects\right_scroller.h"
#include "engine\commands\set_palette_commands.h"

const CommandRunnerCreateInfo sceneMasterTemp_createInfoBootstrapper = { &commandrunner_runall_template, 0, 0, NULL };
const CommandRunnerCreateInfo sceneMasterTemp_createInfo2 = { &commandrunner_rightscroll_template, 0, 3, NULL };
const CreateInfo sceneMasterTemp_createInfo5 = { &ninja_girl_template, 17, 0 };
const CreateInfo sceneMasterTemp_createInfo6 = { &walker_small_template, 56, 130 };
const CreateInfo sceneMasterTemp_createInfo7 = { &walker_template, 80, 73 };
const CreateInfo sceneMasterTemp_createInfo8 = { &robotspring_template, 137, 20 };
const CreateInfo sceneMasterTemp_createInfo9 = { &walker_small_template, 161, 56 };
const CreateInfo sceneMasterTemp_createInfo10 = { &walker_template, 164, 140 };
const CreateInfo sceneMasterTemp_createInfo11 = { &walker_small_template, 165, 118 };
const CreateInfo sceneMasterTemp_createInfo12 = { &walker_template, 166, 171 };
const CreateInfo sceneMasterTemp_createInfo13 = { &robotrunner_template, 182, 30 };

#include "client/tileset_functions.h"
const SetTilesetProperties_Params setTilesetPropertiesParams = 
{ 
 1, 
 breakable_rock_tileset_TilesetFunction, 
 &rock_particle_template
};

const Command sceneMasterTemp_commands[] = 
{
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&sceneMasterTemp_createInfoBootstrapper },
    { 0, (CommandFunction)ResourceManager_LoadResource, &background3_mapResourceInfo},
    { 0, (CommandFunction)ResourceManager_LoadResource, &ninja_girlResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &explosionResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &impactResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &kunaiResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &walker_smallResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &walkerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotspringResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotrunnerResourceInfo },
    { 0, (CommandFunction)SetBackgroundPalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)MapManager_SetTilesetProperties_Command, &setTilesetPropertiesParams  },
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&sceneMasterTemp_createInfo2 },
    { 0, (CommandFunction)SetSpritePalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)RightScroller_Init, &background3_mapResourceInfo },
    { 17, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo5 },
    { 56, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo6 },
    { 80, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo7 },
    { 137, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo8 },
    { 161, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo9 },
    { 164, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo10 },
    { 165, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo11 },
    { 166, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo12 },
    { 182, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo13 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene sceneMasterTemp = 
{
    sceneMasterTemp_commands,
};
