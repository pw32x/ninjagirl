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

	u8 n = (DrawUtils_spriteCounter + 7) / 8;
	switch (DrawUtils_spriteCounter % 8) {
	case 0: do { fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 7:      fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 6:      fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 5:      fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 4:      fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 3:      fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 2:      fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 1:      fx = DrawUtils_screenX + DrawUtils_currentSprite->xOffset; fy = DrawUtils_screenY + DrawUtils_currentSprite->yOffset; if (fx >= 0 && fy >= SCREEN_TOP && fx < SCREEN_RIGHT && fy < SCREEN_BOTTOM) SMS_addSprite(fx, fy, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
			} while (--n > 0);
	}
}

void DrawUtils_Draw(void)
{
	u8 n = (DrawUtils_spriteCounter + 7) / 8;
	switch (DrawUtils_spriteCounter % 8) {
	case 0: do { SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 7:      SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 6:      SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 5:      SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 4:      SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 3:      SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 2:      SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 1:      SMS_addSprite(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
			} while (--n > 0);
	}

}