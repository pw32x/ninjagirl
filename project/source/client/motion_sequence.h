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
	const MotionSequenceNode* motionSequenceNodes;
	u16 numMotionSequenceNodes;
	u8 loopMotion;
} MotionSequence;

typedef struct
{
	const MotionSequence* motionSequence;
	const MotionSequenceNode* currentMotionSequenceNode;
	u8 currentMotionSequenceNodeTime;
} MotionSequenceRunner;


#define MOTION_NO_CHANGE			0
#define MOTION_CHANGED_FRAME		1
#define MOTION_FINISHED				2

u8 MotionUtils_updateMotion(MotionSequenceRunner* motionSequenceRunner);

#endif