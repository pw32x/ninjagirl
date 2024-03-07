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
#define AI_COMMAND_JUMP					1	// offset in ai sequence to jump to
#define AI_COMMAND_SET_COMMANDITEMS		2	// pointer to new sequence
#define AI_COMMAND_SET_SPEEDX			3
#define AI_COMMAND_SET_SPEEDY			4


// AI_COMMAND_SET_MOTION
// AI_COMMAND_SET_COLLISION_FUNCTION
// AI_COMMAND_SET_UPDATE_FUNCTION
// AI_COMMAND_SET_DRAW_FUNCTION
// AI_COMMAND_SET_ANIMATION
// AI_COMMAND_SET_ANIMATION_FRAME
// AI_COMMAND_SET_HEALTH
// AI_COMMAND_SET_DAMAGE
// AI_COMMAND_SET_X
// AI_COMMAND_SET_Y
// AI_COMMAND_SET_SPEEDX
// AI_COMMAND_SET_SPEEDY
// AI_COMMAND_SET_FLIPPED
// AI_COMMAND_SET_RECTLEFT
// AI_COMMAND_SET_RECTRIGHT
// AI_COMMAND_SET_RECTTOP
// AI_COMMAND_SET_RECTBOTTOM
// AI_COMMAND_LOAD_RESOURCE



void AICommandUtils_updateAICommandsRunner(struct game_object* object, AICommandsRunner* aiCommandsRunner);


#endif