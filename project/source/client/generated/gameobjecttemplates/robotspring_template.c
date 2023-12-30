#include "..\..\..\engine\gameobject_template_types.h"
#include "..\..\..\engine\object_types.h"
#include "..\..\..\engine\createinfo_types.h"
#include "..\resource_infos.h"

GameObject* Enemy_Create(const CreateInfo* createInfo);

const GameObjectTemplate robotspring_template = 
{
    2, // health
    1, // damage
    -8, // rect left
    -8, // rect top
    8, // rect right
    11, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    &robotspringResourceInfo, // resource info
    Enemy_Create, // create function
};
