#include "sceneMasterTemp.h"
#include "client\generated\gameobjecttemplates\gameobject_templates.h"
#include "client\generated\resource_infos.h"
#include "engine\object_manager.h"
#include "engine\resource_manager.h"
#include "engine\createinfo_types.h"
#include "engine\commandrunner_runall.h"

#include "engine\map_manager.h"
#include "client\objects\right_scroller.h"
#include "engine\commands\background_commands.h"
#include "engine\commands\set_palette_commands.h"

const CommandRunnerCreateInfo sceneMasterTemp_createInfoBootstrapper = { &commandrunner_runall_template, 0, 0, NULL };
const CommandRunnerCreateInfo sceneMasterTemp_createInfo3 = { &commandrunner_rightscroll_template, 0, 3, NULL };
const CreateInfo sceneMasterTemp_createInfo6 = { &gun_girl_template, 27, 16 };
const CreateInfo sceneMasterTemp_createInfo7 = { &robotrunner_template, 76, 144 };
const CreateInfo sceneMasterTemp_createInfo8 = { &colortweaker_template, 88, 7 };
const CreateInfo sceneMasterTemp_createInfo9 = { &robotrunner_template, 156, 112 };
const CreateInfo sceneMasterTemp_createInfo10 = { &walker_template, 248, 152 };
const CreateInfo sceneMasterTemp_createInfo11 = { &walker_template, 360, 40 };
const CreateInfo sceneMasterTemp_createInfo12 = { &robotrunner_template, 380, 80 };
const CreateInfo sceneMasterTemp_createInfo13 = { &walker_big_template, 464, 112 };
const CreateInfo sceneMasterTemp_createInfo14 = { &robotrunner_template, 620, 96 };

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
    { 0, (CommandFunction)ResourceManager_LoadResource, &gun_girlResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &explosionResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &impactResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &bulletResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotrunnerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &colorTweakerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &walkerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &walker_bigResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &field_mapResourceInfo},
    { 0, (CommandFunction)SetBackgroundVerticalScroll, 4 },
    { 0, (CommandFunction)SetBackgroundPalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)MapManager_SetTilesetProperties_Command, &setTilesetPropertiesParams  },
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&sceneMasterTemp_createInfo3 },
    { 0, (CommandFunction)SetSpritePalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)RightScroller_Init, &background3_mapResourceInfo },
    { 30, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo6 },
    { 85, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo7 },
    { 88, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo8 },
    { 165, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo9 },
    { 256, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo10 },
    { 368, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo11 },
    { 389, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo12 },
    { 480, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo13 },
    { 629, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo14 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene sceneMasterTemp = 
{
    sceneMasterTemp_commands,
};
