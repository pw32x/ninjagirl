#include "SMSlib.h"
#include "PSGlib.h"

#include "engine/base_types.h"
#include "engine/base_defines.h"
#include "engine/level_manager.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/resource_manager.h"

// levels
#include "exported/level001.h"
#include "exported/level002.h"

// music
#include "generated/bank2.h"

#include "client/exported/global_palette.h"

#define LEVEL_TO_RUN level002

void PSGUpdate(void)
{
	PSGFrame();
	PSGSFXFrame();
}

void main(void)
{
	SMS_setFrameInterruptHandler(PSGUpdate);

	ResourceManager_Init();

	PSGPlay(song_psg);

	/* Clear VRAM */
	SMS_VRAMmemsetW(0, 0x0000, 16384);

	LevelManager_Init(&LEVEL_TO_RUN);

	SMS_setSpriteMode(SPRITEMODE_TALL);

	/* Turn on the display */
	SMS_displayOn();
	SMS_waitForVBlank ();

	// game loop
	for(;;) 
	{ 
		ObjectManager_Update();
		SMS_setBackdropColor(COLOR_LIGHT_GREEN);
		// VBLANK
		SMS_waitForVBlank ();
		ScrollManager_UpdateVDP();
		SMS_copySpritestoSAT();
		SMS_setBackdropColor(COLOR_WHITE);
		ObjectManager_VDPDraw();
		SMS_setBackdropColor(0);

	}
}

SMS_EMBED_SEGA_ROM_HEADER(9999,0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1,0,"pw","basicsmsproject","A basic SMS example project with devkitSMS");
