#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resource_infos.h"

GameObject* Enemy_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate wheeler_template = 
{
    3, // health
    1, // damage
    -4, // rect left
    -15, // rect top
    4, // rect right
    16, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    &wheelerResourceInfo, // resource info
    NULL, // extra resource infos
    Enemy_Init, // init function
};
