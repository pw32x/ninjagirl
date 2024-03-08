#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resource_infos.h"

GameObject* Bullet_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate enemy_bullet_template = 
{
    0, // health
    1, // damage
    -4, // rect left
    -4, // rect top
    4, // rect right
    4, // rect bottom
    OBJECTTYPE_ENEMY_PROJECTILE, // object type
    &enemy_bulletResourceInfo, // resource info
    NULL, // extra resource infos
    Bullet_Init, // init function
};
