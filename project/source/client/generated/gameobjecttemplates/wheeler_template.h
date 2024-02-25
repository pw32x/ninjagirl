#ifndef WHEELER_TEMPLATE_INCLUDE_H
#define WHEELER_TEMPLATE_INCLUDE_H

#include "engine\object_types.h"

typedef struct wheeler_object
{
    GAME_OBJECT_FIELDS;
    void (*UpdatePhysics)(struct wheeler_object* gameObject);
} WheelerObjectType;

#endif
