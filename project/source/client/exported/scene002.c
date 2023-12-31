#include "scene002.h"
#include "client\generated\gameobjecttemplates\gameobject_templates.h"
#include "engine\object_manager.h"
#include "engine\resource_manager.h"
#include "client\generated\resource_infos.h"
#include "engine\createinfo_types.h"

#include "engine/command_types.h"
void CommandRunner_RightScroll_Init(const Command* commands);
const CreateInfo scene002_createInfo0 = { &walker_template, 59, 75 };
const CreateInfo scene002_createInfo1 = { &robotrunner_template, 64, 126 };
const CreateInfo scene002_createInfo2 = { &ninja_girl_template, 68, 18 };
const CreateInfo scene002_createInfo3 = { &walker_template, 98, 75 };
const CreateInfo scene002_createInfo4 = { &robotrunner_template, 119, 120 };
const CreateInfo scene002_createInfo5 = { &walker_small_template, 142, 22 };
const CreateInfo scene002_createInfo6 = { &robotspring_template, 143, 30 };
const CreateInfo scene002_createInfo7 = { &walker_small_template, 171, 16 };
const CreateInfo scene002_createInfo8 = { &robotrunner_template, 179, 27 };
const CreateInfo scene002_createInfo9 = { &walker_small_template, 209, 14 };
const CreateInfo scene002_createInfo10 = { &walker_small_template, 246, 11 };
const CreateInfo scene002_createInfo11 = { &robotrunner_template, 287, 1 };

const Command scene002_commands[] = 
{
    { 0, (CommandFunction)ResourceManager_LoadResource, &walkerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotrunnerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &ninja_girlResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &walker_smallResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotspringResourceInfo },
    { 0, (CommandFunction)CommandRunner_RightScroll_Init, NULL },
    { 59, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo0 },
    { 64, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo1 },
    { 68, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo2 },
    { 98, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo3 },
    { 119, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo4 },
    { 142, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo5 },
    { 143, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo6 },
    { 171, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo7 },
    { 179, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo8 },
    { 209, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo9 },
    { 246, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo10 },
    { 287, (CommandFunction)ObjectManager_CreateObjectByCreateInfo, &scene002_createInfo11 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene scene002 = 
{
    scene002_commands,
};
