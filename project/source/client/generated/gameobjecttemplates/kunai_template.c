#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resource_infos.h"

GameObject* Kunai_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate kunai_template = 
{
    0, // health
    1, // damage
    -4, // rect left
    -4, // rect top
    4, // rect right
    4, // rect bottom
    OBJECTTYPE_PROJECTILE, // object type
    &kunaiResourceInfo, // resource info
    Kunai_Init, // init function
};
