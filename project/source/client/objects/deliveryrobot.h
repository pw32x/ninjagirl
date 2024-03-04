#ifndef DELIVERYROBOT_INCLUDE_H
#define DELIVERYROBOT_INCLUDE_H

#include "engine/object_types.h"
#include "engine/createinfo_types.h"
#include "client/motion_sequence.h"
#include "client/generated/gameobjecttemplates/deliveryrobot_template.h"

GameObject* DeliveryRobot_Init(DeliveryRobotObjectType* object, const CreateInfo* createInfo);

#endif