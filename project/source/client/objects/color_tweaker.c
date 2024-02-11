#include "color_tweaker.h"
#include "engine/base_defines.h"
#include "engine/object_utils.h"
#include "engine/draw_utils.h"

#include "SMSlib.h"

void ColorTweaker_Update(GameObject* object);
BOOL ColorTweaker_Draw(GameObject* object);

GameObject* ColorTweaker_Init(GameObject* object, const CreateInfo* createInfo)
{
	UNUSED(createInfo);

	/*
	// move to the next command because the current one is
	// the one that created us.
	CommandManager_currentCommand++;

	ColorTweaker_counter = 0;

	u8 objectId = object->objectId;

	while (CommandManager_currentCommand->command != NULL && 
		   CommandManager_currentCommand->counter <= SCREEN_WIDTH)
	{
		CommandManager_currentCommand->command(CommandManager_currentCommand->data);

		// check if the command runner changed while processing the
		// commands.
		if (objectId != object->objectId)
			return NULL;

		CommandManager_currentCommand++;
	}
	*/
	object->Update = ColorTweaker_Update;
	object->Draw = ColorTweaker_Draw;

	object->screenx = 20;
	object->screeny = 20;

	return object;
}


void ColorTweaker_Update(GameObject* object)
{
	UNUSED(object);

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

	return TRUE;
}