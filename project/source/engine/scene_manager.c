#include "scene_manager.h"
#include "SMSlib.h"
#include "engine/command_manager.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/vdptile_manager.h"
#include "engine/createinfo_types.h"
#include "engine/commandrunner_runall.h"

void SceneManager_Init(const Scene* scene)
{
	// init systems
	ObjectManager_Init();
	VDPTileManager_Init();

	CommandManager_currentCommand = scene->commands;

	// we assume the first item is a command processor
	CommandFunction firstCommand = CommandManager_currentCommand->command;
	firstCommand(CommandManager_currentCommand->data);
}