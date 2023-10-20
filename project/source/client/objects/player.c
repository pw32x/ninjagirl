#include "player.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/draw_utils.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"
#include "engine/resource_manager.h"
#include "engine/math_utils.h"
#include "engine/terrain_manager.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

//kunai
#include "client/objects/kunai.h"
#include "client/exported/kunai.h"
#include "client/exported/ninja_girl.h"

#include <stdio.h>

#define PLAYER_SPEED_X	24
#define PLAYER_SPEED_Y	16

void Player_Update(GameObject* player);
BOOL Player_Draw(GameObject* player);
void Player_FireWeapon(GameObject* player);


POSITION playerX;
POSITION playerY;
s16 playerSpeedX;
s16 playerSpeedY;

u8 playerState;

u8 isPlayerOnGround;
u8 isPlayerMoving;
u8 isPlayerShooting;


#define PLAYER_GRAVITY	5
#define JUMP_SPEED 100

#define PLAYER_STATE_STAND	0
#define PLAYER_STATE_RUN	1
#define PLAYER_STATE_FALL	2
#define PLAYER_STATE_JUMP	3
#define PLAYER_STATE_DUCK	4

u8 stateChanged;
u8 animationChanged;

void setPlayerAnimation(void)
{
	u8 flipped = ObjectManager_player.flipped;
	animationChanged = TRUE;
	if (isPlayerShooting)
	{
		AnimationUtils_setStreamedBatchedAnimationFrame(&ObjectManager_player, 
														flipped ? NINJA_GIRL_SHOOT_LEFT_FRAME_INDEX : NINJA_GIRL_SHOOT_RIGHT_FRAME_INDEX);

		return;
	}

	switch (playerState)
	{
	case PLAYER_STATE_STAND:
		AnimationUtils_setStreamedBatchedAnimationFrame(&ObjectManager_player, 
														flipped ? NINJA_GIRL_STAND_LEFT_FRAME_INDEX : NINJA_GIRL_STAND_RIGHT_FRAME_INDEX);
		break;
	case PLAYER_STATE_RUN:
		AnimationUtils_setStreamedBatchedAnimationFrame(&ObjectManager_player, 
														flipped ? NINJA_GIRL_RUN_LEFT_FRAME_INDEX : NINJA_GIRL_RUN_RIGHT_FRAME_INDEX);
		break;
	case PLAYER_STATE_FALL:
		AnimationUtils_setStreamedBatchedAnimationFrame(&ObjectManager_player, 
														flipped ? NINJA_GIRL_FALL_LEFT_FRAME_INDEX : NINJA_GIRL_FALL_RIGHT_FRAME_INDEX);
		break;
	case PLAYER_STATE_JUMP:
		AnimationUtils_setStreamedBatchedAnimationFrame(&ObjectManager_player, 
														flipped ? NINJA_GIRL_JUMP_LEFT_FRAME_INDEX : NINJA_GIRL_JUMP_RIGHT_FRAME_INDEX);
		break;
	case PLAYER_STATE_DUCK:
		AnimationUtils_setStreamedBatchedAnimationFrame(&ObjectManager_player, 
														flipped ? NINJA_GIRL_DUCK_LEFT_FRAME_INDEX : NINJA_GIRL_DUCK_RIGHT_FRAME_INDEX);
		break;
	}
}

void setPlayerState(u8 newState)
{
	stateChanged = FALSE;

	if (playerState == newState)
	{
		return;
	}

	playerState = newState;

	if (!isPlayerShooting)
		setPlayerAnimation();

	stateChanged = TRUE;
}

#define PLAYER_ANIMATION_FRAME_STAND 0
#define PLAYER_ANIMATION_FRAME_JUMP 1

