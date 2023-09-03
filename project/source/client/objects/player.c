#include "player.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/draw_utils.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"

#include "client/generated/sprite_vdp_locations.h"

//kunai
#include "client/objects/kunai.h"
#include "client/exported/kunai.h"

void Player_Update(GameObject* player);
void Player_Draw(GameObject* player);
void Player_FireWeapon(GameObject* player);

GameObject* Player_Create(const SpawnInfo* spawnInfo)
{
	ObjectManager_player.x = spawnInfo->startX;
	ObjectManager_player.y = spawnInfo->startY;
	ObjectManager_player.Update = Player_Update;
	ObjectManager_player.Draw = Player_Draw;

	ObjectManager_player.rectLeft = -8;
	ObjectManager_player.rectTop = -12;
	ObjectManager_player.rectRight = 8;
	ObjectManager_player.rectBottom = 16;

	AnimationUtils_setupAnimation(&ObjectManager_player, (const AnimationBatched*)spawnInfo->payload, *((u8*)spawnInfo->additionalPayload));

	//Player_FireWeapon(&ObjectManager_player);
	//Player_FireWeapon(&ObjectManager_player);
	//Player_FireWeapon(&ObjectManager_player);

	return &ObjectManager_player;
}

void Player_FireWeapon(GameObject* player)
{
	SpawnInfo spawnInfo = 
	{ 
		player->x, 
		player->y, 
		(const void*)&kunai, 
		(u32)&kunai_spriteVdpLocation, 
		Kunai_Create 
	};

	GameObject* kunai = Kunai_Create(&spawnInfo);

	kunai->speedx = 3;
	kunai->speedy = 0;
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

	u32 buttonsPressed = SMS_getKeysPressed();

	if (buttonsPressed & PORT_A_KEY_1)
		Player_FireWeapon(player);

	AnimationUtils_updateAnimation(player);
}

void Player_Draw(GameObject* object)
{
	DRAWUTILS_SETUP_BATCH(object->x - ScrollManager_horizontalScroll,
						  object->y,
						  object->currentAnimationFrame->spriteBatch,
						  object->animationVdpTileIndex);

	// why would the player sprite ever be clipped?
	DrawUtils_DrawBatched();
}

