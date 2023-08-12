#include "object_manager.h"
#include "SMSlib.h"
#include "player.h"

GameObject ObjectManager_player;

void ObjectManager_Update(void)
{
	ObjectManager_player.Update(&ObjectManager_player);
}

void ObjectManager_Draw(void)
{
	SMS_initSprites();

	ObjectManager_player.Draw(&ObjectManager_player);
}