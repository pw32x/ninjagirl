#ifndef CREATEINFO_TYPES_INCLUDE_H
#define CREATEINFO_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "engine/gameobject_template_types.h"
#include "engine/command_types.h"

#define STANDARD_CREATE_INFO \
const GameObjectTemplate* gameObjectTemplate;\
s16 startX;\
s16 startY;

typedef struct create_info
{
	STANDARD_CREATE_INFO
} CreateInfo;

typedef struct commandrunner_create_info
{
	STANDARD_CREATE_INFO
	const Command* commands;
} CommandRunnerCreateInfo;

#endif