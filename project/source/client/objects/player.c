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
#include "engine/joystick_manager.h"
#include "engine/createinfo_types.h"

// music and sfx
#include "PSGlib.h"
#include "client/generated/bank2.h"

#include "client/managers/weapon_manager.h"

//bullet
#include "client/objects/bullet.h"
#include "client/exported/animations/streamed/gun_girl.h"


#include "client/generated/gameobjecttemplates/gameobject_templates.h"

#include <stdio.h>

BOOL Player_Draw(GameObject* player);
void Player_FireWeapon(GameObject* player);


s16 playerX;
s16 playerY;
s16 playerSpeedX;
s16 playerSpeedY;

u8 playerState;

u16 jumpPressCounter;
u8 jumpWhenLanding;
u8 canStillJumpFrames;
u8 pointingUp;
u8 pointingDown;

#define NUM_FRAMES_AFTER_LEAVING_LEDGE_TO_JUMP	4
#define NUM_FRAMES_JUMP_BUFFER_AFTER_LANDING	7

u8 isPlayerShooting;

#define PLAYER_SPEED_X	24
#define PLAYER_GRAVITY	4
#define PLAYER_GRAVITY_HEAVY 14
#define JUMP_SPEED 81

#define PLAYER_STATE_STAND		0
#define PLAYER_STATE_RUN		1
#define PLAYER_STATE_FALL		2
#define PLAYER_STATE_JUMP		3
#define PLAYER_STATE_DUCK		4
#define PLAYER_STATE_NOTHING	5
#define PLAYER_NUM_STATES		6

void Player_Update(GameObject* player);
void Player_UpdateStand(GameObject* player);
void Player_UpdateRun(GameObject* player);
void Player_UpdateFall(GameObject* player);
void Player_UpdateJump(GameObject* player);
void Player_UpdateDuck(GameObject* player);

ObjectFunctionType player_SubUpdate;

const ObjectFunctionType playerStateFunctions[PLAYER_NUM_STATES] = 
{
	Player_UpdateStand,
	Player_UpdateRun,
	Player_UpdateFall,
	Player_UpdateJump,
	Player_UpdateDuck,
	ObjectUtils_gameObjectDoNothing
};

u8 updateAnimationStream = FALSE;

void setPlayerAnimation(void)
{
	u8 flipped = ObjectManager_player.flipped;

	switch (playerState)
	{
	case PLAYER_STATE_STAND:
		if (!pointingUp)
			AnimationUtils_setBatchedAnimationFrame(&ObjectManager_player, 
													flipped ? GUN_GIRL_STAND_LEFT_FRAME_INDEX : GUN_GIRL_STAND_RIGHT_FRAME_INDEX);
		else
			AnimationUtils_setBatchedAnimationFrame(&ObjectManager_player, 
													flipped ? GUN_GIRL_STAND_LEFT_UP_FRAME_INDEX : GUN_GIRL_STAND_RIGHT_UP_FRAME_INDEX);
		break;
	case PLAYER_STATE_RUN:
		if (!pointingUp)
			AnimationUtils_setBatchedAnimationFrame(&ObjectManager_player, 
													flipped ? GUN_GIRL_RUN_LEFT_FRAME_INDEX : GUN_GIRL_RUN_RIGHT_FRAME_INDEX);
		else
			AnimationUtils_setBatchedAnimationFrame(&ObjectManager_player, 
													flipped ? GUN_GIRL_RUN_LEFT_UP_FRAME_INDEX : GUN_GIRL_RUN_RIGHT_UP_FRAME_INDEX);

		break;
	case PLAYER_STATE_FALL:
		if (pointingUp)
			AnimationUtils_setBatchedAnimationFrame(&ObjectManager_player, 
													flipped ? GUN_GIRL_FALL_LEFT_UP_FRAME_INDEX : GUN_GIRL_FALL_RIGHT_UP_FRAME_INDEX);
		else if (pointingDown)
			AnimationUtils_setBatchedAnimationFrame(&ObjectManager_player, 
													flipped ? GUN_GIRL_SHOOT_DOWN_LEFT_FRAME_INDEX : GUN_GIRL_SHOOT_DOWN_RIGHT_FRAME_INDEX);
		else
			AnimationUtils_setBatchedAnimationFrame(&ObjectManager_player, 
													flipped ? GUN_GIRL_FALL_LEFT_FRAME_INDEX : GUN_GIRL_FALL_RIGHT_FRAME_INDEX);
		break;
	case PLAYER_STATE_JUMP:
		if (pointingUp)
			AnimationUtils_setBatchedAnimationFrame(&ObjectManager_player, 
													flipped ? GUN_GIRL_JUMP_LEFT_UP_FRAME_INDEX : GUN_GIRL_JUMP_RIGHT_UP_FRAME_INDEX);
		else if (pointingDown)
			AnimationUtils_setBatchedAnimationFrame(&ObjectManager_player, 
													flipped ? GUN_GIRL_SHOOT_DOWN_LEFT_FRAME_INDEX : GUN_GIRL_SHOOT_DOWN_RIGHT_FRAME_INDEX);
		else
			AnimationUtils_setBatchedAnimationFrame(&ObjectManager_player, 
													flipped ? GUN_GIRL_JUMP_LEFT_FRAME_INDEX : GUN_GIRL_JUMP_RIGHT_FRAME_INDEX);

		break;
	case PLAYER_STATE_DUCK:
		AnimationUtils_setBatchedAnimationFrame(&ObjectManager_player, 
												flipped ? GUN_GIRL_DUCK_LEFT_FRAME_INDEX : GUN_GIRL_DUCK_RIGHT_FRAME_INDEX);
		break;
	}

	updateAnimationStream = TRUE;
}

