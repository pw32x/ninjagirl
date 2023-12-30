#include "..\..\..\engine\gameobject_template_types.h"
#include "..\..\..\engine\object_types.h"
#include "..\resource_infos.h"

const GameObjectTemplate robotrunner_template = 
{
    3, // health
    1, // damage
    -9, // rect left
    -15, // rect top
    9, // rect right
    16, // rect bottom
    OBJECTTYPE_ENEMY, // object type
    &robotrunnerResourceInfo, // resource info
};