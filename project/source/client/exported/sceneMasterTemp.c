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
const CreateInfo sceneMasterTemp_createInfo6 = { &threeshotflyer_template, 944/*59*/, 752/*47/*/ };
const CreateInfo sceneMasterTemp_createInfo7 = { &gun_girl_template, 1856/*116*/, 1712/*107/*/ };
const CreateInfo sceneMasterTemp_createInfo8 = { &threeshotflyer_template, 1776/*111*/, 352/*22/*/ };
const CreateInfo sceneMasterTemp_createInfo9 = { &threeshotflyer_template, 2608/*163*/, 1456/*91/*/ };
const CreateInfo sceneMasterTemp_createInfo10 = { &threeshotflyer_template, 4624/*289*/, 1168/*73/*/ };
const CreateInfo sceneMasterTemp_createInfo11 = { &wheeler_template, 5648/*353*/, 576/*36/*/ };
const CreateInfo sceneMasterTemp_createInfo12 = { &wheeler_template, 5936/*371*/, 2272/*142/*/ };
const CreateInfo sceneMasterTemp_createInfo13 = { &deliveryrobot_template, 6688/*418*/, 1216/*76/*/ };
const CreateInfo sceneMasterTemp_createInfo14 = { &wheeler_template, 7664/*479*/, 1712/*107/*/ };

#include "client/tileset_functions.h"
static const SetTilesetProperties_Params setTilesetPropertiesParams = 
{ 
 1, 
 breakable_rock_tileset_TilesetFunction, 
 &rock_particle_template
};

const Command sceneMasterTemp_commands[] = 
{
    { 0, (CommandFunction)ObjectManager_CreateCommandRunner, &sceneMasterTemp_createInfoBootstrapper },
    { 0, (CommandFunction)ResourceManager_LoadResource, &threeshotflyer_animResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &enemy_bullet_animResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &gun_girl_animResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &explosion_animResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &impact_animResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &bullet_animResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &shotgun_bullet_animResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &wheeler_animResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &deliveryrobot_animResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &shotgun_item_animResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &field_mapResourceInfo},
    { 0, (CommandFunction)SetBackgroundVerticalScroll, 4 },
    { 0, (CommandFunction)SetBackgroundPalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)MapManager_SetTilesetProperties_Command, &setTilesetPropertiesParams },
    { 0, (CommandFunction)ObjectManager_CreateCommandRunner, &sceneMasterTemp_createInfo3 },
    { 0, (CommandFunction)SetSpritePalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)RightScroller_Init, &field_mapResourceInfo },
    { 71, (CommandFunction)ObjectManager_CreateEnemy, &sceneMasterTemp_createInfo6 },
    { 119, (CommandFunction)ObjectManager_CreatePlayer, &sceneMasterTemp_createInfo7 },
    { 123, (CommandFunction)ObjectManager_CreateEnemy, &sceneMasterTemp_createInfo8 },
    { 175, (CommandFunction)ObjectManager_CreateEnemy, &sceneMasterTemp_createInfo9 },
    { 301, (CommandFunction)ObjectManager_CreateEnemy, &sceneMasterTemp_createInfo10 },
    { 357, (CommandFunction)ObjectManager_CreateEnemy, &sceneMasterTemp_createInfo11 },
    { 375, (CommandFunction)ObjectManager_CreateEnemy, &sceneMasterTemp_createInfo12 },
    { 430, (CommandFunction)ObjectManager_CreateEnemy, &sceneMasterTemp_createInfo13 },
    { 483, (CommandFunction)ObjectManager_CreateEnemy, &sceneMasterTemp_createInfo14 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene sceneMasterTemp = 
{
    sceneMasterTemp_commands,
};
