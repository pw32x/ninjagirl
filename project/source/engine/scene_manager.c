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


	// we assume the first item is a command processor
	CommandFunction firstCommand = scene->commands->command;
	firstCommand(scene->commands + 1);
}