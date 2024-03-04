#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resource_infos.h"

GameObject* ThreeShotFlyer_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate threeshotflyer_template = 
{
    2, // health
    1, // damage
    -12, // rect left
    -12, // rect top
    12, // rect right
    6, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    &threeshotflyerResourceInfo, // resource info
    NULL, // extra resource infos
    ThreeShotFlyer_Init, // init function
};