GameObject* Player_Create(const CreateInfo* createInfo)
{
	ObjectManager_player.x = createInfo->startX;
	ObjectManager_player.y = createInfo->startY;


	playerX = P2V(createInfo->startX);
	playerY = P2V(createInfo->startY);

	ObjectManager_player.Update = Player_Update;
	ObjectManager_player.Draw = Player_Draw;

	ObjectManager_player.rectLeft = -3;
	ObjectManager_player.rectTop = -12;
	ObjectManager_player.rectRight = 3;
	ObjectManager_player.rectBottom = 16;

	ObjectManager_player.flipped = FALSE;

	playerSpeedX = 0;

	//AnimationUtils_setupAnimation(&ObjectManager_player, (const AnimationBatched*)spawnInfo->payload, *((u8*)spawnInfo->additionalPayload));

	ResourceManager_SetupResource(&ObjectManager_player, createInfo->resource);

	//ObjectManager_player.animationVdpTileIndex = 0xff;


	//SMS_setBGPaletteColor(1, 0xffff);

	ObjectManager_QueueVDPDraw(&ObjectManager_player, AnimationUtils_UpdateStreamedBatchedAnimationFrame);

	return &ObjectManager_player;
}

void Player_FireWeapon(GameObject* player)
{
	CreateInfo createInfo = 
	{ 
		player->x + (ObjectManager_player.flipped ? -10 : 10), 
		player->y - 7, 
		(const void*)&kunai, 
	};

	GameObject* kunai = Kunai_Create(&createInfo);

	kunai->speedx = ObjectManager_player.flipped ? -3 : 3;
	kunai->speedy = 0;

	if (ObjectManager_player.flipped)
		AnimationUtils_setBatchedAnimationFrame(kunai, 1);

	isPlayerShooting = TRUE;
	stateChanged = TRUE;
	setPlayerAnimation();
}

u32 buttonState;
u32 buttonsPressed;
u32 buttonsReleased;

void Player_UpdateX(void)
{
	s16 offset = 0;

	POSITION projectedX = playerX + playerSpeedX;

	POSITION xSensor = projectedX;

	if (playerSpeedX > 0)
	{
		offset = P2V(ObjectManager_player.rectRight + 1);
	}
	else if (playerSpeedX < 0)
	{
		offset = P2V(ObjectManager_player.rectLeft);
	}

	xSensor += offset;

	POSITION horzScroll = P2V(ScrollManager_horizontalScroll + 16);

	if (xSensor < horzScroll)
	{
		playerX = horzScroll - offset;
		playerSpeedX = projectedX - playerX;
		return;
	}

	s16 blockX = V2B(xSensor);
	s16 blockY = V2B(playerY + P2V(ObjectManager_player.rectTop));
		

	if (blockY < 0)
		goto update_x;

	u16 tileType = GET_TERRAIN(blockX, blockY);

	if (tileType == TERRAIN_SOLID)
	{
		if (playerSpeedX < 0)
			blockX++;

		playerX = B2V(blockX) - offset;
		playerSpeedX = projectedX - playerX;
		return;
	}

	blockY = V2B(playerY + P2V(ObjectManager_player.rectBottom - 1));

	if (blockY < 0)
		goto update_x;

	tileType = GET_TERRAIN(blockX, blockY);

	if (tileType == TERRAIN_SOLID)
	{
		if (playerSpeedX < 0)
			blockX++;

		playerX = B2V(blockX) - offset;
		playerSpeedX = projectedX - playerX;
		return;
	}
	
	blockY = V2B(playerY + P2V((ObjectManager_player.rectBottom + ObjectManager_player.rectTop) >> 1));

	if (blockY < 0)
		goto update_x;

	tileType = GET_TERRAIN(blockX, blockY);

	if (tileType == TERRAIN_SOLID)
	{
		if (playerSpeedX < 0)
			blockX++;

		playerX = B2V(blockX) - offset;
		playerSpeedX = projectedX - playerX;
		return;
	}
	
update_x:
	playerX = projectedX;
}

