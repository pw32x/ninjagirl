#include "color_tweaker.h"
#include "engine/base_defines.h"
#include "engine/object_utils.h"
#include "engine/draw_utils.h"
#include "engine/resource_manager.h"

#include "SMSlib.h"

void ColorTweaker_Update(GameObject* object);
BOOL ColorTweaker_Draw(GameObject* object);

#define cursorAnimation extraData1

GameObject* ColorTweaker_Init(GameObject* object, const CreateInfo* createInfo)
{
	ResourceManager_LoadResource(createInfo->gameObjectTemplate->extraResources[0]);
	object->cursorAnimation = (u16)createInfo->gameObjectTemplate->extraResources[0]->resource;

	object->Update = ColorTweaker_Update;
	object->Draw = ColorTweaker_Draw;

	return object;
}


void ColorTweaker_Update(GameObject* object)
{
	object->screenx = 20;
	object->screeny = 20;

	/*
	ColorTweaker_counter = ScrollManager_horizontalScroll + SCREEN_WIDTH;

	u8 objectId = object->objectId;

	while (CommandManager_currentCommand->command != NULL && 
		   CommandManager_currentCommand->counter <= ColorTweaker_counter)
	{
		CommandManager_currentCommand->command(CommandManager_currentCommand->data);

		// check if the command runner changed while processing the
		// commands.
		if (objectId != object->objectId)
			return;

		CommandManager_currentCommand++;		
	}
	*/

	//SMS_debugPrintf("Hello\n");
}

BOOL ColorTweaker_Draw(GameObject* object)
{
	DRAWUTILS_SETUP_BATCH(object->screenx,
						  object->screeny,
						  object->currentBatchedAnimationFrame->spriteStrips,
						  *object->batchedAnimation->vdpLocation);

	DrawUtils_DrawBatched();


	const BatchedAnimation* cursor = (const BatchedAnimation*)object->cursorAnimation;

	DRAWUTILS_SETUP_BATCH(50,
						  object->screeny,
						  cursor->frames[0]->spriteStrips,
						  *cursor->vdpLocation);

	DrawUtils_DrawBatched();


	return TRUE;
}