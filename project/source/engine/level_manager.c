#include "level_manager.h"
#include "SMSlib.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/vdptile_manager.h"

void LevelManager_Init(const Level* level)
{
	// init systems
	ObjectManager_Init();
	VDPTileManager_Init();

	level->InitLevel();
	
	SMS_loadBGPalette(level->backgroundPalette);
	SMS_loadSpritePalette(level->spritePalette);
	

	// spawn the first object. If it's a spawner it'll take 
	// control of the rest of the object spawning.

	if (level->bootstrapSpawnInfo != NULL)
	{
		const SpawnInfo* spawnInfo = level->bootstrapSpawnInfo;
		spawnInfo->Object_Create(spawnInfo);
	}
}