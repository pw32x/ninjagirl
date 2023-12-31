#include "commandrunner_rightscroll.h"
#include "engine/base_defines.h"
#include "engine/scroll_manager.h"
#include "engine/command_manager.h"
#include "engine/object_utils.h"

u16 CommandRunner_scrollX;
const Command* CommandRunner_currentCommand;
u32 CommandRunner_counter;

void CommandRunner_RightScroll_Update(void);

void CommandRunner_RightScroll_Init(const Command* commands)
{
	CommandRunner_scrollX = 0;

	CommandRunner_currentCommand = commands;

	while (CommandRunner_currentCommand->command != NULL && 
		   CommandRunner_currentCommand->counter < SCREEN_WIDTH)
	{
		CommandRunner_currentCommand->command(CommandRunner_currentCommand->data);
		CommandRunner_currentCommand++;
	}

	CommandManager_Update = CommandRunner_RightScroll_Update;
}


void CommandRunner_RightScroll_Update(void)
{
	CommandRunner_scrollX += ScrollManager_speedX;

	while (CommandRunner_currentCommand->command != NULL && 
		   CommandRunner_currentCommand->counter < CommandRunner_scrollX + SCREEN_WIDTH)
	{
		CommandRunner_currentCommand->command(CommandRunner_currentCommand->data);
		CommandRunner_currentCommand++;		
	}
}