#include "engine\gameobject_template_types.h"
#include "engine\object_types.h"
#include "engine\createinfo_types.h"
#include "client\generated\resource_infos.h"

ResourceInfo* colortweaker_templateResourceInfos[] = 
{
&colorTweakerCursorResourceInfo,
};

GameObject* ColorTweaker_Init(GameObject* object, const CreateInfo* createInfo);

const GameObjectTemplate colortweaker_template = 
{
    0, // health
    0, // damage
    0, // rect left
    0, // rect top
    0, // rect right
    0, // rect bottom
    OBJECTTYPE_EFFECT, // object type
    &colorTweakerResourceInfo, // resource info
    colortweaker_templateResourceInfos, // resource infos
    ColorTweaker_Init, // init function
};
