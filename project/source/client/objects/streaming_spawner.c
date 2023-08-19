#include "streaming_spawner.h"
#include "engine/base_defines.h"
#include "engine/scroll_manager.h"
#include "engine/spawn_manager.h"
#include "engine/object_utils.h"

u16 StreamingSpawner_scrollX;
const SpawnInfo* StreamingSpawner_currentSpawnInfo;
u32 StreamingSpawner_counter;

void StreamingSpawner_Update(void);

void StreamingSpawner_Create(const SpawnInfo* spawnInfo)
{
	StreamingSpawner_scrollX = 0;

	StreamingSpawner_currentSpawnInfo = (const SpawnInfo*)spawnInfo->payload;
	StreamingSpawner_counter = spawnInfo->additionalPayload;

	while (StreamingSpawner_counter && StreamingSpawner_currentSpawnInfo->startX < SCREEN_WIDTH)
	{
		StreamingSpawner_currentSpawnInfo->Object_Create(StreamingSpawner_currentSpawnInfo);
		StreamingSpawner_currentSpawnInfo++;
		StreamingSpawner_counter--;
	}

	SpawnManager_Update = StreamingSpawner_Update;
}


void StreamingSpawner_Update(void)
{
	StreamingSpawner_scrollX += ScrollManager_speedX;

	while (StreamingSpawner_counter && StreamingSpawner_currentSpawnInfo->startX < StreamingSpawner_scrollX + SCREEN_WIDTH)
	{
		StreamingSpawner_currentSpawnInfo->Object_Create(StreamingSpawner_currentSpawnInfo);
		StreamingSpawner_currentSpawnInfo++;
		StreamingSpawner_counter--;
	}
}