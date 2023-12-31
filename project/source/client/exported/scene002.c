#include "scene002.h"

#include "engine/resource_manager.h"
#include "engine/command_types.h"
#include "client/generated/resource_infos.h"
#include "client/generated/gameobjecttemplates/gameobject_templates.h"
#include "engine\createinfo_types.h"


#include "client/objects/commandrunner_rightscroll.h"
#include "client/objects/player.h"
#include "client/objects/kunai.h"
#include "client/objects/enemy.h"
#include "client/objects/right_scroller.h"
//#include "client/objects/bird.h"
#include "client/objects/tile_animator.h"

const CreateInfo scene002_createInfo0 = { 59, 75, &walker_template};
const CreateInfo scene002_createInfo1 = { 64, 126, &robotrunner_template};
const CreateInfo scene002_createInfo2 = { 68, 18, &ninja_girl_template};
const CreateInfo scene002_createInfo3 = { 98, 75, &walker_template};
const CreateInfo scene002_createInfo4 = { 119, 120, &robotrunner_template};
const CreateInfo scene002_createInfo5 = { 142, 22, &walker_small_template};
const CreateInfo scene002_createInfo6 = { 143, 30, &robotspring_template};
const CreateInfo scene002_createInfo7 = { 171, 16, &walker_small_template};
const CreateInfo scene002_createInfo8 = { 179, 27, &robotrunner_template};
const CreateInfo scene002_createInfo9 = { 209, 14, &walker_small_template};
const CreateInfo scene002_createInfo10 = { 246, 11, &walker_small_template};
const CreateInfo scene002_createInfo11 = { 287, 1, &robotrunner_template};

const Command scene002_commands[] = 
{
    { 0, (CommandFunction)ResourceManager_LoadResource, &walkerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotrunnerResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &ninja_girlResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &walker_smallResourceInfo },
    { 0, (CommandFunction)ResourceManager_LoadResource, &robotspringResourceInfo },
    { 0, (CommandFunction)CommandRunner_RightScroll_Create, NULL },
    { 59, (CommandFunction)Enemy_Create, &scene002_createInfo0 },
    { 64, (CommandFunction)Enemy_Create, &scene002_createInfo1 },
    { 68, (CommandFunction)Player_Create, &scene002_createInfo2 },
    { 98, (CommandFunction)Enemy_Create, &scene002_createInfo3 },
    { 119, (CommandFunction)Enemy_Create, &scene002_createInfo4 },
    { 142, (CommandFunction)Enemy_Create, &scene002_createInfo5 },
    { 143, (CommandFunction)Enemy_Create, &scene002_createInfo6 },
    { 171, (CommandFunction)Enemy_Create, &scene002_createInfo7 },
    { 179, (CommandFunction)Enemy_Create, &scene002_createInfo8 },
    { 209, (CommandFunction)Enemy_Create, &scene002_createInfo9 },
    { 246, (CommandFunction)Enemy_Create, &scene002_createInfo10 },
    { 287, (CommandFunction)Enemy_Create, &scene002_createInfo11 },
    { 0, (CommandFunction)NULL, NULL}
};

const Scene scene002 = 
{
    scene002_commands,
};
