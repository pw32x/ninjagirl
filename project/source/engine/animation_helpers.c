#include "animation_helpers.h"
#include "SMSlib.h"

void Animation_DrawFrame(const AnimationFrame* frame, 
						 u8 vdpTileIndex,
						 s16 x, 
						 s16 y)
{
	char loop = frame->numSprites;
	const AnimationSprite* currentSprite = frame->sprites;

	while (loop--)
	{
		SMS_addSprite(x + currentSprite->xOffset, 
					  y + currentSprite->yOffset, 
					  currentSprite->tileIndex + vdpTileIndex);
		currentSprite++;
	}
}