void setPlayerState(u8 newState)
{
	playerState = newState;

	player_SubUpdate = playerStateFunctions[playerState];

	switch (playerState)
	{
	case PLAYER_STATE_STAND:
		playerSpeedX = 0;
		playerSpeedY = 0;
		break;
	case PLAYER_STATE_RUN:
		playerSpeedY = 0;
		break;
	case PLAYER_STATE_FALL:
		break;
	case PLAYER_STATE_JUMP:
		jumpWhenLanding = FALSE;
		playerSpeedY -= JUMP_SPEED;
		break;
	case PLAYER_STATE_DUCK:
		playerSpeedX = 0;
		playerSpeedY = 0;
		break;
	}
	SMS_mapROMBank(ObjectManager_player.resourceInfo->bankNumber);
	setPlayerAnimation();
}

GameObject* Player_Init(GameObject* object, const CreateInfo* createInfo)
{
	jumpPressCounter = 0;
	jumpWhenLanding = FALSE;

	UNUSED(createInfo);
	playerX = P2V(object->x);
	playerY = P2V(object->y);

	ObjectManager_player.Update = Player_Update;
	ObjectManager_player.Draw = Player_Draw;
	ObjectManager_player.flipped = FALSE;

	updateAnimationStream = FALSE;

	playerSpeedX = 0;
	playerSpeedY = 0;
	setPlayerState(PLAYER_STATE_STAND);

	return &ObjectManager_player;
}

void Player_FireWeapon(GameObject* player)
{
	s8 offset = (playerState == PLAYER_STATE_DUCK) ? 3 : -4;

	if (pointingUp)
	{
		WeaponManager_FireWeaponVertical(player->x + (ObjectManager_player.flipped ? -5 : 5), 
										 player->y - 19,
										 FALSE);
	}
	else if (pointingDown)
	{
		WeaponManager_FireWeaponVertical(player->x + (ObjectManager_player.flipped ? -5 : 5), 
										 player->y + 12,
										 TRUE);
	}
	else
	{
		WeaponManager_FireWeapon(player->x + (ObjectManager_player.flipped ? -13 : 13), 
								 player->y + offset,
								 ObjectManager_player.flipped);
	}
}

void Player_UpdateX(void)
{
	s16 offset = 0;

	s16 projectedX = playerX + playerSpeedX;

	s16 xSensor = projectedX;

	if (!ObjectManager_player.flipped)
	{
		offset = P2V(ObjectManager_player.rectRight + 1);
	}
	else
	{
		offset = P2V(ObjectManager_player.rectLeft);
	}

	xSensor += offset;

	s16 horzScroll = P2V(ScrollManager_horizontalScroll + 16);

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
		if (ObjectManager_player.flipped)
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
		if (ObjectManager_player.flipped)
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
		if (ObjectManager_player.flipped)
			blockX++;

		playerX = B2V(blockX) - offset;
		playerSpeedX = projectedX - playerX;

		return;
	}
	
