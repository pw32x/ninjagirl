#ifndef LEVEL_TYPES_INCLUDE_H
#define LEVEL_TYPES_INCLUDE_H

#include "engine/spawn_types.h"
#include "engine/map_types.h"
#include "engine/command_types.h"

typedef struct
{
	const Command* commands;
} Level;

#endif