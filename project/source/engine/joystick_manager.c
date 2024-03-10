#include "joystick_manager.h"

#include "SMSlib.h"

u32 JoystickManager_buttonState;
u32 JoystickManager_buttonsPressed;
u32 JoystickManager_buttonsReleased;

extern volatile unsigned int KeysStatus;
extern volatile unsigned int PreviousKeysStatus;

void JoystickManager_Update(void)
{
	JoystickManager_buttonState = KeysStatus;
	JoystickManager_buttonsPressed = (KeysStatus&(~PreviousKeysStatus));
	JoystickManager_buttonsReleased = ((~KeysStatus)&PreviousKeysStatus);
}