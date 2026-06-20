#include "sceneMasterTemp.h"
#include "client\generated\gameobjecttemplates\gameobject_templates.h"
#include "client\generated\resource_infos.h"
#include "engine\object_manager_create.h"
#include "engine\resource_manager.h"
#include "engine\createinfo_types.h"
#include "engine\commandrunner_runall.h"

#include "engine\map_manager.h"
#include "client\objects\right_scroller.h"
#include "engine\commands\background_commands.h"
#include "engine\commands\set_palette_commands.h"

const CommandRunnerCreateInfo sceneMasterTemp_createInfoBootstrapper = { &commandrunner_runall_template, 0, 0, NULL };
const CommandRunnerCreateInfo sceneMasterTemp_createInfo3 = { &commandrunner_rightscroll_template, 0, 3, NULL };
const CreateInfo sceneMasterTemp_createInfo6 = { &gun_girl_template, 48, 88 };
const CreateInfo sceneMasterTemp_createInfo7 = { &threeshotflyer_template, 80, 53 };
const CreateInfo sceneMasterTemp_createInfo8 = { &wheeler_template, 380, 30 };
const CreateInfo sceneMasterTemp_createInfo9 = { &wheeler_template, 404, 77 };

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
    { 0, (CommandFunction)ResourceManager_LoadResource, &shotgun_bulletResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &threeshotflyerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &enemy_bulletResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &wheelerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &field_mapResourceInfo},
    { 0, (CommandFunction)SetBackgroundVerticalScroll, 4 },
    { 0, (CommandFunction)SetBackgroundPalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)MapManager_SetTilesetProperties_Command, &setTilesetPropertiesParams  },
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&sceneMasterTemp_createInfo3 },
    { 0, (CommandFunction)SetSpritePalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)RightScroller_Init, &field_mapResourceInfo },
    { 51, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo6 },
    { 92, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo7 },
    { 384, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo8 },
    { 408, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo9 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene sceneMasterTemp = 
{
    sceneMasterTemp_commands,
};
