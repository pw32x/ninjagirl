#ifndef MOTION_SEQUENCE_INCLUDE_H
#define MOTION_SEQUENCE_INCLUDE_H

#include "engine/base_types.h"

typedef struct
{
	s16 x;
	s16 y;
	u8 time;
} MotionSequenceNode;

typedef struct
{
	MotionSequenceNode* motionSequenceNodes;
	u16 numMotionSequenceNodes;
	u8 loopMotion;
} MotionSequence;


#endif