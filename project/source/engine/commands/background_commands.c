#include "background_commands.h"
#include "engine/palette_types.h"

#include "smslib.h"

void SetBackgroundVerticalScroll(s16 value)
{
	SMS_setBGScrollY(value);
}