update_x:
	playerX = projectedX;
}

u16 oldBottomTileTypeLeft = TERRAIN_SOLID;
u16 oldBottomTileTypeRight = TERRAIN_SOLID;
s16 oldBlockY = 0;


void Player_UpdateStand(GameObject* player)
{
	if (JoystickManager_buttonsPressed & PORT_A_KEY_2 || jumpWhenLanding)
	{
		setPlayerState(PLAYER_STATE_JUMP);
		return;
	}

	if (JoystickManager_buttonState & PORT_A_KEY_LEFT || JoystickManager_buttonState & PORT_A_KEY_RIGHT)
	{
		setPlayerState(PLAYER_STATE_RUN);
		return;
	}
	else if (JoystickManager_buttonState & PORT_A_KEY_DOWN)
	{
		setPlayerState(PLAYER_STATE_DUCK);
		return;
	}

	pointingUp = (JoystickManager_buttonState & PORT_A_KEY_UP);
	pointingDown = FALSE;


	s16 blockLeft = V2B(playerX + P2V(ObjectManager_player.rectLeft));
	s16 blockRight = V2B(playerX + P2V(ObjectManager_player.rectRight));

	s16 ySensor = playerY + P2V(ObjectManager_player.rectBottom);
	s16 blockY = V2B(ySensor);

	u16 bottomTileTypeLeft = GET_TERRAIN(blockLeft, blockY);
	u16 bottomTileTypeRight = GET_TERRAIN(blockRight, blockY);

	if (bottomTileTypeLeft == TERRAIN_EMPTY && bottomTileTypeRight == TERRAIN_EMPTY)
	{
		canStillJumpFrames = NUM_FRAMES_AFTER_LEAVING_LEDGE_TO_JUMP;
		setPlayerState(PLAYER_STATE_FALL);
	}
}

void Player_UpdateRun(GameObject* player)
{
	if (JoystickManager_buttonsPressed & PORT_A_KEY_2 || jumpWhenLanding)
	{
		setPlayerState(PLAYER_STATE_JUMP);
		return;
	}
	else if (JoystickManager_buttonState & PORT_A_KEY_DOWN)
	{
		setPlayerState(PLAYER_STATE_DUCK);
		return;
	}
	else if (JoystickManager_buttonState & PORT_A_KEY_LEFT)
	{
		ObjectManager_player.flipped = TRUE;
		playerSpeedX = -PLAYER_SPEED_X;
	}
	else if (JoystickManager_buttonState & PORT_A_KEY_RIGHT)
	{
		ObjectManager_player.flipped = FALSE;
		playerSpeedX = PLAYER_SPEED_X;
	}
	else
	{
		setPlayerState(PLAYER_STATE_STAND);
		return;
	}

	pointingUp = (JoystickManager_buttonState & PORT_A_KEY_UP);
	pointingDown = FALSE;

	Player_UpdateX();

	s16 blockLeft = V2B(playerX + P2V(ObjectManager_player.rectLeft));
	s16 blockRight = V2B(playerX + P2V(ObjectManager_player.rectRight));

	s16 ySensor = playerY + P2V(ObjectManager_player.rectBottom);
	s16 blockY = V2B(ySensor);

	u16 bottomTileTypeLeft = GET_TERRAIN(blockLeft, blockY);
	u16 bottomTileTypeRight = GET_TERRAIN(blockRight, blockY);

	if (bottomTileTypeLeft == TERRAIN_EMPTY && bottomTileTypeRight == TERRAIN_EMPTY)
	{
		canStillJumpFrames = NUM_FRAMES_AFTER_LEAVING_LEDGE_TO_JUMP;
		setPlayerState(PLAYER_STATE_FALL);
	}
}

