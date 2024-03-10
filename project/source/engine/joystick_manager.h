#ifndef JOYSTICK_MANAGER_INCLUDE_H
#define JOYSTICK_MANAGER_INCLUDE_H

#include "engine/base_types.h"

inline void JoystickManager_Update(void);


extern u32 JoystickManager_buttonState;
extern u32 JoystickManager_buttonsPressed;
extern u32 JoystickManager_buttonsReleased;

#endif