#ifndef COMMAND_TYPES_INCLUDE_H
#define COMMAND_TYPES_INCLUDE_H

#include "engine/base_types.h"

typedef BOOL (*CommandFunction)(void* data);

typedef struct 
{
	u16 counter;// counter/timer/scroll pos
	CommandFunction command;
	void* data;
} Command;


#endif