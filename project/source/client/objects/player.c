#include "player.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/draw_utils.h"
#include "engine/object_utils.h"
#include "engine/animation_utils.h"
#include "engine/resource_manager.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

//kunai
#include "client/objects/kunai.h"
#include "client/exported/kunai.h"

#include <stdio.h>

void Player_Update(GameObject* player);
BOOL Player_Draw(GameObject* player);
void Player_FireWeapon(GameObject* player);

typedef s32 POSITION;
typedef s16 POSITION_PIXEL;

#define PIXEL_TO_VIRTUAL(value) ((value) << 5) // 32 virtual pixels per on screen pixel
#define PIXEL_TO_TILE(value)    ((value) >> 3) // 8 pixels per tile
#define PIXEL_TO_BLOCK(value)    ((value) >> 4) // 16 pixels per block

#define VIRTUAL_TO_PIXEL(value) ((value) >> 5) // 32 virtual pixels per on screen pixel
#define VIRTUAL_TO_TILE(value)  ((value) >> 8) // 32 virtual pixels per pixel, 8 pixels per tile
#define VIRTUAL_TO_BLOCK(value)  ((value) >> 9) // 32 virtual pixels per pixel, 8 pixels per tile, 2 tiles per block

#define TILE_TO_PIXEL(value)    ((value) << 3) // 8 pixels per tile
#define TILE_TO_VIRTUAL(value)  ((value) << 8) // 64 virtual pixels per pixel, 8 pixels per tile
#define TILE_TO_BLOCK(value)    ((value) >> 1) // 2 tiles per block pixels per tile

#define BLOCK_TO_PIXEL(value)    ((value) << 4) // 16 pixels per block
#define BLOCK_TO_VIRTUAL(value)  ((value) << 9) // 32 virtual pixels per pixel, 16 pixels per block
#define BLOCK_TO_TILE(value)    ((value) << 1) // 2 tiles per block pixels per tile



#define P2V(value) PIXEL_TO_VIRTUAL(value)
#define P2T(value) PIXEL_TO_TILE(value)
#define P2B(value) PIXEL_TO_BLOCK(value)

#define V2P(value) VIRTUAL_TO_PIXEL(value)
#define V2T(value) VIRTUAL_TO_TILE(value)
#define V2B(value) VIRTUAL_TO_BLOCK(value)

#define T2V(value) TILE_TO_VIRTUAL(value)
#define T2P(value) TILE_TO_PIXEL(value)
#define T2B(value) TILE_TO_BLOCK(value)

#define B2V(value) BLOCK_TO_VIRTUAL(value)
#define B2P(value) BLOCK_TO_PIXEL(value)
#define B2T(value) BLOCK_TO_TILE(value)


#define TILE_EMPTY  0
#define TILE_SOLID  1
#define TILE_TOPSOLID  2
#define TILE_CLIMB  3
#define TILE_HURT  4
#define TILE_SLOPE45RIGHT  5
#define TILE_SLOPE45LEFT  6
#define TILE_SLOPE30RIGHT1  7
#define TILE_SLOPE30RIGHT2  8
#define TILE_SLOPE30LEFT1  9
#define TILE_SLOPE30LEFT2  10
#define TILE_SLOPE45RIGHTFLAT  11
#define TILE_SLOPE45LEFTFLAT  12
#define TILE_SLOPE30RIGHTFLAT  13
#define TILE_SLOPE30LEFTFLAT  14
#define TILE_SLOPEHALFHEIGHT  15
#define TILE_SLOPE15RIGHT1  16
#define TILE_SLOPE15RIGHT2  17
#define TILE_SLOPE15RIGHT3  18
#define TILE_SLOPE15RIGHT4  19
#define TILE_SLOPE15LEFT1  20
#define TILE_SLOPE15LEFT2  21
#define TILE_SLOPE15LEFT3  22
#define TILE_SLOPE15LEFT4  23
#define TILE_WATER  24

POSITION playerX;
POSITION playerY;
s16 playerSpeedX;
s16 playerSpeedY;

#define PLAYER_SPEED_X	48
#define PLAYER_SPEED_Y	32

#define PLAYER_GRAVITY	10
#define JUMP_SPEED 200

GameObject* Player_Create(const CreateInfo* createInfo)
{
	ObjectManager_player.x = createInfo->startX;
	ObjectManager_player.y = createInfo->startY;


	playerX = P2V(createInfo->startX);
	playerY = P2V(createInfo->startY);

	ObjectManager_player.Update = Player_Update;
	ObjectManager_player.Draw = Player_Draw;

	ObjectManager_player.rectLeft = -8;
	ObjectManager_player.rectTop = -12;
	ObjectManager_player.rectRight = 8;
	ObjectManager_player.rectBottom = 16;

	//AnimationUtils_setupAnimation(&ObjectManager_player, (const AnimationBatched*)spawnInfo->payload, *((u8*)spawnInfo->additionalPayload));

	ResourceManager_SetupResource(&ObjectManager_player, createInfo->resource);

	//ObjectManager_player.animationVdpTileIndex = 0xff;

	//Player_FireWeapon(&ObjectManager_player);
	//Player_FireWeapon(&ObjectManager_player);
	//Player_FireWeapon(&ObjectManager_player);

		SMS_setBGPaletteColor(1, 0xffff);

	return &ObjectManager_player;
}

