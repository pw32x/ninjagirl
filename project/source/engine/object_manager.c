#include "object_manager.h"
#include "SMSlib.h"
#include "scroll_manager.h"

GameObject ObjectManager_player;

void ObjectManager_Update(void)
{
	ObjectManager_player.Update(&ObjectManager_player);
	ScrollManager_Update(&ObjectManager_player);
	//SpawnManager_Update(); // uses ScrollManager_horizontalScroll
}

void ObjectManager_Draw(void)
{
	SMS_initSprites();

	ObjectManager_player.Draw(&ObjectManager_player);
}