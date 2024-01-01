#ifndef COMMAND_MANAGER_INCLUDE_H
#define COMMAND_MANAGER_INCLUDE_H

#include "engine\base_types.h"
#include "engine\object_types.h"
#include "engine\command_types.h"

extern GameObject CommandManager_commandRunnerObject;
extern const Command* CommandManager_currentCommand;
extern u16 CommandRunner_counter;

#endif