void Player_UpdateY(void)
{
	playerSpeedY += PLAYER_GRAVITY;

	playerY += playerSpeedY;

	s16 blockX1 = V2B(playerX + P2V(ObjectManager_player.rectRight));
	s16 blockX2 = V2B(playerX + P2V(ObjectManager_player.rectLeft));

	// falling
	if (playerSpeedY > 0)
	{
		POSITION ySensor = playerY + P2V(ObjectManager_player.rectBottom);

		s16 blockY = V2B(ySensor);

		if (blockY < 0)
			return;

		u16 tileType = GET_TERRAIN(blockX1, blockY);

		if (tileType == TERRAIN_SOLID || tileType == TERRAIN_TOPSOLID)
		{
			playerY = B2V(blockY) - P2V(ObjectManager_player.rectBottom);
			playerSpeedY = 0;
			isPlayerOnGround = TRUE;

			

			if (buttonState & PORT_A_KEY_DOWN && 
				isPlayerOnGround)
			{
				setPlayerState(PLAYER_STATE_DUCK);
			}
			else
			{
				if (isPlayerMoving) 
					setPlayerState(PLAYER_STATE_RUN);
				else 
					setPlayerState(PLAYER_STATE_STAND);
			}
			
			return;
		}

		tileType = GET_TERRAIN(blockX2, blockY);

		if (tileType == TERRAIN_SOLID || tileType == TERRAIN_TOPSOLID)
		{
			playerY = B2V(blockY) - P2V(ObjectManager_player.rectBottom);
			playerSpeedY = 0;
			isPlayerOnGround = TRUE;

			if (buttonState & PORT_A_KEY_DOWN && 
				isPlayerOnGround)
			{
				setPlayerState(PLAYER_STATE_DUCK);
			}

			if (playerState != PLAYER_STATE_DUCK && isPlayerMoving) 
				setPlayerState(PLAYER_STATE_RUN);
			else 
				setPlayerState(PLAYER_STATE_STAND);

			return;
		}

		isPlayerOnGround = FALSE;
		setPlayerState(PLAYER_STATE_FALL);
	}
	else if (playerSpeedY < 0) // jump up
	{
		isPlayerOnGround = FALSE;

		POSITION ySensor = playerY + P2V(ObjectManager_player.rectTop);

		s16 blockY = V2B(ySensor);

		if (blockY < 0)
			return;

		u16 tileType = GET_TERRAIN(blockX1, blockY);

		if (tileType == TERRAIN_SOLID)
		{
			playerY = B2V(blockY + 1) - P2V(ObjectManager_player.rectTop);
			playerSpeedY = 0;
			setPlayerState(PLAYER_STATE_FALL);
			return;
		}

		tileType = GET_TERRAIN(blockX2, blockY);

		if (tileType == TERRAIN_SOLID)
		{
			playerY = B2V(blockY + 1) - P2V(ObjectManager_player.rectTop);
			playerSpeedY = 0;
			setPlayerState(PLAYER_STATE_FALL);
			return;
		}


	}

	//char output[255];
	//sprintf(output, "%d, %d, %d     ", blockX, blockY, tileType);
	//SMS_printatXY(1, 0, output); 
	//
	//sprintf(output, "%d", MapManager_mapWidth);
	//SMS_printatXY(1, 1, output); 
}

#define NOT_MOVING		0
#define MOVING_LEFT		1
#define MOVING_RIGHT	2

