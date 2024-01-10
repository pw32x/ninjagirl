#include "scene003.h"
#include "client\generated\gameobjecttemplates\gameobject_templates.h"
#include "client\generated\resource_infos.h"
#include "engine\object_manager.h"
#include "engine\resource_manager.h"
#include "engine\createinfo_types.h"
#include "engine\commandrunner_runall.h"

#include "engine\map_manager.h"
#include "client\objects\right_scroller.h"
#include "engine\commands\set_palette_commands.h"

const CommandRunnerCreateInfo scene003_createInfoBootstrapper = { &commandrunner_runall_template, 0, 0, NULL };
const CommandRunnerCreateInfo scene003_createInfo2 = { &commandrunner_rightscroll_template, 0, 3, NULL };
const CreateInfo scene003_createInfo5 = { &walker_small_template, 56, 130 };
const CreateInfo scene003_createInfo6 = { &ninja_girl_template, 61, 15 };
const CreateInfo scene003_createInfo7 = { &robotspring_template, 137, 20 };
const CreateInfo scene003_createInfo8 = { &walker_template, 159, 85 };
const CreateInfo scene003_createInfo9 = { &walker_small_template, 161, 56 };
const CreateInfo scene003_createInfo10 = { &walker_template, 164, 140 };
const CreateInfo scene003_createInfo11 = { &walker_small_template, 165, 118 };
const CreateInfo scene003_createInfo12 = { &walker_template, 166, 171 };
const CreateInfo scene003_createInfo13 = { &robotrunner_template, 182, 30 };

#include "client/tileset_functions.h"
const SetTilesetProperties_Params setTilesetPropertiesParams = 
{ 
 1, 
 breakable_rock_tileset_TilesetFunction, 
 &rock_particle_template
};

const Command scene003_commands[] = 
{
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&scene003_createInfoBootstrapper },
    { 0, (CommandFunction)ResourceManager_LoadResource, &background3_mapResourceInfo},
    { 0, (CommandFunction)ResourceManager_LoadResource, &walker_smallResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &ninja_girlResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &explosionResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &impactResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &kunaiResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotspringResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &walkerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotrunnerResourceInfo },
    { 0, (CommandFunction)SetBackgroundPalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)MapManager_SetTilesetProperties_Command, &setTilesetPropertiesParams  },
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&scene003_createInfo2 },
    { 0, (CommandFunction)SetSpritePalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)RightScroller_Init, &background3_mapResourceInfo },
    { 56, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo5 },
    { 61, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo6 },
    { 137, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo7 },
    { 159, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo8 },
    { 161, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo9 },
    { 164, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo10 },
    { 165, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo11 },
    { 166, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo12 },
    { 182, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo13 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene scene003 = 
{
    scene003_commands,
};
