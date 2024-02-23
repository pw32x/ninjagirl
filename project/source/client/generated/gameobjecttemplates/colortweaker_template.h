#ifndef COLORTWEAKER_TEMPLATE_INCLUDE_H
#define COLORTWEAKER_TEMPLATE_INCLUDE_H

#include "engine\object_types.h"

typedef struct
{
    GAME_OBJECT_FIELDS;
    const BatchedAnimation* cursorAnimation;
    u8 cursorY;
    u8 colorIndex;
    const u8* originalPalette;
} ColorTweakerObjectType;

#endif