void Player_UpdateFall(GameObject* player)
{
	if (canStillJumpFrames)
	{
		if (JoystickManager_buttonsPressed & PORT_A_KEY_2)
		{
			playerSpeedY = 0;
			setPlayerState(PLAYER_STATE_JUMP);
			return;
		}

		canStillJumpFrames--;
	}
	else
	{
		if (JoystickManager_buttonsPressed & PORT_A_KEY_2)
			jumpPressCounter = 0;

		jumpPressCounter++;
	}

	if (JoystickManager_buttonState & PORT_A_KEY_LEFT)
	{
		ObjectManager_player.flipped = TRUE;
		playerSpeedX = -PLAYER_SPEED_X;
	}
	else if (JoystickManager_buttonState & PORT_A_KEY_RIGHT)
	{
		ObjectManager_player.flipped = FALSE;
		playerSpeedX = PLAYER_SPEED_X;
	}
	else
	{
		playerSpeedX = 0;
	}

	pointingUp = (JoystickManager_buttonState & PORT_A_KEY_UP);
	pointingDown = (JoystickManager_buttonState & PORT_A_KEY_DOWN);

	Player_UpdateX();

	playerSpeedY += PLAYER_GRAVITY;
	playerY += playerSpeedY;

	s16 blockLeft = V2B(playerX + P2V(ObjectManager_player.rectLeft));
	s16 blockRight = V2B(playerX + P2V(ObjectManager_player.rectRight));

	s16 ySensor = playerY + P2V(ObjectManager_player.rectBottom);

	s16 blockY = V2B(ySensor);

	// don't do any collisions if our feet are offscreen
	if (blockY < 0)
		return;

	u16 bottomTileTypeLeft = GET_TERRAIN(blockLeft, blockY);
	u16 bottomTileTypeRight = GET_TERRAIN(blockRight, blockY);

	if (bottomTileTypeLeft == TERRAIN_SOLID || 
		bottomTileTypeRight == TERRAIN_SOLID ||
		(oldBlockY != blockY && // don't detect topsolid tiles if we're on the same block as previous
			(
				(oldBottomTileTypeLeft == TERRAIN_EMPTY && bottomTileTypeLeft == TERRAIN_TOPSOLID) ||
				(oldBottomTileTypeRight == TERRAIN_EMPTY && bottomTileTypeRight == TERRAIN_TOPSOLID)
			)
		 ))
	{
		playerY = B2V(blockY) - P2V(ObjectManager_player.rectBottom);
		playerSpeedY = 0;

		jumpWhenLanding = (jumpPressCounter < NUM_FRAMES_JUMP_BUFFER_AFTER_LANDING);

		setPlayerState(PLAYER_STATE_STAND);

	}

	oldBottomTileTypeLeft = bottomTileTypeLeft;
	oldBottomTileTypeRight = bottomTileTypeRight;
	oldBlockY = blockY;
}

void Player_UpdateJump(GameObject* player)
{
	if (JoystickManager_buttonState & PORT_A_KEY_LEFT)
	{
		ObjectManager_player.flipped = TRUE;
		playerSpeedX = -PLAYER_SPEED_X;
	}
	else if (JoystickManager_buttonState & PORT_A_KEY_RIGHT)
	{
		ObjectManager_player.flipped = FALSE;
		playerSpeedX = PLAYER_SPEED_X;
	}
	else
	{
		playerSpeedX = 0;
	}

	pointingUp = (JoystickManager_buttonState & PORT_A_KEY_UP);
	pointingDown = (JoystickManager_buttonState & PORT_A_KEY_DOWN);

	Player_UpdateX();

	playerSpeedY += (JoystickManager_buttonState & PORT_A_KEY_2) ? PLAYER_GRAVITY : PLAYER_GRAVITY_HEAVY;

	if (playerSpeedY > 0)
	{
		playerSpeedY = 0;
		canStillJumpFrames = 0;

		oldBottomTileTypeLeft = TERRAIN_INVALID;
		oldBottomTileTypeRight = TERRAIN_INVALID;

		setPlayerState(PLAYER_STATE_FALL);
		return;
	}

	playerY += playerSpeedY;

	s16 blockLeft = V2B(playerX + P2V(ObjectManager_player.rectLeft));
	s16 blockRight = V2B(playerX + P2V(ObjectManager_player.rectRight));

	s16 ySensor = playerY + P2V(ObjectManager_player.rectTop);

	s16 blockY = V2B(ySensor);

	// don't do any collisions if the head is offscreen
	if (blockY < 0)
		return;

	u16 topTileTypeLeft = GET_TERRAIN(blockLeft, blockY);
	u16 topTileTypeRight = GET_TERRAIN(blockRight, blockY);

	if (topTileTypeLeft == TERRAIN_SOLID  || topTileTypeRight == TERRAIN_SOLID)
	{
		playerY = B2V(blockY + 1) - P2V(ObjectManager_player.rectTop);
		playerSpeedY = 0;
		canStillJumpFrames = 0;
		setPlayerState(PLAYER_STATE_FALL);
	}
}

