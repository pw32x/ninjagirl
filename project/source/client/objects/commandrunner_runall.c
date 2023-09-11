#include "commandrunner_runall.h"
#include "engine/command_manager.h"
#include "engine/object_utils.h"

GameObject* CommandRunner_RunAll_Create(const Command* commands)
{
	const Command* commandRunner = commands;

	while (commandRunner->command != NULL)
	{
		commandRunner->command(commandRunner->data);
		commandRunner++;
	}

	CommandManager_Update = ObjectUtils_doNothing;

	return NULL;
}



