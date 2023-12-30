#include "..\..\..\engine\gameobject_template_types.h"
#include "..\..\..\engine\object_types.h"
#include "..\resource_infos.h"

const GameObjectTemplate walker_big_template = 
{
    4, // health
    1, // damage
    -16, // rect left
    -16, // rect top
    16, // rect right
    16, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    &walker_bigResourceInfo, // resource info
};