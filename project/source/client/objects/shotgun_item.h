#ifndef SHOTGUNITEM_INCLUDE_H
#define SHOTGUNITEM_INCLUDE_H

#include "engine/object_types.h"
#include "engine/createinfo_types.h"
#include "client/generated/gameobjecttemplates/shotgun_item_template.h"

GameObject* ShotgunItem_Init(ShotgunItemObjectType* object, const CreateInfo* createInfo);

#endif