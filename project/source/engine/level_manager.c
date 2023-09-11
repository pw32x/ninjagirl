#include "level_manager.h"
#include "SMSlib.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/vdptile_manager.h"

void LevelManager_Init(const Level* level)
{
	// init systems
	ObjectManager_Init();
	VDPTileManager_Init();


	// we assume the first item is a command processor
	CommandFunction firstCommand = level->commands->command;
	firstCommand(level->commands + 1);
}