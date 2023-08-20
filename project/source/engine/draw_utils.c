#include "draw_utils.h"
#include "SMSlib.h"
#include "engine/base_defines.h"

char DrawUtils_spriteCounter;
const AnimationSprite* DrawUtils_currentSprite;
u8 DrawUtils_vdpTileIndex;
s16 DrawUtils_screenX;
s16 DrawUtils_screenY;

void DrawUtils_DrawClipped(void)
{
	s16 fx; // final position to clip against
	s16 fy; // final position to clip against

	switch (DrawUtils_spriteCounter) 
	{
	case 16: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 15: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 14: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 13: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 12: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 11: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 10: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 9:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 8:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 7:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 6:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 5:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 4:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 3:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 2:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 1:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	}
}

void DrawUtils_DrawClippedSides(void)
{
	s16 fx; // final position to clip against
	s16 fy; // final position to clip against

	switch (DrawUtils_spriteCounter) 
	{
	case 16: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 15: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 14: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 13: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 12: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 11: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 10: fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 9:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 8:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 7:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 6:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 5:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 4:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 3:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 2:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 1:  fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fx < SCREEN_RIGHT) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	}
}


void DrawUtils_Draw(void)
{
	// doesn't support sprites with more than 16 8x8 sprites
	switch (DrawUtils_spriteCounter) 
	{
	case 16: SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 15: SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 14: SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 13: SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 12: SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 11: SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 10: SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 9:  SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 8:  SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 7:  SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 6:  SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 5:  SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 4:  SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 3:  SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 2:  SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 1:  SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	}
}