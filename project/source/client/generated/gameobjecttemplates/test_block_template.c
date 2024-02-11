#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resource_infos.h"

GameObject* Enemy_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate test_block_template = 
{
    3, // health
    1, // damage
    -8, // rect left
    -16, // rect top
    8, // rect right
    16, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    &test_blockResourceInfo, // resource info
    NULL, // resource infos
    Enemy_Init, // init function
};
