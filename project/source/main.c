#include <stdio.h>
#include "SMSlib.h"
#include "ninja_girl.h"
#include "background.h"
#include "background_tileset.h"

#define TRUE 1
#define FALSE 0

unsigned char globalPalette[16] = 
{
 0x00 , 0x01 , 0x10 , 0x15 , 0x06 , 0x04 , 0x17 , 0x15 , 0x39 , 0x0B , 0x2A , 0x09 , 0x2B , 0x3D , 0x1F , 0x3F
};

void Animation_DrawFrame(const AnimationFrame* frame, short x, short y)
{
	char loop = frame->numSprites;
	const AnimationSprite* currentSprite = frame->sprites;

	while (loop--)
	{
		SMS_addSprite(x + currentSprite->xOffset, y + currentSprite->yOffset, currentSprite->tileIndex);
		currentSprite++;
	}

}
typedef struct
{
	short x;
	short y;
	const Animation* animation;
	unsigned char animationVdpTileIndex;
	const AnimationFrame* currentAnimationFrame;
	unsigned char currentAnimationFrameIndex;
	unsigned char animationTime;
} GameObject;

void Player_Update(GameObject* gameObject)
{
	/*
	gameObject->x++;
	gameObject->x %= 255;
*/
	unsigned int buttonState = SMS_getKeysHeld();

	if (buttonState & PORT_A_KEY_LEFT)
		gameObject->x--;

	if (buttonState & PORT_A_KEY_RIGHT)
		gameObject->x++;

	if (buttonState & PORT_A_KEY_UP)
		gameObject->y--;

	if (buttonState & PORT_A_KEY_DOWN)
		gameObject->y++;

	if (gameObject->animationTime == gameObject->currentAnimationFrame->frameTime)
	{
		gameObject->currentAnimationFrameIndex++;

		if (gameObject->currentAnimationFrameIndex == gameObject->animation->numFrames)
			gameObject->currentAnimationFrameIndex = 0;

		gameObject->currentAnimationFrame = gameObject->animation->frames[gameObject->currentAnimationFrameIndex];
		gameObject->animationTime = 0;
	}




	gameObject->animationTime++;
}

unsigned short ScrollManager_horizontalScroll = 0;
unsigned char Scroll_vdpHorizontalScroll = 0;

// hard-coded column when we need to show more of the map. Replace
// this with an actual larger map.
#define SCROLL_COLUMN_HEIGHT 24
unsigned short Scroll_column[SCROLL_COLUMN_HEIGHT];

unsigned char Scroll_updateMapColumn = FALSE;
unsigned char Scroll_speed = 0;//1;

void buildColumn(unsigned short tileColumn)
{
	// from the tile column, get the metatile from the level map
	unsigned short metatileColumn = (tileColumn >> 1) % background_map.mapWidth;

	// figure out which column of the metatile to get. Metatiles contain two tile columns.
	unsigned char metatileOffset = tileColumn & 1;

	unsigned short* columnRunner = Scroll_column;

	// for the height of a map column, fill the Scroll_column
	for (unsigned char loop = 0; loop < background_map.mapHeight; loop++)
	{
		// get the index into the metatile loop-up table
		unsigned short metatile_index = (background_map.metatileMap[metatileColumn + (loop * background_map.mapWidth)] * 4) + metatileOffset;

		// set the first tile
		*columnRunner = background_tileset.metatile_lut[metatile_index];
		columnRunner++;

		// set the second tile
		*columnRunner = background_tileset.metatile_lut[metatile_index + 2];
		columnRunner++;
	}
}

void Scroll_InitTilemap()
{
	// fill the map from the second column to the last.
	for (int loop = 1; loop < 32; loop++)
	{
		buildColumn(loop);
		SMS_loadTileMapColumn(loop, 0, Scroll_column, 24);
	}

	// prep the next column to be visible where the first column is.
	// we do this because columns are only updated when we hit an 8 pixel
	// boundary when we scroll. At the start, we're already at the boundary.
	// We won't see it anyway.
	buildColumn(32);
	SMS_loadTileMapColumn(0, 0, Scroll_column, 24);
}

