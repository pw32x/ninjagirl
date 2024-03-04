#ifndef DELIVERYROBOT_TEMPLATE_INCLUDE_H
#define DELIVERYROBOT_TEMPLATE_INCLUDE_H

#include "engine\object_types.h"

typedef struct delivery_robot_object
{
    GAME_OBJECT_FIELDS;
    MotionSequenceRunner motionSequenceRunner;
} DeliveryRobotObjectType;

#endif
