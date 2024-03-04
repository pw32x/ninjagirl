#include "scene003.h"
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

const CommandRunnerCreateInfo scene003_createInfoBootstrapper = { &commandrunner_runall_template, 0, 0, NULL };
const CommandRunnerCreateInfo scene003_createInfo3 = { &commandrunner_rightscroll_template, 0, 3, NULL };
const CreateInfo scene003_createInfo6 = { &gun_girl_template, 63, 117 };
const CreateInfo scene003_createInfo7 = { &threeshotflyer_template, 151, 38 };
const CreateInfo scene003_createInfo8 = { &deliveryrobot_template, 206, 89 };
const CreateInfo scene003_createInfo9 = { &wheeler_template, 35, 145 };
const CreateInfo scene003_createInfo10 = { &wheeler_template, 321, 145 };
const CreateInfo scene003_createInfo11 = { &wheeler_template, 383, 96 };
const CreateInfo scene003_createInfo12 = { &wheeler_template, 412, 143 };
const CreateInfo scene003_createInfo13 = { &wheeler_template, 464, 96 };
const CreateInfo scene003_createInfo14 = { &wheeler_template, 498, 142 };
const CreateInfo scene003_createInfo15 = { &deliveryrobot_template, 537, 34 };
const CreateInfo scene003_createInfo16 = { &wheeler_template, 601, 145 };
const CreateInfo scene003_createInfo17 = { &wheeler_template, 643, 72 };
const CreateInfo scene003_createInfo18 = { &wheeler_template, 717, 144 };
const CreateInfo scene003_createInfo19 = { &wheeler_template, 748, 97 };
const CreateInfo scene003_createInfo20 = { &wheeler_template, 812, 55 };
const CreateInfo scene003_createInfo21 = { &wheeler_template, 943, 146 };

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
    { 0, (CommandFunction)ResourceManager_LoadResource, &deliveryrobotResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &shotgun_itemResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &wheelerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &level_001_mapResourceInfo},
    { 0, (CommandFunction)SetBackgroundVerticalScroll, 4 },
    { 0, (CommandFunction)SetBackgroundPalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)MapManager_SetTilesetProperties_Command, &setTilesetPropertiesParams  },
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&scene003_createInfo3 },
    { 0, (CommandFunction)SetSpritePalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)RightScroller_Init, &background3_mapResourceInfo },
    { 66, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo6 },
    { 163, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo7 },
    { 218, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo8 },
    { 264, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo9 },
    { 325, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo10 },
    { 387, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo11 },
    { 416, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo12 },
    { 468, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo13 },
    { 502, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo14 },
    { 549, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo15 },
    { 605, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo16 },
    { 647, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo17 },
    { 721, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo18 },
    { 752, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo19 },
    { 816, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo20 },
    { 947, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo21 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene scene003 = 
{
    scene003_commands,
};
