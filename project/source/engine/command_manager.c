#include "engine/command_manager.h"
#include "engine/object_utils.h"

void (*CommandManager_Update)(void) = ObjectUtils_doNothing;