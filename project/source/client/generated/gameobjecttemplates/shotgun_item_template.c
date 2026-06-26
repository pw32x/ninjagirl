#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resource_infos.h"

GameObject* ShotgunItem_Init(void/*GameObject* object, const CreateInfo* createInfo*/);

const GameObjectTemplate shotgun_item_template = 
{
    0, // health
    0, // damage
    -8, // rect left
    -8, // rect top
    8, // rect right
    8, // rect bottom
    OBJECTTYPE_ITEM, // object type
    &shotgun_item_animResourceInfo, // resource info
    NULL, // extra resource infos
    (InitObjectFunctionType)ShotgunItem_Init, // init function
};
