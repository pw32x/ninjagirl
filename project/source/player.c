#include "player.h"
#include "SMSlib.h"
#include "animation_helpers.h"
#include "object_manager.h"
#include "scroll_manager.h"

void Player_Update(GameObject* player);
void Player_Draw(GameObject* player);

GameObject* Player_Create(const SpawnInfo* spawnInfo)
{
	ObjectManager_player.x = spawnInfo->startx;
	ObjectManager_player.y = spawnInfo->starty;
	ObjectManager_player.animation = spawnInfo->animation;
	ObjectManager_player.animationVdpTileIndex = *spawnInfo->animationVdpTileIndexPtr;
	ObjectManager_player.currentAnimationFrameIndex = 0;
	ObjectManager_player.currentAnimationFrame = ObjectManager_player.animation->frames[ObjectManager_player.currentAnimationFrameIndex];
	ObjectManager_player.animationTime = 0;
	ObjectManager_player.Update = Player_Update;
	ObjectManager_player.Draw = Player_Draw;

	return &ObjectManager_player;
}

void Player_Update(GameObject* player)
{
	/*
	gameObject->x++;
	gameObject->x %= 255;
*/
	u32 buttonState = SMS_getKeysHeld();

	if (buttonState & PORT_A_KEY_LEFT)
		player->x--;

	if (buttonState & PORT_A_KEY_RIGHT)
		player->x++;

	if (buttonState & PORT_A_KEY_UP)
		player->y--;

	if (buttonState & PORT_A_KEY_DOWN)
		player->y++;

	if (player->animationTime == player->currentAnimationFrame->frameTime)
	{
		player->currentAnimationFrameIndex++;

		if (player->currentAnimationFrameIndex == player->animation->numFrames)
			player->currentAnimationFrameIndex = 0;

		player->currentAnimationFrame = player->animation->frames[player->currentAnimationFrameIndex];
		player->animationTime = 0;
	}

	player->animationTime++;
}

void Player_Draw(GameObject* player)
{
	Animation_DrawFrame(player->currentAnimationFrame, 
						player->animationVdpTileIndex,
						player->x - ScrollManager_horizontalScroll, 
						player->y);
}

