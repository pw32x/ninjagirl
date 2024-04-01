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
const CreateInfo sceneMasterTemp_createInfo6 = { &gun_girl_template, 63, 117 };
const CreateInfo sceneMasterTemp_createInfo7 = { &threeshotflyer_template, 139, 132 };
const CreateInfo sceneMasterTemp_createInfo8 = { &threeshotflyer_template, 177, 132 };
const CreateInfo sceneMasterTemp_createInfo9 = { &wheeler_template, 35, 145 };
const CreateInfo sceneMasterTemp_createInfo10 = { &wheeler_template, 321, 145 };
const CreateInfo sceneMasterTemp_createInfo11 = { &deliveryrobot_template, 343, 23 };
const CreateInfo sceneMasterTemp_createInfo12 = { &wheeler_template, 383, 96 };
const CreateInfo sceneMasterTemp_createInfo13 = { &wheeler_template, 412, 143 };
const CreateInfo sceneMasterTemp_createInfo14 = { &wheeler_template, 464, 96 };
const CreateInfo sceneMasterTemp_createInfo15 = { &wheeler_template, 498, 142 };
const CreateInfo sceneMasterTemp_createInfo16 = { &deliveryrobot_template, 537, 34 };
const CreateInfo sceneMasterTemp_createInfo17 = { &wheeler_template, 601, 145 };
const CreateInfo sceneMasterTemp_createInfo18 = { &wheeler_template, 643, 72 };
const CreateInfo sceneMasterTemp_createInfo19 = { &wheeler_template, 717, 144 };
const CreateInfo sceneMasterTemp_createInfo20 = { &wheeler_template, 748, 97 };
const CreateInfo sceneMasterTemp_createInfo21 = { &wheeler_template, 812, 55 };
const CreateInfo sceneMasterTemp_createInfo22 = { &wheeler_template, 943, 146 };

#include "client/tileset_functions.h"
const SetTilesetProperties_Params setTilesetPropertiesParams2 = 
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
    { 0, (CommandFunction)ResourceManager_LoadResource, &shotgunResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &threeshotflyerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &enemy_bulletResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &wheelerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &deliveryrobotResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &shotgun_itemResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &field_mapResourceInfo},
    { 0, (CommandFunction)SetBackgroundVerticalScroll, 4 },
    { 0, (CommandFunction)SetBackgroundPalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)MapManager_SetTilesetProperties_Command, &setTilesetPropertiesParams2  },
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&sceneMasterTemp_createInfo3 },
    { 0, (CommandFunction)SetSpritePalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)RightScroller_Init, &field_mapResourceInfo },
    { 66, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo6 },
    { 151, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo7 },
    { 189, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo8 },
    { 264, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo9 },
    { 325, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo10 },
    { 355, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo11 },
    { 387, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo12 },
    { 416, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo13 },
    { 468, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo14 },
    { 502, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo15 },
    { 549, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo16 },
    { 605, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo17 },
    { 647, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo18 },
    { 721, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo19 },
    { 752, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo20 },
    { 816, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo21 },
    { 947, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &sceneMasterTemp_createInfo22 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene sceneMasterTemp = 
{
    sceneMasterTemp_commands,
};
