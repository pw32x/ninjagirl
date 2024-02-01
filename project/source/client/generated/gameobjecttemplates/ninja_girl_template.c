#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resource_infos.h"

GameObject* Player_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate ninja_girl_template = 
{
    2, // health
    0, // damage
    -3, // rect left
    -12, // rect top
    3, // rect right
    16, // rect bottom
    OBJECTTYPE_PLAYER, // object type
    &gun_girlResourceInfo, // resource info
    Player_Init, // init function
};
