#ifndef SET_PALETTE_COMMANDS_INCLUDE_H
#define SET_PALETTE_COMMANDS_INCLUDE_H

#include "engine/palette_types.h"

// [COMMAND "Set Background Palette" PALETTE_RESOURCE_TYPE]
void SetBackgroundPalette(const PaletteResource* palette);

// [COMMAND "Set Sprite Palette " PALETTE_RESOURCE_TYPE]
void SetSpritePalette(const PaletteResource* palette);

#endif