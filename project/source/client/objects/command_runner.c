#include "command_runner.h"
#include "engine/base_defines.h"
#include "engine/scroll_manager.h"
#include "engine/spawn_manager.h"
#include "engine/object_utils.h"

u16 CommandRunner_scrollX;
const Command* CommandRunner_currentCommand;
u32 CommandRunner_counter;

void CommandRunner_Update(void);

void CommandRunner_Create(const Command* commands)
{
	CommandRunner_scrollX = 0;

	CommandRunner_currentCommand = commands;

	while (CommandRunner_currentCommand->command != NO_DATA && CommandRunner_currentCommand->counter < SCREEN_WIDTH)
	{
		CommandRunner_currentCommand->command(CommandRunner_currentCommand->data);
		CommandRunner_currentCommand++;
	}

	SpawnManager_Update = CommandRunner_Update;
}


void CommandRunner_Update(void)
{
	CommandRunner_scrollX += ScrollManager_speedX;

	while (CommandRunner_currentCommand->command != NO_DATA && 
		   CommandRunner_currentCommand->counter < CommandRunner_scrollX + SCREEN_WIDTH)
	{
		CommandRunner_currentCommand->command(CommandRunner_currentCommand->data);
		CommandRunner_currentCommand++;		
	}
}