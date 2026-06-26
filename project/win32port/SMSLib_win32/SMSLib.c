#include "SMSLib.h"

void SMS_setBGScrollY (unsigned char scrollY)
{

}

void SMS_loadBGPalette (const void *palette)
{

}

void SMS_loadSpritePalette (const void *palette)
{

}

void UNSAFE_SMS_copySpritestoSAT (void)
{

}

void SMS_debugPrintf(const unsigned char *format, ...)
{

}

void SMS_initSprites (void)
{

}

signed char SMS_addSprite_f (unsigned int y, unsigned int x_tile)
{
	return 0;
}

void SMS_VRAMmemcpy (unsigned int dst, const void *src, unsigned int size) 
{

}

void SMS_mapROMBank(unsigned char bankNumber)
{

}

unsigned char SMS_getROMBank()
{
	return 0;
}

void SMS_loadTileMapColumnatAddr (unsigned int dst, const void *src, unsigned int height)
{

}

unsigned char MetaSpriteBaseTile;

void SMS_addMetaSprite_f (unsigned int origin_yx, const void *metasprite)
{

}

void SMS_addTwoAdjoiningSprites_f (unsigned int y, unsigned int x_tile)
{

}

void SMS_addThreeAdjoiningSprites_f (unsigned int y, unsigned int x_tile) 
{

}

void SMS_addFourAdjoiningSprites_f (unsigned int y, unsigned int x_tile)
{

}

void SMS_VDPturnOnFeature (unsigned int feature) 
{

}
void SMS_VDPturnOffFeature (unsigned int feature)
{

}

void SMS_setBackdropColor (unsigned char entry)
{

}

void SMS_useFirstHalfTilesforSprites (_Bool usefirsthalf)
{

}

void SMS_setSpriteMode (unsigned char mode)
{

}

void SMS_waitForVBlank (void)
{

}

void SMS_copySpritestoSAT (void)
{

}

void SMS_autoSetUpTextRenderer (void)
{

}

void SMS_setFrameInterruptHandler (void (*theHandlerFunction)(void))
{

}

void SMS_VRAMmemsetW (unsigned int dst, unsigned int value, unsigned int size)
{

}

void SMS_setBGPaletteColor (unsigned char entry, unsigned char color)
{

}

void SMS_setSpritePaletteColor (unsigned char entry, unsigned char color)
{

}

void SMS_crt0_RST08(unsigned int addr)
{

}

void SMS_crt0_RST18(unsigned int tile)
{

}

void SMS_setBGScrollX (unsigned char scrollX)
{

}

void UNSAFE_SMS_VRAMmemcpy32 (unsigned int dst, const void *src)
{

}

void UNSAFE_SMS_VRAMmemcpy64 (unsigned int dst, const void *src)
{

}

void UNSAFE_SMS_VRAMmemcpy128 (unsigned int dst, const void *src)
{

}

void UNSAFE_SMS_VRAMmemcpy192 (unsigned int dst, const void *src)
{

}

void UNSAFE_SMS_VRAMmemcpy256 (unsigned int dst, const void *src)
{

}
