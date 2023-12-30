#include "..\..\..\engine\gameobject_template_types.h"
#include "..\..\..\engine\object_types.h"
#include "..\resource_infos.h"

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
};
