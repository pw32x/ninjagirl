#include "commandrunner_rightscroll.h"
#include "engine/base_defines.h"
#include "engine/scroll_manager.h"
#include "engine/command_manager.h"
#include "engine/object_utils.h"

#include "SMSlib.h"

void CommandRunner_RightScroll_Update(GameObject* object);

GameObject* CommandRunner_RightScroll_Init(GameObject* object, const CommandRunnerCreateInfo* createInfo)
{
	UNUSED(createInfo);

	// move to the next command because the current one is
	// the one that created us.
	CommandManager_currentCommand++;

	CommandRunner_counter = 0;

	u8 objectId = object->objectId;

	while (CommandManager_currentCommand->command != NULL && 
		   CommandManager_currentCommand->counter < SCREEN_WIDTH)
	{
		CommandManager_currentCommand->command(CommandManager_currentCommand->data);

		// check if the command runner changed while processing the
		// commands.
		if (objectId != object->objectId)
			return NULL;

		CommandManager_currentCommand++;
	}

	object->Update = CommandRunner_RightScroll_Update;

	return object;
}


void CommandRunner_RightScroll_Update(GameObject* object)
{
	UNUSED(object);

	CommandRunner_counter = ScrollManager_horizontalScroll + SCREEN_WIDTH;

	u8 objectId = object->objectId;

	while (CommandManager_currentCommand->command != NULL && 
		   CommandManager_currentCommand->counter < CommandRunner_counter)
	{
		CommandManager_currentCommand->command(CommandManager_currentCommand->data);

		// check if the command runner changed while processing the
		// commands.
		if (objectId != object->objectId)
			return;

		CommandManager_currentCommand++;		
	}
}