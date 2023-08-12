#include "player.h"
#include "SMSlib.h"
#include "ninja_girl.h"

GameObject player;

void Player_Update(GameObject* player);

GameObject* Player_Create(const Animation* animation)
{
	player.x = 122;
	player.y = 88;
	player.animation = animation;
	player.currentAnimationFrameIndex = 0;
	player.currentAnimationFrame = animation->frames[player.currentAnimationFrameIndex];
	player.animationTime = 0;
	player.animationVdpTileIndex = 0;	
	player.Update = Player_Update;

	return &player;
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


