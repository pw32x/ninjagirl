#include "level_manager.h"
#include "SMSlib.h"
#include "animation_helpers.h"
#include "scroll_manager.h"
#include "vdptile_manager.h"

void LevelManager_Init(const Level* level)
{
	// init systems
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