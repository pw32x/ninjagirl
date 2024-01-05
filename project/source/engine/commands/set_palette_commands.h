#ifndef SET_PALETTE_COMMANDS_INCLUDE_H
#define SET_PALETTE_COMMANDS_INCLUDE_H

#include "engine/resource_types.h"


// [COMMAND "Set Background Palette" PALETTE_RESOURCE_TYPE]
void SetBackgroundPalette(const ResourceInfo* resourceInfo);

// [COMMAND "Set Sprite Palette" PALETTE_RESOURCE_TYPE]
void SetSpritePalette(const ResourceInfo* resourceInfo);

#endif