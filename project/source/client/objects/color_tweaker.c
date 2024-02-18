#include "color_tweaker.h"
#include "engine/base_defines.h"
#include "engine/object_utils.h"
#include "engine/draw_utils.h"
#include "engine/resource_manager.h"
#include "engine/joystick_manager.h"
#include "engine/animation_utils.h"

#include "engine/palette_types.h"

#include "SMSlib.h"
#include <string.h>

void ColorTweaker_Update(GameObject* object);
BOOL ColorTweaker_Draw(GameObject* object);

#define cursorAnimation extraData1
#define cursorY extraData2
#define colorIndex extraData3
#define originalPalette extraData4


u8 redChannel[16];
u8 greenChannel[16];
u8 blueChannel[16];
u8 palette[16];

GameObject* ColorTweaker_Init(GameObject* object, const CreateInfo* createInfo)
{
	ResourceManager_LoadResource(createInfo->gameObjectTemplate->extraResources[0]);
	object->cursorAnimation = (u16)createInfo->gameObjectTemplate->extraResources[0]->resource;

	const PaletteResource* paletteResource = (const PaletteResource*)createInfo->gameObjectTemplate->extraResources[1]->resource;

	object->originalPalette = paletteResource->palette;

	for (int loop = 0; loop < 16; loop++)
	{
		redChannel[loop] = paletteResource->palette[loop] & 0x03;
		greenChannel[loop] = (paletteResource->palette[loop] & 0x0C) >> 2;
		blueChannel[loop] = (paletteResource->palette[loop] & 0x30) >> 4;
		palette[loop] = paletteResource->palette[loop];
	}

	object->Update = ColorTweaker_Update;
	object->Draw = ColorTweaker_Draw;

	object->cursorY = 0;
	object->colorIndex = 0;
	AnimationUtils_setBatchedAnimationFrame(object, object->colorIndex);

	return object;
}


