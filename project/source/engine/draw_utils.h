#ifndef DRAW_UTILS_INCLUDE_H
#define DRAW_UTILS_INCLUDE_H

#include "engine/animation_types.h"

struct game_object;

// batched sprites drawing functions

#define DRAWUTILS_SETUP_BATCH(x, y, batchedSprites, vdpTileIndex)\
{\
	DrawUtils_screenX = x;\
	DrawUtils_screenY = y;\
	DrawUtils_currentBatchedSprites = batchedSprites;\
	DrawUtils_vdpTileIndex = vdpTileIndex;\
} 

void DrawUtils_DrawBatched(void);
void DrawUtils_DrawStreamedBatched(void);

extern char DrawUtils_spriteCounter;
extern const BatchedAnimationSprite* DrawUtils_currentBatchedSprites;
extern u8 DrawUtils_vdpTileIndex;
extern s16 DrawUtils_screenX;
extern s16 DrawUtils_screenY;

extern u8 DrawUtils_spritesDrawn;

void DrawUtils_DrawPlaneAnimationFrame(struct game_object* gameObject);

#endif