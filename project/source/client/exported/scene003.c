#include "scene003.h"
#include "client\generated\gameobjecttemplates\gameobject_templates.h"
#include "client\generated\resource_infos.h"
#include "engine\object_manager.h"
#include "engine\resource_manager.h"
#include "engine\createinfo_types.h"
#include "engine\commandrunner_runall.h"

#include "client\objects\right_scroller.h"
#include "engine\commands\set_palette_commands.h"

const CommandRunnerCreateInfo scene003_createInfoBootstrapper = { &commandrunner_runall_template, 0, 0, NULL };
const CommandRunnerCreateInfo scene003_createInfo1 = { &commandrunner_rightscroll_template, 0, 3, NULL };
const CreateInfo scene003_createInfo4 = { &walker_small_template, 56, 130 };
const CreateInfo scene003_createInfo5 = { &walker_template, 58, 68 };
const CreateInfo scene003_createInfo6 = { &ninja_girl_template, 61, 15 };
const CreateInfo scene003_createInfo7 = { &walker_small_template, 90, 81 };
const CreateInfo scene003_createInfo8 = { &walker_template, 102, 126 };
const CreateInfo scene003_createInfo9 = { &walker_small_template, 116, 72 };
const CreateInfo scene003_createInfo10 = { &walker_template, 128, 119 };
const CreateInfo scene003_createInfo11 = { &robotspring_template, 137, 20 };
const CreateInfo scene003_createInfo12 = { &robotrunner_template, 182, 30 };

const Command scene003_commands[] = 
{
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&scene003_createInfoBootstrapper },
    { 0, (CommandFunction)ResourceManager_LoadResource, &background3_mapResourceInfo},
    { 0, (CommandFunction)ResourceManager_LoadResource, &walker_smallResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &walkerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &ninja_girlResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotspringResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotrunnerResourceInfo },
    { 0, (CommandFunction)SetBackgroundPalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&scene003_createInfo1 },
    { 0, (CommandFunction)SetSpritePalette, &globalPaletteResourceInfo },
    { 0, (CommandFunction)RightScroller_Init, &background3_mapResourceInfo },
    { 56, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo4 },
    { 58, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo5 },
    { 61, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo6 },
    { 90, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo7 },
    { 102, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo8 },
    { 116, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo9 },
    { 128, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo10 },
    { 137, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo11 },
    { 182, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene003_createInfo12 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene scene003 = 
{
    scene003_commands,
};
