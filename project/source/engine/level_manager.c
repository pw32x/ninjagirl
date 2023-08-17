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
	
	const SpawnInfo* spawnsRunner = level->levelSpawns;
	u16 spawnsCount = level->levelSpawnsCount;

	for (u16 loop = 0; loop < spawnsCount; loop++)
	{
		spawnsRunner->Object_Create(spawnsRunner);
		spawnsRunner++;
	}
}