#include "draw_utils.h"
#include "SMSlib.h"
#include "engine/base_defines.h"
#include "engine/object_types.h"
#include "engine/scroll_manager.h"

u8 DrawUtils_spriteCounter;
const BatchedAnimationSpriteStrip* DrawUtils_currentSpriteStrips;
u8 DrawUtils_vdpTileIndex;
s16 DrawUtils_screenX;
s16 DrawUtils_screenY;

u8 DrawUtils_spritesDrawn;

#define MAXSPRITES      64

void DrawUtils_addSprite(unsigned int y, unsigned int x_tile) __naked __preserves_regs(d,e,iyh,iyl) __sdcccall(1) 
{
    UNUSED(y);
    UNUSED(x_tile);
  // Y passed in L
  // X passed in D
  // tile passed in E
  // return value will be in A
  __asm
    ld  a,(#_SpriteNextFree)
    cp  a,#MAXSPRITES
    ret nc                           ; no sprites left, leave!
    ld  c,a                          ; save SpriteNextFree value in c

    ld  a,l
    cp  a,#0xd1
    ret z                            ; invalid Y, leave!

    ld  hl,#_SpriteTableY
    ld  b,#0x00
    add hl,bc                        ; hl+=SpriteNextFree
    dec a
    ld (hl),a                        ; write Y (as Y-1)

    ld hl,#_SpriteTableXN
    ld a,c                           ; save sprite handle to A
    sla c
    add hl,bc                        ; hl+=(SpriteNextFree*2)
    ld (hl),d                        ; write X
    inc hl
    ld (hl),e                        ; write tile number

    inc a                            ; increment and
    ld (#_SpriteNextFree),a          ; save SpriteNextFree value
    ret
 __endasm;
}

// based on SMS_addTwoAdjoiningSprites_f but asumes sprites are 8 pixels wide
void DrawUtils_addTwoAdjoiningSprites(unsigned int y, unsigned int x_tile) __naked __preserves_regs(d,e,iyh,iyl) __sdcccall(1) 
{
    UNUSED(y);
    UNUSED(x_tile);
  // Y passed in L
  // X passed in D
  // tile passed in E
  __asm
    ld  a,(#_SpriteNextFree)
    cp  a,#MAXSPRITES-1
    ret nc                           ; we do not have 2 sprites left, leave!
    ld  c,a                          ; save SpriteNextFree value in c
    ld  b,#0x00

    ld  a,l
    cp  a,#0xd1
    ret z                            ; invalid Y, leave!

    ld  hl,#_SpriteTableY
    add hl,bc
    dec a
    ld (hl),a                        ; write Y  (as Y-1)
    inc hl
    ld (hl),a                        ; write Y again for the second sprite (always as Y-1)

    ld hl,#_SpriteTableXN
    add hl,bc
    add hl,bc
    ld (hl),d                        ; write X
    inc hl
    ld (hl),e                        ; write tile number

    ld a,#8                          ; load current sprite width
    add a,d
    jr c,_secondSpriteClipped        ; if new X is overflowing, do not place second sprite
    inc hl
    ld (hl),a                        ; write X + spritesWidth

    ld a,(#_spritesTileOffset)       ; load current sprite tile offset
    add a,e
    inc hl
    ld (hl),a                        ; write tile number + spritesTileOffset

    ld  a,c
    add a,#2
    ld (#_SpriteNextFree),a          ; save SpriteNextFree new value
    ret

_secondSpriteClipped:
    ld  hl,#_SpriteNextFree          ; second sprite has been clipped, so just inc SpriteNextFree
    inc (hl)
    ret
  __endasm;
}

// based on SMS_addThreeAdjoiningSprites_f but asumes sprites are 8 pixels wide
void DrawUtils_addThreeAdjoiningSprites(unsigned int y, unsigned int x_tile) __naked __preserves_regs(d,e,iyh,iyl) __sdcccall(1) 
{
    UNUSED(y);
    UNUSED(x_tile);
  // Y passed in L
  // X passed in D
  // tile passed in E
  __asm
    ld  a,(#_SpriteNextFree)
    cp  a,#MAXSPRITES-2
    ret nc                           ; we do not have 3 sprites left, leave!
    ld  c,a                          ; save SpriteNextFree value in c

    ld  a,l
    cp  a,#0xd1
    ret z                            ; invalid Y, leave!

    ld  b,#0x00
    ld  hl,#_SpriteTableY
    add hl,bc
    dec a
    ld (hl),a                        ; write Y  (as Y-1)
    inc hl
    ld (hl),a                        ; write Y again for the second sprite (always as Y-1)
    inc hl
    ld (hl),a                        ; write Y once more for the third sprite (always as Y-1)

    ld hl,#_SpriteTableXN
    add hl,bc
    add hl,bc
    ld (hl),d                        ; write X
    inc hl
    ld (hl),e                        ; write tile number

    ld a,(#_spritesWidth)            ; load current sprite width
    add a,d
    jr c,_secondSpriteClipped3        ; if new X is overflowing, do not place second sprite
    inc hl
    ld (hl),a                        ; write X + spritesWidth

    ld a,(#_spritesTileOffset)       ; load current sprite tile offset
    add a,e
    inc hl
    ld (hl),a                        ; write tile number + spritesTileOffset

    ld a,(#_spritesWidth)            ; load current sprite width
    add a,a                          ; double that
    add a,d
    jr c,_thirdSpriteClipped3         ; if new X is overflowing, do not place third sprite
    inc hl
    ld (hl),a                        ; write X + spritesWidth*2

    ld a,(#_spritesTileOffset)       ; load current sprite tile offset
    add a,a                          ; double that
    add a,e
    inc hl
    ld (hl),a                        ; write tile number + spritesTileOffset*2

    ld  a,c                          ; three sprite has been placed, then SpriteNextFree+=3
    add a,#3
    ld (#_SpriteNextFree),a          ; save SpriteNextFree new value
    ret

_secondSpriteClipped3:
    ld  a,c                          ; second sprite has been clipped, so just inc SpriteNextFree
    inc a
    ld (#_SpriteNextFree),a          ; save SpriteNextFree new value
    ret

_thirdSpriteClipped3:
    ld  a,c                          ; third sprite has been clipped, so just SpriteNextFree+=2
    add a,#2
    ld (#_SpriteNextFree),a          ; save SpriteNextFree new value
    ret
 __endasm;
}

// based on SMS_addThreeAdjoiningSprites_f but does four sprites and asumes sprites are 8 pixels wide
void DrawUtils_addFourAdjoiningSprites(unsigned int y, unsigned int x_tile) __naked __preserves_regs(d, e, iyh, iyl) __sdcccall(1) 
{
    UNUSED(y);
    UNUSED(x_tile);
  // Y passed in L
  // X passed in D
  // tile passed in E
  __asm
    ld  a, (#_SpriteNextFree)
    cp  a, #MAXSPRITES-3
    ret nc                           ; we do not have 4 sprites left, leave!
    ld  c, a                          ; save SpriteNextFree value in c

    ld  a, l
    cp  a, #0xD1
    ret z                            ; invalid Y, leave!

    ld  b, #0x00
    ld  hl, #_SpriteTableY
    add hl, bc
    dec a
    ld (hl), a                        ; write Y  (as Y-1)
    inc hl
    ld (hl), a                        ; write Y again for the second sprite (always as Y-1)
    inc hl
    ld (hl), a                        ; write Y once more for the third sprite (always as Y-1)
    inc hl
    ld (hl), a                        ; write Y once more for the fourth sprite (always as Y-1)

    ld hl, #_SpriteTableXN
    add hl, bc
    add hl, bc
    ld (hl), d                        ; write X
    inc hl
    ld (hl), e                        ; write tile number

    ld a, #8            ; load current sprite width
    add a, d
    jr c, _secondSpriteClipped2        ; if new X is overflowing, do not place second sprite
    inc hl
    ld (hl), a                        ; write X + spritesWidth

    ld a, (#_spritesTileOffset)       ; load current sprite tile offset
    add a, e
    inc hl
    ld (hl), a                        ; write tile number + spritesTileOffset

    ld a, #16            ; load current sprite width
    add a, d
    jr c, _thirdSpriteClipped2         ; if new X is overflowing, do not place third sprite
    inc hl
    ld (hl), a                        ; write X + spritesWidth*2

    ld a, (#_spritesTileOffset)       ; load current sprite tile offset
    add a, a                          ; double that
    add a, e
    inc hl
    ld (hl), a                        ; write tile number + spritesTileOffset*2

    ld a, #24                         ; load current sprite width
    add a, d
    jr c, _fourthSpriteClipped2        ; if new X is overflowing, do not place fourth sprite
    inc hl
    ld (hl), a                        ; write X + spritesWidth*4

    ld a, (#_spritesTileOffset)       ; load current sprite tile offset
    add a, a                          ; double that again
	add a, #2
    add a, e
    inc hl
    ld (hl), a                        ; write tile number + spritesTileOffset*4

    ld  a, c                          ; four sprites have been placed, then SpriteNextFree += 4
    add a, #4
    ld (#_SpriteNextFree), a          ; save SpriteNextFree new value
    ret

_secondSpriteClipped2:
    ld  a, c                          ; second sprite has been clipped, so just inc SpriteNextFree
    inc a
    ld (#_SpriteNextFree), a          ; save SpriteNextFree new value
    ret

_thirdSpriteClipped2:
    ld  a, c                          ; third sprite has been clipped, so just SpriteNextFree += 2
    add a, #2
    ld (#_SpriteNextFree), a          ; save SpriteNextFree new value
    ret

_fourthSpriteClipped2:
    ld  a, c                          ; fourth sprite has been clipped, so just SpriteNextFree += 3
    add a, #3
    ld (#_SpriteNextFree), a          ; save SpriteNextFree new value
    ret
 __endasm;
}


void (*drawSprite[]) (unsigned int y, unsigned int x_tile) __naked __preserves_regs(d,e,iyh,iyl) __sdcccall(1) = 
{
	NULL, // do nothing for 0 sprites
	DrawUtils_addSprite,
	DrawUtils_addTwoAdjoiningSprites,
	DrawUtils_addThreeAdjoiningSprites,
	DrawUtils_addFourAdjoiningSprites,
};

#define PARAM_COMBINER(x, tile) (((x)&0xff)<<8)|(((tile)&0xff))

void DrawUtils_DrawBatched(void)
{
	const BatchedAnimationSpriteStrip* runner = DrawUtils_currentSpriteStrips;

	while (runner->count)
	{
		drawSprite[runner->count](DrawUtils_screenY + runner->yOffset, 
								  PARAM_COMBINER(DrawUtils_screenX + runner->xOffset, runner->tileIndex + DrawUtils_vdpTileIndex));

		runner++;
	}
}

void DrawUtils_DrawStreamedBatched(void)
{
    const BatchedAnimationSpriteStrip * runner = DrawUtils_currentSpriteStrips;

    int vdpOffset = 0;

    //SMS_debugPrintf("\n********* DrawStreamedBatched\n");

    while (runner->count)
    {
        //SMS_debugPrintf("%d, ", vdpOffset + DrawUtils_vdpTileIndex);

        drawSprite[runner->count](DrawUtils_screenY + runner->yOffset, 
                                  PARAM_COMBINER(DrawUtils_screenX + runner->xOffset, 
                                                 vdpOffset + DrawUtils_vdpTileIndex));

        vdpOffset += (runner->count << 1);

        runner++;
    }
}

__sfr __at 0xBF VDPControlPort2;
__sfr __at 0xBE VDPDataPort2;

u8 x; 
u8 y; 
const u16* buffer; 
u8 bufferWidth; 
u8 bufferHeight; 
u16 vdpOffset;

void drawToPlane(void)
{
    u16 address = ((x << 1) + (y << 6)) + 0x3800;

    while (bufferHeight--)
    {
        __asm di __endasm;
        u8* add = (u8*)&address;
        VDPControlPort2 = add[0];
        VDPControlPort2 = add[1] | (1 << 6);
        __asm ei __endasm;

        u16 value;
        u8* val;

        switch (bufferWidth) // limited to 16 tiles
        {
        case 16: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 15: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 14: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 13: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 12: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 11: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 10: value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 9:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 8:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 7:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 6:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 5:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 4:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 3:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 2:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        case 1:  value = *buffer + vdpOffset; val = (u8*)&value; VDPDataPort2 = *val; VDPDataPort2 = *(val + 1); buffer++;
        }

        address += 64;
    }
}

void DrawUtils_DrawPlaneAnimationFrame(struct game_object* gameObject) 
{
    const PlaneAnimation* planeAnimation = gameObject->planeAnimation;
    const PlaneAnimationFrame* frame = gameObject->currentPlaneAnimationFrame;

    x                  = gameObject->x >> 3;
    y                  = gameObject->y >> 3;
    buffer             = frame->frameTilemap;
    bufferWidth        = planeAnimation->tileWidth;
    bufferHeight       = planeAnimation->tileHeight;
    vdpOffset          = *planeAnimation->vdpLocation;

    drawToPlane();
}
