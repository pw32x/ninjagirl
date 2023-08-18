#include "engine/spawn_manager.h"
#include "engine/object_utils.h"

void (*SpawnManager_Update)(void) = ObjectUtils_doNothing;