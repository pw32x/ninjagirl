#ifndef SHOTGUN_ITEM_TEMPLATE_INCLUDE_H
#define SHOTGUN_ITEM_TEMPLATE_INCLUDE_H

#include "engine\object_types.h"

typedef struct shotgunitem_object
{
    GAME_OBJECT_FIELDS;
    void (*UpdatePhysics)(struct shotgunitem_object* gameObject);
} ShotgunItemObjectType;

#endif
