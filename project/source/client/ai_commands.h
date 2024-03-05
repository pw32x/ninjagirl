#ifndef AI_COMMANDS_INCLUDE_H
#define AI_COMMANDS_INCLUDE_H

#include "engine/base_types.h"
#include "engine/object_types.h"

typedef BOOL (*AICommand)(struct game_object* object, void* data);

typedef struct
{
	AICommand command;
	void* data;
} AICommandItem;

typedef struct
{
	const AICommandItem* currentAICommandItem;
	u16 waitTime;
} AICommandsRunner;

											// data:
#define AI_COMMAND_WAIT					0	// number of frames to wait
#define AI_COMMAND_JUMP					1	// pointer offset in sequence to jump to
#define AI_COMMAND_SET_COMMANDITEMS		2	// pointer to new sequence

void AICommandUtils_updateAICommandsRunner(struct game_object* object, AICommandsRunner* aiCommandsRunner);


#endif