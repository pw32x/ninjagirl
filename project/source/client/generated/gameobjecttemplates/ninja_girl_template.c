#include "..\..\..\engine\gameobject_template_types.h"
#include "..\..\..\engine\object_types.h"
#include "..\resource_infos.h"

const GameObjectTemplate ninja_girl_template = 
{
    2, // health
    0, // damage
    -3, // rect left
    -12, // rect top
    3, // rect right
    16, // rect bottom
    OBJECTTYPE_PLAYER, // object type
    &ninja_girlResourceInfo, // resource info
};