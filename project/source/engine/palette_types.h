#ifndef PALETTE_TYPES_INCLUDE_H
#define PALETTE_TYPES_INCLUDE_H

#include "engine/resource_types.h"

typedef struct
{
    u8 resourceType;
    const u8* palette;
} PaletteResource;

#endif