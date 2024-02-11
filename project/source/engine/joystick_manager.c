#include "joystick_manager.h"

#include "SMSlib.h"

u32 JoystickManager_buttonState;
u32 JoystickManager_buttonsPressed;
u32 JoystickManager_buttonsReleased;

void JoystickManager_Update(void)
{
	JoystickManager_buttonState = SMS_getKeysStatus();
	JoystickManager_buttonsPressed = SMS_getKeysPressed();
	JoystickManager_buttonsReleased = SMS_getKeysReleased();
}