void Player_Update(GameObject* player)
{
	/*
	gameObject->x++;
	gameObject->x %= 255;
*/
	u8 oldIsPlayerMoving = isPlayerMoving;
	
	isPlayerMoving = NOT_MOVING;

	buttonState = SMS_getKeysStatus();
	buttonsPressed = SMS_getKeysPressed();
	buttonsReleased = SMS_getKeysReleased();

	//if (buttonsReleased & PORT_A_KEY_DOWN && playerState == PLAYER_STATE_DUCK)
	//{
	//	setPlayerState(PLAYER_STATE_STAND);
	//}

	u8 flippedChanged = FALSE;
	
	if (playerState == PLAYER_STATE_DUCK)
	{
		playerSpeedX = 0;

		if (buttonState & PORT_A_KEY_LEFT)
		{
			if (!ObjectManager_player.flipped)
			{
				ObjectManager_player.flipped = TRUE;
				flippedChanged = TRUE;
				setPlayerAnimation();
			}
		}
		else if (buttonState & PORT_A_KEY_RIGHT)
		{
			if (ObjectManager_player.flipped)
			{
				ObjectManager_player.flipped = FALSE;
				flippedChanged = TRUE;
				setPlayerAnimation();
			}
		}
	}

	else
	{
		if (buttonState & PORT_A_KEY_LEFT)
		{
			ObjectManager_player.flipped = TRUE;

			if (isPlayerShooting && isPlayerOnGround)
				playerSpeedX = 0;
			else
				playerSpeedX = -PLAYER_SPEED_X;

			isPlayerMoving = MOVING_LEFT;

			// if state is not run
			// if on ground
			//		setstate(run)
			//			set animation

			//if (isPlayerOnGround)
			//	setPlayerState(PLAYER_STATE_RUN);
		}
		else if (buttonState & PORT_A_KEY_RIGHT)
		{
			ObjectManager_player.flipped = FALSE;

			if (isPlayerShooting && isPlayerOnGround)
				playerSpeedX = 0;
			else
				playerSpeedX = PLAYER_SPEED_X;

			isPlayerMoving = MOVING_RIGHT;

			//if (isPlayerOnGround)
			//	setPlayerState(PLAYER_STATE_RUN);
		}
		else
		{
			playerSpeedX = 0;

			//if (isPlayerOnGround)
			//	setPlayerState(PLAYER_STATE_STAND);
		}

		if (oldIsPlayerMoving != isPlayerMoving && !isPlayerShooting)
			setPlayerAnimation();
	}

	if (buttonsPressed & PORT_A_KEY_1  && !isPlayerShooting)
		Player_FireWeapon(player);

	if (buttonsPressed & PORT_A_KEY_2  && 
		isPlayerOnGround &&
		!isPlayerShooting)
	{
		playerSpeedY -= JUMP_SPEED;

		if (isPlayerOnGround && playerState != PLAYER_STATE_JUMP)
			setPlayerState(PLAYER_STATE_JUMP);
	}


	Player_UpdateX();
	Player_UpdateY();

	player->x = V2P(playerX);
	player->y = V2P(playerY);

	//char output[255];
	//sprintf(output, " %d, %d     ", player->x, playerX);
	//SMS_printatXY(1, 0, output); 
	//
	//sprintf(output, "%d", MapManager_mapWidth);
	//SMS_printatXY(1, 1, output); 

	//char output[255];
	//sprintf(output, 
	//		" %d, %d, %d   ", 
	//		ObjectManager_player.currentStreamedBatchedAnimationFrame->frameTime,
	//		ObjectManager_player.currentStreamedBatchedAnimationFrame->tileIndex,
	//		ObjectManager_player.animationTime);
	//SMS_printatXY(1, 0, output); 

	u8 updateResult = ObjectManager_player.UpdateAnimation(&ObjectManager_player);

	if (isPlayerShooting && updateResult == ANIMATION_FINISHED)
	{
		isPlayerShooting = FALSE;
		setPlayerAnimation();
	}

	if (updateResult == ANIMATION_CHANGED_FRAME || 
		stateChanged ||
		flippedChanged ||
		animationChanged ||
		oldIsPlayerMoving != isPlayerMoving)
	{
		ObjectManager_QueueVDPDraw(&ObjectManager_player, AnimationUtils_UpdateStreamedBatchedAnimationFrame);
	}

	animationChanged = FALSE;
}

BOOL Player_Draw(GameObject* object)
{
	DRAWUTILS_SETUP_BATCH(object->x - ScrollManager_horizontalScroll,
						  object->y,
						  object->currentStreamedBatchedAnimationFrame->batchedSprites,
						  *object->streamedBatchedAnimation->vdpLocation);

	// why would the player sprite ever be clipped?
	DrawUtils_DrawBatched();

	return TRUE;
}

