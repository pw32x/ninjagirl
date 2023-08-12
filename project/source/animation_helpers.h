#ifndef ANIMATION_HELPERS_INCLUDE_H
#define ANIMATION_HELPERS_INCLUDE_H

#include "animation_types.h"

void Animation_DrawFrame(const AnimationFrame* frame, 
						 u8 vdpTileIndex,
						 s16 x, 
						 s16 y);

#endif