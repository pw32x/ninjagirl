#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resource_infos.h"

GameObject* Enemy_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate walker_template = 
{
    2, // health
    1, // damage
    -8, // rect left
    -8, // rect top
    8, // rect right
    8, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    &walkerResourceInfo, // resource info
    NULL, // extra resource infos
    Enemy_Init, // init function
};
