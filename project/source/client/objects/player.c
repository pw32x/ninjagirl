#include "player.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/draw_utils.h"

void Player_Update(GameObject* player);
void Player_Draw(GameObject* player);

void Player_Create(const SpawnInfo* spawnInfo)
{
	ObjectManager_player.x = spawnInfo->startX;
	ObjectManager_player.y = spawnInfo->startY;
	ObjectManager_player.animation = (const Animation*)spawnInfo->payload;
	ObjectManager_player.animationVdpTileIndex = *((u8*)spawnInfo->additionalPayload);
	ObjectManager_player.currentAnimationFrameIndex = 0;
	ObjectManager_player.currentAnimationFrame = ObjectManager_player.animation->frames[ObjectManager_player.currentAnimationFrameIndex];
	ObjectManager_player.animationTime = ObjectManager_player.currentAnimationFrame->frameTime;
	ObjectManager_player.Update = Player_Update;
	ObjectManager_player.Draw = Player_Draw;
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

void Player_Draw(GameObject* object)
{
	DRAWUTILS_SETUP(ObjectManager_playerLeft,
					ObjectManager_playerTop,
					object->currentAnimationFrame->numSprites, 
					object->currentAnimationFrame->sprites,
					object->animationVdpTileIndex);

	if (ObjectManager_playerLeft < SCREEN_LEFT || 
		ObjectManager_playerTop < SCREEN_TOP ||
		ObjectManager_playerRight > SCREEN_RIGHT ||
		ObjectManager_playerBottom > SCREEN_BOTTOM)
	{
		DrawUtils_DrawClipped();
	}
	else
	{
		DrawUtils_Draw();
	}
}

