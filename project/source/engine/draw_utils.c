#include "draw_utils.h"
#include "SMSlib.h"
#include "engine/base_defines.h"

u8 DrawUtils_spriteCounter;
const AnimationSprite* DrawUtils_currentSprite;
u8 DrawUtils_vdpTileIndex;
s16 DrawUtils_screenX;
s16 DrawUtils_screenY;

#define MAX_SPRITES 64
u8 DrawUtils_spritesDrawn;

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

// 1st sdcccall(1) ASM version: 116 CPU cycles
void SMS_addSprite_fast_f (unsigned char y, unsigned int x_tile) __naked __preserves_regs(d,e,iyh,iyl) __sdcccall(1) {
  // Y passed in A
  // X passed in D
  // tile passed in E
  __asm
    ld  hl,#_SpriteNextFree          ; load current SpriteNextFree value
    ld  c,(hl)                       ; (in C)
    inc (hl)                         ; increment SpriteNextFree
    ld  b,#0x00
    ld  hl,#_SpriteTableY
    add hl,bc                        ; hl+=SpriteNextFree
    dec a
    ld (hl),a                        ; write Y (as Y-1)

    ld hl,#_SpriteTableXN
    sla c
    add hl,bc                        ; hl+=(SpriteNextFree*2)
    ld (hl),d                        ; write X
    inc hl
    ld (hl),e                        ; write tile number
    ret
 __endasm;
}

#define SMS_addSprite_fast(x,y,tile) SMS_addSprite_fast_f((y),(((x)&0xff)<<8)|(((tile)&0xff)))
//#define SMS_addSprite_fast(x,y,tile) SMS_addSprite_f((y),(((x)&0xff)<<8)|(((tile)&0xff)))

void DrawUtils_Draw(void)
{
	if (DrawUtils_spritesDrawn + DrawUtils_spriteCounter > MAX_SPRITES - 1)
			DrawUtils_spriteCounter = MAX_SPRITES - DrawUtils_spritesDrawn;

	// doesn't support sprites with more than 16 8x8 sprites
	switch (DrawUtils_spriteCounter) 
	{
	case 16: SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 15: SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 14: SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 13: SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 12: SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 11: SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 10: SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 9:  SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 8:  SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 7:  SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 6:  SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 5:  SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 4:  SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 3:  SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 2:  SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	case 1:  SMS_addSprite_fast(DrawUtils_screenX + DrawUtils_currentSprite->xOffset, DrawUtils_screenY + DrawUtils_currentSprite->yOffset, DrawUtils_currentSprite->tileIndex + DrawUtils_vdpTileIndex); DrawUtils_currentSprite++;
	}

	DrawUtils_spritesDrawn += DrawUtils_spriteCounter;
}