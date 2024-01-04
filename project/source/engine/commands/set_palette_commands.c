#include "set_palette_commands.h"


// [COMMAND "Set Background Palette" PALETTE_RESOURCE_TYPE]
void SetBackgroundPalette(const PaletteResource* palette)
{
	SMS_loadBGPalette(palette->palette);
}

// [COMMAND "Set Sprite Palette " PALETTE_RESOURCE_TYPE]
void SetSpritePalette(const PaletteResource* palette)
{
	SMS_loadSpritePalette(palette->palette);
}