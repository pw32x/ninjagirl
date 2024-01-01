#include "commandrunner_runall.h"
#include "engine/command_manager.h"
#include "engine/object_utils.h"

const GameObjectTemplate commandrunner_runall_template = 
{
	0, // health
	0, // damage
	0, // rect left
	0, // rect top
	0, // rect right
	0, // rect bottom
	OBJECTTYPE_COMMANDRUNNER, // object type
	NULL, // resource info
	(InitObjectFunctionType)CommandRunner_RunAll_Init, // init function
};

GameObject* CommandRunner_RunAll_Init(GameObject* object, const CommandRunnerCreateInfo* createInfo)
{
	UNUSED(createInfo);

	// move to the next command because the current one is
	// the one that created us.
	CommandManager_currentCommand++;

	u8 objectId = object->objectId;

	while (CommandManager_currentCommand->command != NULL)
	{
		CommandManager_currentCommand->command(CommandManager_currentCommand->data);

		// check if the command runner changed while processing the
		// commands.
		if (objectId != object->objectId)
			return NULL;

		CommandManager_currentCommand++;
	}

	object->Update = ObjectUtils_gameObjectDoNothing;

	return NULL;
}