void Scroll_Update(GameObject* gameObject)
{
	if (gameObject->x > ScrollManager_horizontalScroll + 128)
	{
		Scroll_speed = gameObject->x - (ScrollManager_horizontalScroll + 128);
	}
	else
	{
		Scroll_speed = 0;
	}

	// here we move the vdp scrolling and logical map scrolling to the same speed
	ScrollManager_horizontalScroll += Scroll_speed; // scrolling towards the right into the map
	Scroll_vdpHorizontalScroll -= Scroll_speed; // vdp scrolls backwards in comparison

	ScrollManager_horizontalScroll %= (background_map.mapWidth * 16); // clamp the scrolling to the pixel width of the map.

	if (ScrollManager_horizontalScroll % 8 == 0 && Scroll_speed) // when we hit a 8 pixel boundary, prep a new column to display
	{
		// figure out the column to update
		unsigned short tileColumn = (ScrollManager_horizontalScroll >> 3) + 32; 
		buildColumn(tileColumn);

		Scroll_updateMapColumn = TRUE;
	}	
}

void main(void)
{
	/* Clear VRAM */
	SMS_VRAMmemsetW(0, 0x0000, 16384);

	SMS_loadBGPalette(globalPalette);
	SMS_loadSpritePalette(globalPalette);
  
	// load tiles from Animation
	SMS_loadTiles(ninja_girl.tileData, 256, ninja_girl.totalTileCount * 32);

	// load tiles for background
	SMS_loadTiles(background_tileset.tiles, 0, background_tileset.numTiles * 32);
  
	Scroll_updateMapColumn = FALSE;

	SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);
	Scroll_InitTilemap();


	GameObject player;
	player.x = 122;
	player.y = 88;
	player.animation = &ninja_girl;
	player.currentAnimationFrameIndex = 0;
	player.currentAnimationFrame = ninja_girl.frames[player.currentAnimationFrameIndex];
	player.animationTime = 0;
	player.animationVdpTileIndex = 0;


	/* Turn on the display */
	SMS_displayOn();
	SMS_waitForVBlank ();

	// infinite loop
	for(;;) 
	{ 
		SMS_setBackdropColor(6);
		//SMS_setBGPaletteColor(0, 0x2A);
		// Game Loop
		SMS_initSprites();
		SMS_setBackdropColor(7);
		//SMS_setBGPaletteColor(0, 0x09 );
		Player_Update(&player);
		SMS_setBackdropColor(8);
		//SMS_setBGPaletteColor(0, 0x2B);
		Scroll_Update(&player);
		SMS_setBackdropColor(9);
		//SMS_setBGPaletteColor(0, 0x3D);

		// draw
		
		Animation_DrawFrame(player.currentAnimationFrame, player.x - ScrollManager_horizontalScroll, player.y);
		SMS_setBackdropColor(0);
		//SMS_setBGPaletteColor(0, 0x1F);

		// VBLANK

		SMS_waitForVBlank ();
		SMS_setBackdropColor(11);
		SMS_setBGScrollX(Scroll_vdpHorizontalScroll);

		if (Scroll_updateMapColumn)
		{
			Scroll_updateMapColumn = FALSE;
			unsigned char scrollMapColumn = Scroll_vdpHorizontalScroll >> 3;
			SMS_loadTileMapColumn((32 - scrollMapColumn) & 31, 0, Scroll_column, 24);
		}

		SMS_copySpritestoSAT();
		SMS_setBackdropColor(0);
	}
}

SMS_EMBED_SEGA_ROM_HEADER(9999,0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1,0,"pw","basicsmsproject","A basic SMS example project with devkitSMS");
