#include "ai_commands.h"

void AICommandUtils_updateAICommandsRunner(struct game_object* object, AICommandsRunner* aiCommandsRunner)
{
	if (aiCommandsRunner->waitTime--)
		return;

	// process until we have to wait, which means the "frame" is done.
	while (1)
	{
		aiCommandsRunner->currentAICommandItem++;

		const AICommandItem* aiCommandItem = 	aiCommandsRunner->currentAICommandItem;
		u16 data = (u16)aiCommandItem->data;

		switch ((u16)aiCommandItem->command)
		{
		case AI_COMMAND_WAIT:
			aiCommandsRunner->waitTime = data;
			return; // we're done, so just return
		case AI_COMMAND_JUMP:
			aiCommandsRunner->currentAICommandItem = aiCommandItem + (s16)data;
			break;
		case AI_COMMAND_SET_COMMANDITEMS:
			aiCommandsRunner->currentAICommandItem = (const AICommandItem*)data;
		default:
			// run the command
			aiCommandItem->command(object, (void*)data);
			break;
		}
	}
}