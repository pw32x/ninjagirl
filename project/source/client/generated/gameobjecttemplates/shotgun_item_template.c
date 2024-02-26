#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resource_infos.h"

GameObject* ShotgunItem_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate shotgun_item_template = 
{
    0, // health
    0, // damage
    -8, // rect left
    -8, // rect top
    8, // rect right
    8, // rect bottom
    OBJECTTYPE_ITEM, // object type
    &shotgun_itemResourceInfo, // resource info
    NULL, // extra resource infos
    ShotgunItem_Init, // init function
};
