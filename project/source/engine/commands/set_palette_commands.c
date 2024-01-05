#include "set_palette_commands.h"
#include "engine/palette_types.h"

#include "smslib.h"

// [COMMAND "Set Background Palette" PALETTE_RESOURCE_TYPE]
void SetBackgroundPalette(const ResourceInfo* resourceInfo)
{
	if (resourceInfo->bankNumber != 0)
		SMS_debugPrintf("SetBackgroundPalette using palette not in bank 0. Address: %d\n", resourceInfo->resource);

	PaletteResource* palette = (PaletteResource*)resourceInfo->resource;
	SMS_loadBGPalette(palette->palette);
}

// [COMMAND "Set Sprite Palette " PALETTE_RESOURCE_TYPE]
void SetSpritePalette(const ResourceInfo* resourceInfo)
{
	if (resourceInfo->bankNumber != 0)
		SMS_debugPrintf("SetSpritePalette using palette not in bank 0. Address: %d\n", resourceInfo->resource);

	PaletteResource* palette = (PaletteResource*)resourceInfo->resource;
	SMS_loadSpritePalette(palette->palette);
}