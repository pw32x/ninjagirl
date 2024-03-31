#include "SMSlib.h"
#include "PSGlib.h"

#include "engine/base_types.h"
#include "engine/base_defines.h"
#include "engine/scene_manager.h"
#include "engine/object_manager.h"
#include "engine/scroll_manager.h"
#include "engine/resource_manager.h"
#include "engine/joystick_manager.h"

#include "client/managers/weapon_manager.h"

#include "objects/on_resource_loaded_callback.h"

// levels
//#include "exported/level001.h"
//#include "exported/scenes/scene001.h"
#include "exported/scenes/scene003.h"

#ifdef USE_SCENEMASTER_LEVEL
#include "exported/sceneMasterTemp.h"
#define SCENE_TO_RUN sceneMasterTemp
#endif

#ifndef SCENE_TO_RUN
#define SCENE_TO_RUN scene003
#endif

void PSGUpdate(void)
{
	PSGFrame();
	PSGSFXFrame();
}

void main(void)
{
	SMS_debugPrintf("**********************************\n");
	SMS_debugPrintf("**********************************\n");
	SMS_debugPrintf("**********************************\n");

	SMS_setFrameInterruptHandler(PSGUpdate);

	SMS_useFirstHalfTilesforSprites(TRUE);

	ResourceManager_Init((OnResourceLoadedCallback)OnResourceLoaded);

	/* Clear VRAM */
	SMS_VRAMmemsetW(0, 0x0000, 16384);

	WeaponManager_InitGame();

	SMS_autoSetUpTextRenderer();

	SceneManager_Init(&SCENE_TO_RUN);
		
	SMS_setSpriteMode(SPRITEMODE_TALL);

	/* Turn on the display */
	SMS_displayOn();
	SMS_waitForVBlank ();

	// game loop
	for(;;) 
	{ 
		SMS_setBackdropColor(COLOR_DARK_GREEN);
		JoystickManager_Update();
		ObjectManager_Update();
		SMS_setBackdropColor(COLOR_LIGHT_GREEN);
		// VBLANK
		SMS_waitForVBlank ();
		//SMS_setBackdropColor(COLOR_DARK_BLUE);
		SMS_copySpritestoSAT(); // UNSAFE_SMS_copySpritestoSAT(); ???

		ObjectManager_VDPDraw();

		ScrollManager_UpdateVDP();

		//SMS_setBackdropColor(COLOR_BLACK);

	}
}

SMS_EMBED_SEGA_ROM_HEADER(9999,0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1,0,"pw","basicsmsproject","A basic SMS example project with devkitSMS");
