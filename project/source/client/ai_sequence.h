#ifndef AI_SEQUENCE_INCLUDE_H
#define AI_SEQUENCE_INCLUDE_H

#include "engine/base_types.h"

typedef BOOL (*AICommand)(struct game_object* object, void* data);

AICommandItem
{
	AICommand command;
	void* data;
};

typedef struct
{
	const AICommandItem* AICommandItems;
	u8 numAICommandItems;
	u8 time;
} AISequenceNode;

typedef struct
{
	AISequenceNode* AISequenceNodes;
	u16 numAISequenceNodes;
	u8 loop;
} AISequence;



#endif