#include "joystick_manager.h"

#include "SMSlib.h"

u32 JoystickManager_buttonState;
u32 JoystickManager_buttonsPressed;
u32 JoystickManager_buttonsReleased;

#ifdef WIN32
unsigned int KeysStatus;
unsigned int PreviousKeysStatus;
#else
extern volatile unsigned int KeysStatus;
extern volatile unsigned int PreviousKeysStatus;
#endif

void JoystickManager_Update(void)
{
	JoystickManager_buttonState = KeysStatus;
	JoystickManager_buttonsPressed = (KeysStatus&(~PreviousKeysStatus));
	JoystickManager_buttonsReleased = ((~KeysStatus)&PreviousKeysStatus);
}