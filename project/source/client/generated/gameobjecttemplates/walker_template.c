#include "..\..\..\engine\gameobject_template_types.h"
#include "..\..\..\engine\object_types.h"
#include "..\resource_infos.h"

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
};
