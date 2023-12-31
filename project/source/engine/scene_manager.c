#include "scene_manager.h"
#include "SMSlib.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/vdptile_manager.h"

void SceneManager_Init(const Scene* scene)
{
	// init systems
	ObjectManager_Init();
	VDPTileManager_Init();

	// TODO
	// use a "dumb" command runner go through all the commands.
	// if it finds a new command runner, it'll switch over to it.

	// we assume the first item is a command processor
	CommandFunction firstCommand = scene->commands->command;
	firstCommand(scene->commands + 1);
}