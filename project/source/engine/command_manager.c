#include "engine/command_manager.h"
#include "engine/object_utils.h"

GameObject CommandManager_commandRunnerObject;
const Command* CommandManager_currentCommand;
u16 CommandRunner_counter;