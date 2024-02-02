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
const CreateInfo sceneMasterTemp_createInfo5 = { &gun_girl_template, 129, 124 };
const CreateInfo sceneMasterTemp_createInfo6 = { &walker_template, 169, 57 };
const CreateInfo sceneMasterTemp_createInfo7 = { &robotrunner_template, 236, 128 };
const CreateInfo sceneMasterTemp_createInfo8 = { &walker_big_template, 301, 16 };
const CreateInfo sceneMasterTemp_createInfo9 = { &robotrunner_template, 478, 129 };
const CreateInfo sceneMasterTemp_createInfo10 = { &robotrunner_template, 510, 80 };

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
    { 0, (CommandFunction)ResourceManager_LoadResource, &gun_girlResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &explosionResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &impactResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &kunaiResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &walkerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotrunnerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &walker_bigResourceInfo },
    { 0, (CommandFunction)SetBackgroundPalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)MapManager_SetTilesetProperties_Command, &setTilesetPropertiesParams  },
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&sceneMasterTemp_createInfo2 },
    { 0, (CommandFunction)SetSpritePalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)RightScroller_Init, &background3_mapResourceInfo },
    { 109, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo5 },
    { 161, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo6 },
    { 224, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo7 },
    { 285, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo8 },
    { 466, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo9 },
    { 498, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo10 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene sceneMasterTemp = 
{
    sceneMasterTemp_commands,
};
