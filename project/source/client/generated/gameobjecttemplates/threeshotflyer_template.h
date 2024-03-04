#ifndef THREESHOTFLYER_TEMPLATE_INCLUDE_H
#define THREESHOTFLYER_TEMPLATE_INCLUDE_H

#include "engine\object_types.h"

typedef struct three_shot_flyer_object
{
    GAME_OBJECT_FIELDS;
    const AISequence* aiSequence;
} ThreeShotFlyerObjectType;

#endif