void ColorTweaker_Update(GameObject* object)
{
	object->screenx = 20;
	object->screeny = 20;

	BOOL printDebug = FALSE;

	if (JoystickManager_buttonsPressed & PORT_B_KEY_DOWN)
	{
		object->cursorY++;
		printDebug = TRUE;
	}
	else if (JoystickManager_buttonsPressed & PORT_B_KEY_UP)
	{
		object->cursorY--;
		printDebug = TRUE;
	}

	object->cursorY &= 3;

	if (JoystickManager_buttonsPressed & PORT_B_KEY_1)
	{
		SMS_loadSpritePalette((void*)object->originalPalette);
		SMS_loadBGPalette((void*)object->originalPalette);

		for (int loop = 0; loop < 16; loop++)
		{
			redChannel[loop] = ((u8*)object->originalPalette)[loop] & 0x03;
			greenChannel[loop] = (((u8*)object->originalPalette)[loop] & 0x0C) >> 2;
			blueChannel[loop] = (((u8*)object->originalPalette)[loop] & 0x30) >> 4;
			palette[loop] = ((u8*)object->originalPalette)[loop];
		}
	}

	if (JoystickManager_buttonsPressed & PORT_B_KEY_LEFT)
	{
		if (object->cursorY == 0)
		{
			if (object->colorIndex == 0)
				object->colorIndex = 15;
			else
				object->colorIndex--;

			AnimationUtils_setBatchedAnimationFrame(object, object->colorIndex);
			printDebug = TRUE;
		}
		else if (object->cursorY == 1)
		{
			redChannel[object->colorIndex]--;
			redChannel[object->colorIndex] &= 3;

			u8 newColor = redChannel[object->colorIndex] + 
						  (greenChannel[object->colorIndex] << 2) + 
						  (blueChannel[object->colorIndex] << 4);
			palette[object->colorIndex] = newColor;
			SMS_setBGPaletteColor(object->colorIndex, newColor);
			SMS_setSpritePaletteColor(object->colorIndex, newColor);
			printDebug = TRUE;
		}
		else if (object->cursorY == 2)
		{
			greenChannel[object->colorIndex]--;
			greenChannel[object->colorIndex] &= 3;

			u8 newColor = redChannel[object->colorIndex] + 
				(greenChannel[object->colorIndex] << 2) + 
				(blueChannel[object->colorIndex] << 4);
			palette[object->colorIndex] = newColor;
			SMS_setBGPaletteColor(object->colorIndex, newColor);
			SMS_setSpritePaletteColor(object->colorIndex, newColor);
			printDebug = TRUE;
		}
		else if (object->cursorY == 3)
		{
			blueChannel[object->colorIndex]--;
			blueChannel[object->colorIndex] &= 3;

			u8 newColor = redChannel[object->colorIndex] + 
				(greenChannel[object->colorIndex] << 2) + 
				(blueChannel[object->colorIndex] << 4);
			palette[object->colorIndex] = newColor;
			SMS_setBGPaletteColor(object->colorIndex, newColor);
			SMS_setSpritePaletteColor(object->colorIndex, newColor);
			printDebug = TRUE;
		}
	}
	else if (JoystickManager_buttonsPressed & PORT_B_KEY_RIGHT)
	{
		if (object->cursorY == 0)
		{
			if (object->colorIndex == 15)
				object->colorIndex = 0;
			else
				object->colorIndex++;

			AnimationUtils_setBatchedAnimationFrame(object, object->colorIndex);
			printDebug = TRUE;
		}
		else if (object->cursorY == 1)
		{
			redChannel[object->colorIndex]++;
			redChannel[object->colorIndex] &= 3;

			u8 newColor = redChannel[object->colorIndex] + 
						  (greenChannel[object->colorIndex] << 2) + 
						  (blueChannel[object->colorIndex] << 4);
			palette[object->colorIndex] = newColor;
			SMS_setBGPaletteColor(object->colorIndex, newColor);
			SMS_setSpritePaletteColor(object->colorIndex, newColor);
			printDebug = TRUE;
		}
		else if (object->cursorY == 2)
		{
			greenChannel[object->colorIndex]++;
			greenChannel[object->colorIndex] &= 3;

			u8 newColor = redChannel[object->colorIndex] + 
				(greenChannel[object->colorIndex] << 2) + 
				(blueChannel[object->colorIndex] << 4);
			palette[object->colorIndex] = newColor;
			SMS_setBGPaletteColor(object->colorIndex, newColor);
			SMS_setSpritePaletteColor(object->colorIndex, newColor);
			printDebug = TRUE;
		}
		else if (object->cursorY == 3)
		{
			blueChannel[object->colorIndex]++;
			blueChannel[object->colorIndex] &= 3;

			u8 newColor = redChannel[object->colorIndex] + 
				(greenChannel[object->colorIndex] << 2) + 
				(blueChannel[object->colorIndex] << 4);
			palette[object->colorIndex] = newColor;
			SMS_setBGPaletteColor(object->colorIndex, newColor);
			SMS_setSpritePaletteColor(object->colorIndex, newColor);

			printDebug = TRUE;
		}
	}

	if (printDebug)
	{
		SMS_debugPrintf("Colors: ");
		for (int loop = 0; loop < 16; loop++)
			SMS_debugPrintf("%x, ", palette[loop]);
		SMS_debugPrintf("\n");
	}
}

BOOL ColorTweaker_Draw(GameObject* object)
{
	DRAWUTILS_SETUP_BATCH(object->screenx,
						  object->screeny,
						  object->currentBatchedAnimationFrame->spriteStrips,
						  *object->batchedAnimation->vdpLocation);

	DrawUtils_DrawBatched();


	const BatchedAnimation* cursor = (const BatchedAnimation*)object->cursorAnimation;

	DRAWUTILS_SETUP_BATCH(12,
						  object->screeny + (object->cursorY << 3) + 8,
						  cursor->frames[0]->spriteStrips,
						  *cursor->vdpLocation);

	DrawUtils_DrawBatched();

	DRAWUTILS_SETUP_BATCH(38,
						  object->screeny + 16,
						  cursor->frames[redChannel[object->colorIndex] + 1]->spriteStrips,
						  *cursor->vdpLocation);

	DrawUtils_DrawBatched();

	DRAWUTILS_SETUP_BATCH(38,
						  object->screeny + 24,
						  cursor->frames[greenChannel[object->colorIndex] + 1]->spriteStrips,
						  *cursor->vdpLocation);

	DrawUtils_DrawBatched();

	DRAWUTILS_SETUP_BATCH(38,
						  object->screeny + 32,
						  cursor->frames[blueChannel[object->colorIndex] + 1]->spriteStrips,
						  *cursor->vdpLocation);

	DrawUtils_DrawBatched();


	return TRUE;
}