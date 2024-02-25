#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resource_infos.h"

GameObject* Shotgun_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate shotgun_template = 
{
    0, // health
    3, // damage
    -6, // rect left
    -6, // rect top
    6, // rect right
    6, // rect bottom
    OBJECTTYPE_PROJECTILE, // object type
    &shotgunResourceInfo, // resource info
    NULL, // extra resource infos
    Shotgun_Init, // init function
};
