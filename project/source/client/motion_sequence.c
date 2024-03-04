#include "motion_sequence.h"

u8 MotionUtils_updateMotion(MotionSequenceRunner* motionSequenceRunner)
{
	if (!motionSequenceRunner->currentMotionSequenceNodeTime--)
	{
		motionSequenceRunner->currentMotionSequenceNode++;

		if (motionSequenceRunner->currentMotionSequenceNode->time == (u8)-1)
		{
			motionSequenceRunner->currentMotionSequenceNode = motionSequenceRunner->motionSequence->motionSequenceNodes;
		}

		motionSequenceRunner->currentMotionSequenceNodeTime = motionSequenceRunner->currentMotionSequenceNode->time;
		return MOTION_CHANGED_FRAME;
	}

	return MOTION_NO_CHANGE;
}