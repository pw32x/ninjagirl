#include "scene003.h"
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

const CommandRunnerCreateInfo scene003_createInfoBootstrapper = { &commandrunner_runall_template, 0, 0, NULL };
const CommandRunnerCreateInfo scene003_createInfo3 = { &commandrunner_rightscroll_template, 0, 3, NULL };
const CreateInfo scene003_createInfo6 = { &gun_girl_template, 48, 88 };
const CreateInfo scene003_createInfo7 = { &threeshotflyer_template, 80, 53 };
const CreateInfo scene003_createInfo8 = { &wheeler_template, 123, 98 };
const CreateInfo scene003_createInfo9 = { &wheeler_template, 162, 105 };

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
    { 0, (CommandFunction)ResourceManager_LoadResource, &gun_girlResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &explosionResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &impactResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &bulletResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &shotgunResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &threeshotflyerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &enemy_bulletResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &wheelerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &field_mapResourceInfo},
    { 0, (CommandFunction)SetBackgroundVerticalScroll, 4 },
    { 0, (CommandFunction)SetBackgroundPalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)MapManager_SetTilesetProperties_Command, &setTilesetPropertiesParams  },
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&scene003_createInfo3 },
    { 0, (CommandFunction)SetSpritePalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)RightScroller_Init, &field_mapResourceInfo },
    { 51, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo6 },
    { 92, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo7 },
    { 127, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo8 },
    { 166, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo9 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene scene003 = 
{
    scene003_commands,
};
