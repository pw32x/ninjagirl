#include "..\..\..\engine\gameobject_template_types.h"
#include "..\..\..\engine\object_types.h"
#include "..\resource_infos.h"

const GameObjectTemplate walker_small_template = 
{
    1, // health
    0, // damage
    -4, // rect left
    -4, // rect top
    4, // rect right
    4, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    &walker_smallResourceInfo, // resource info
};