#include "..\..\..\engine\gameobject_template_types.h"
#include "..\..\..\engine\object_types.h"
#include "..\resource_infos.h"

const GameObjectTemplate impact_template = 
{
    0, // health
    0, // damage
    0, // rect left
    0, // rect top
    0, // rect right
    0, // rect bottom
    OBJECTTYPE_EFFECT, // object type
    &impactResourceInfo, // resource info
};
