#include "scene002.h"
#include "client\generated\gameobjecttemplates\gameobject_templates.h"
#include "engine\object_manager.h"
#include "engine\resource_manager.h"
#include "client\generated\resource_infos.h"
#include "engine\createinfo_types.h"

const CommandRunnerCreateInfo scene002_createInfo0 = { &commandrunner_rightscroll_template, 0, 4, NULL };
const CreateInfo scene002_createInfo1 = { &walker_template, 59, 75 };
const CreateInfo scene002_createInfo2 = { &robotrunner_template, 64, 126 };
const CreateInfo scene002_createInfo3 = { &ninja_girl_template, 68, 18 };
const CreateInfo scene002_createInfo4 = { &walker_template, 98, 75 };
const CreateInfo scene002_createInfo5 = { &robotrunner_template, 119, 120 };
const CreateInfo scene002_createInfo6 = { &walker_small_template, 142, 22 };
const CreateInfo scene002_createInfo7 = { &robotspring_template, 143, 30 };
const CreateInfo scene002_createInfo8 = { &walker_small_template, 171, 16 };
const CreateInfo scene002_createInfo9 = { &robotrunner_template, 179, 27 };
const CreateInfo scene002_createInfo10 = { &walker_small_template, 209, 14 };
const CreateInfo scene002_createInfo11 = { &walker_small_template, 246, 11 };
const CreateInfo scene002_createInfo12 = { &robotrunner_template, 287, 1 };

const Command scene002_commands[] = 
{
    { 0, (CommandFunction)ResourceManager_LoadResource, &walkerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotrunnerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &ninja_girlResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &walker_smallResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotspringResourceInfo },
    { 0, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, (const CreateInfo*)&scene002_createInfo0 },
    { 59, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo1 },
    { 64, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo2 },
    { 68, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo3 },
    { 98, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo4 },
    { 119, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo5 },
    { 142, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo6 },
    { 143, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo7 },
    { 171, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo8 },
    { 179, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo9 },
    { 209, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo10 },
    { 246, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo11 },
    { 287, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo12 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene scene002 = 
{
    scene002_commands,
};
