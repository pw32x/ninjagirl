#include "SMSlib.h"
#include "engine/base_types.h"
#include "engine/level_manager.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"

// levels
#include "exported/level001.h"
#include "exported/level002.h"

#define LEVEL_TO_RUN level002

void main(void)
{
	/* Clear VRAM */
	SMS_VRAMmemsetW(0, 0x0000, 16384);

	LevelManager_Init(&LEVEL_TO_RUN);

	/* Turn on the display */
	SMS_displayOn();
	SMS_waitForVBlank ();

	// game loop
	for(;;) 
	{ 
		SMS_setBackdropColor(9);
		ObjectManager_Update();
		SMS_setBackdropColor(10);
		//ObjectManager_Draw();
		SMS_setBackdropColor(11);
		// VBLANK
		SMS_waitForVBlank ();
		ScrollManager_UpdateVDP();
		SMS_copySpritestoSAT();
		SMS_setBackdropColor(0);
	}
}

SMS_EMBED_SEGA_ROM_HEADER(9999,0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1,0,"pw","basicsmsproject","A basic SMS example project with devkitSMS");
