#include <stdio.h>
#include "SMSlib.h"
#include "types.h"
#include "objecttypes.h"
#include "ninja_girl.h"
#include "player.h"
#include "scroll_manager.h"
#include "background.h"
#include "background_tileset.h"

u8 globalPalette[16] = 
{
 0x00 , 0x01 , 0x10 , 0x15 , 0x06 , 0x04 , 0x17 , 0x15 , 0x39 , 0x0B , 0x2A , 0x09 , 0x2B , 0x3D , 0x1F , 0x3F
};

void Animation_DrawFrame(const AnimationFrame* frame, s16 x, s16 y)
{
	char loop = frame->numSprites;
	const AnimationSprite* currentSprite = frame->sprites;

	while (loop--)
	{
		SMS_addSprite(x + currentSprite->xOffset, y + currentSprite->yOffset, currentSprite->tileIndex);
		currentSprite++;
	}

}



void loadResources(void)
{
	SMS_loadBGPalette(globalPalette);
	SMS_loadSpritePalette(globalPalette);
  
	// load tiles from Animation
	SMS_loadTiles(ninja_girl.tileData, 256, ninja_girl.totalTileCount * 32);

	// load tiles for background
	SMS_loadTiles(background_tileset.tiles, 0, background_tileset.numTiles * 32);
}

void main(void)
{
	/* Clear VRAM */
	SMS_VRAMmemsetW(0, 0x0000, 16384);

	loadResources();
  
	// init systems
	ScrollManager_Init(&background_map, &background_tileset);
	GameObject* player = Player_Create(&ninja_girl);

	/* Turn on the display */
	SMS_displayOn();
	SMS_waitForVBlank ();

	// infinite loop
	for(;;) 
	{ 
		// Game Loop
		SMS_initSprites();
	
		// update systess
		player->Update(player);		
		ScrollManager_Update(player);

		// draw
		Animation_DrawFrame(player->currentAnimationFrame, 
							player->x - ScrollManager_horizontalScroll, 
							player->y);

		// VBLANK
		SMS_waitForVBlank ();

		ScrollManager_UpdateVDP();

		SMS_copySpritestoSAT();
	}
}

SMS_EMBED_SEGA_ROM_HEADER(9999,0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1,0,"pw","basicsmsproject","A basic SMS example project with devkitSMS");
