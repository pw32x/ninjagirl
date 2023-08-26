#include "everything_spawner.h"
#include "engine/spawn_manager.h"
#include "engine/object_utils.h"

GameObject* EverythingSpawner_Create(const SpawnInfo* spawnInfo)
{
	const SpawnInfo* spawnsRunner = (const SpawnInfo*)spawnInfo->payload;
	u32 spawnsCount = spawnInfo->additionalPayload;

	for (u16 loop = 0; loop < spawnsCount; loop++)
	{
		spawnsRunner->Object_Create(spawnsRunner);
		spawnsRunner++;
	}

	SpawnManager_Update = ObjectUtils_doNothing;

	return NULL;
}



