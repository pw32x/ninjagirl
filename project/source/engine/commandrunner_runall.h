#ifndef COMMANDRUNNER_RUNALL_INCLUDE_H
#define COMMANDRUNNER_RUNALL_INCLUDE_H

#include "engine/object_types.h"
#include "engine/command_types.h"
#include "engine/createinfo_types.h"
#include "engine\gameobject_template_types.h"

GameObject* CommandRunner_RunAll_Init(GameObject* object, const CommandRunnerCreateInfo* createInfo);

extern const GameObjectTemplate commandrunner_runall_template;


#endif