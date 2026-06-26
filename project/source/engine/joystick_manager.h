#ifndef JOYSTICK_MANAGER_INCLUDE_H
#define JOYSTICK_MANAGER_INCLUDE_H

#include "engine/base_types.h"

void JoystickManager_Update(void);

#ifdef WIN32
unsigned int KeysStatus;
unsigned int PreviousKeysStatus;
#endif

extern u32 JoystickManager_buttonState;
extern u32 JoystickManager_buttonsPressed;
extern u32 JoystickManager_buttonsReleased;

#endif