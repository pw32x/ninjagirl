#ifndef THREESHOTFLYER_INCLUDE_H
#define THREESHOTFLYER_INCLUDE_H

#include "engine/object_types.h"
#include "engine/createinfo_types.h"

#include "client/ai_commands.h"
#include "client/generated/gameobjecttemplates/threeshotflyer_template.h"

GameObject* ThreeShotFlyer_Init(ThreeShotFlyerObjectType* object, const CreateInfo* createInfo);

#endif