#ifndef DRAW_UTILS_INCLUDE_H
#define DRAW_UTILS_INCLUDE_H

#include "engine/animation_types.h"

#define DRAWUTILS_SETUP(x, y, count, sprite, vdpTileIndex)\
{\
	DrawUtils_screenX = x;\
	DrawUtils_screenY = y;\
	DrawUtils_spriteCounter = count;\
	DrawUtils_currentSprite = sprite;\
	DrawUtils_vdpTileIndex = vdpTileIndex;\
} 

void DrawUtils_Draw(void);
void DrawUtils_DrawClipped(void);
void DrawUtils_DrawClippedSides(void);

extern char DrawUtils_spriteCounter;
extern const AnimationSprite* DrawUtils_currentSprite;
extern u8 DrawUtils_vdpTileIndex;
extern s16 DrawUtils_screenX;
extern s16 DrawUtils_screenY;

#endif