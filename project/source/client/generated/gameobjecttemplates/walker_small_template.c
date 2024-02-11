#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resource_infos.h"

GameObject* Enemy_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate walker_small_template = 
{
    1, // health
    0, // damage
    -4, // rect left
    -4, // rect top
    4, // rect right
    4, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    &walker_smallResourceInfo, // resource info
    NULL, // resource infos
    Enemy_Init, // init function
};