void Player_UpdateDuck(GameObject* player)
{
	if (!(JoystickManager_buttonState & PORT_A_KEY_DOWN))
	{
		setPlayerState(PLAYER_STATE_STAND);
		return;
	}
	else if (JoystickManager_buttonState & PORT_A_KEY_LEFT)
	{
		ObjectManager_player.flipped = TRUE;
	}
	else if (JoystickManager_buttonState & PORT_A_KEY_RIGHT)
	{
		ObjectManager_player.flipped = FALSE;
	}

	pointingUp = FALSE;
	pointingDown = FALSE;

	s16 blockLeft = V2B(playerX + P2V(ObjectManager_player.rectLeft));
	s16 blockRight = V2B(playerX + P2V(ObjectManager_player.rectRight));

	s16 ySensor = playerY + P2V(ObjectManager_player.rectBottom);
	s16 blockY = V2B(ySensor);

	u16 bottomTileTypeLeft = GET_TERRAIN(blockLeft, blockY);
	u16 bottomTileTypeRight = GET_TERRAIN(blockRight, blockY);

	if (JoystickManager_buttonsPressed & PORT_A_KEY_2 && 
		(bottomTileTypeLeft == TERRAIN_TOPSOLID &&
		 bottomTileTypeRight == TERRAIN_TOPSOLID)) 
	{
		playerY++;
		playerSpeedY = 0;
		canStillJumpFrames = 0;
		setPlayerState(PLAYER_STATE_FALL);
		return;
	}

	if (bottomTileTypeLeft == TERRAIN_EMPTY && bottomTileTypeRight == TERRAIN_EMPTY)
	{
		canStillJumpFrames = NUM_FRAMES_AFTER_LEAVING_LEDGE_TO_JUMP;
		setPlayerState(PLAYER_STATE_FALL);
	}
}

void AnimationUtils_UpdateStreamedBatchedAnimationFrameBanked(GameObject* gameObject)
{
	SMS_mapROMBank(gameObject->resourceInfo->bankNumber);
	AnimationUtils_UpdateStreamedBatchedAnimationFrame(gameObject);
}

void Player_Update(GameObject* player)
{

	u8 oldFlip = ObjectManager_player.flipped;
	u8 oldPointingUp = pointingUp;
	u8 oldPointingDown = pointingDown;

	player_SubUpdate(player);

	if (JoystickManager_buttonsPressed & PORT_A_KEY_1 /* && !isPlayerShooting*/)
		Player_FireWeapon(player);

	player->x = V2P(playerX);
	player->y = V2P(playerY);

	// update animation
	SMS_mapROMBank(player->resourceInfo->bankNumber);

	if (ObjectManager_player.flipped != oldFlip ||
		oldPointingUp != pointingUp ||
		oldPointingDown != pointingDown)
		setPlayerAnimation();


	if (ObjectManager_player.UpdateAnimation(&ObjectManager_player) == ANIMATION_CHANGED_FRAME || 
		updateAnimationStream)
	{
		ObjectManager_QueueVDPDraw(&ObjectManager_player, AnimationUtils_UpdateStreamedBatchedAnimationFrameBanked);
	}
}

BOOL Player_Draw(GameObject* object)
{
	//SMS_debugPrintf("Switching to Bank %d.\n", object->resourceInfo->bankNumber);
	SMS_mapROMBank(object->resourceInfo->bankNumber);
	//SMS_debugPrintf("Switched\n");
	DRAWUTILS_SETUP_BATCH(object->screenx,
						  object->screeny,
						  object->currentBatchedAnimationFrame->spriteStrips,
						  *object->batchedAnimation->vdpLocation);
	//SMS_debugPrintf("batch start\n");
	DrawUtils_DrawStreamedBatched();
	//SMS_debugPrintf("batch end\n");
	return TRUE;
}

