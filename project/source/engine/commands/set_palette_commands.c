#include "set_palette_commands.h"
#include "engine/palette_types.h"

#include "smslib.h"

void SetBackgroundPalette(const ResourceInfo* resourceInfo)
{
	if (resourceInfo->bankNumber != 0)
		SMS_debugPrintf("SetBackgroundPalette using palette not in bank 0. Address: %d\n", resourceInfo->resource);

	PaletteResource* palette = (PaletteResource*)resourceInfo->resource;
	SMS_loadBGPalette(palette->palette);
}

void SetSpritePalette(const ResourceInfo* resourceInfo)
{
	if (resourceInfo->bankNumber != 0)
		SMS_debugPrintf("SetSpritePalette using palette not in bank 0. Address: %d\n", resourceInfo->resource);

	PaletteResource* palette = (PaletteResource*)resourceInfo->resource;
	SMS_loadSpritePalette(palette->palette);
}