void Player_FireWeapon(GameObject* player)
{
	CreateInfo createInfo = 
	{ 
		player->x, 
		player->y, 
		(const void*)&kunai, 
	};

	GameObject* kunai = Kunai_Create(&createInfo);

	kunai->speedx = 3;
	kunai->speedy = 0;
}

void Player_UpdateX(void)
{
	playerX += playerSpeedX;

	POSITION xSensor = playerX;
	s16 offset = 0;

	if (playerSpeedX > 0)
	{
		offset = P2V(ObjectManager_player.rectRight);
	}
	else if (playerSpeedX < 0)
	{
		offset = P2V(ObjectManager_player.rectLeft);
	}

	xSensor += offset;

	s16 blockX = V2B(xSensor);
	s16 blockY = V2B(playerY + P2V(ObjectManager_player.rectBottom - 1));

	u8 tileType = ScrollManager_terrainMap[blockX + (blockY * ScrollManager_mapWidth)];

	if (tileType != TILE_EMPTY)
	{
		if (playerSpeedX < 0)
			blockX++;

		playerX = B2V(blockX) - offset;
		playerSpeedX = 0;
		return;
	}

	blockY = V2B(playerY + P2V(ObjectManager_player.rectTop));

	tileType = ScrollManager_terrainMap[blockX + (blockY * ScrollManager_mapWidth)];

	if (tileType != TILE_EMPTY)
	{
		if (playerSpeedX < 0)
			blockX++;

		playerX = B2V(blockX) - offset;
		playerSpeedX = 0;
		return;
	}
}

void Player_UpdateY(void)
{
	playerSpeedY += PLAYER_GRAVITY;

	playerY += playerSpeedY;

	// falling
	if (playerSpeedY > 0)
	{
		POSITION ySensor = playerY + P2V(ObjectManager_player.rectBottom);

		s16 blockX = V2B(playerX);
		s16 blockY = V2B(ySensor);

		u8 tileType = ScrollManager_terrainMap[blockX + (blockY * ScrollManager_mapWidth)];

		if (tileType != TILE_EMPTY)
		{
			playerY = B2V(blockY) - P2V(ObjectManager_player.rectBottom);
			playerSpeedY = 0;
		}
	}
	else if (playerSpeedY < 0) // jump up
	{
		POSITION ySensor = playerY + P2V(ObjectManager_player.rectTop);
		s16 blockX = V2B(playerX);
		s16 blockY = V2B(ySensor);

		u8 tileType = ScrollManager_terrainMap[blockX + (blockY * ScrollManager_mapWidth)];

		if (tileType != TILE_EMPTY)
		{
			playerY = B2V(blockY + 1) - P2V(ObjectManager_player.rectTop);
			playerSpeedY = 0;
		}
	}

	//char output[255];
	//sprintf(output, "%d, %d, %d     ", blockX, blockY, tileType);
	//SMS_printatXY(1, 0, output); 
	//
	//sprintf(output, "%d", ScrollManager_mapWidth);
	//SMS_printatXY(1, 1, output); 
}

void Player_Update(GameObject* player)
{
	/*
	gameObject->x++;
	gameObject->x %= 255;
*/
	
	u32 buttonState = SMS_getKeysHeld();

	if (buttonState & PORT_A_KEY_LEFT)
		playerSpeedX = -PLAYER_SPEED_X;
	else if (buttonState & PORT_A_KEY_RIGHT)
		playerSpeedX = PLAYER_SPEED_X;
	else
		playerSpeedX = 0;

	//if (buttonState & PORT_A_KEY_UP)
	//	playerY -= PLAYER_SPEED_Y;
	//
	//if (buttonState & PORT_A_KEY_DOWN)
	//	playerY += PLAYER_SPEED_Y;
	

	u32 buttonsPressed = SMS_getKeysPressed();

	if (buttonsPressed & PORT_A_KEY_1)
		Player_FireWeapon(player);

	if (buttonsPressed & PORT_A_KEY_2)
		playerSpeedY -= JUMP_SPEED;

	Player_UpdateX();
	Player_UpdateY();

	player->x = V2P(playerX);
	player->y = V2P(playerY);

	ObjectManager_player.UpdateAnimation(player);
}

BOOL Player_Draw(GameObject* object)
{
	DRAWUTILS_SETUP_BATCH(object->x - ScrollManager_horizontalScroll,
						  object->y,
						  object->currentAnimationBatchedFrame->spriteBatch,
						  *object->animationBatched->vdpLocation);

	// why would the player sprite ever be clipped?
	DrawUtils_DrawBatched();

	return TRUE;
}

