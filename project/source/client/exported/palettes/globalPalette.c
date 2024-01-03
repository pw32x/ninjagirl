#include "globalPalette.h"

const u8 globalPaletteValues[16] = 
{
    0x00,
    0x01,
    0x10,
    0x15,
    0x06,
    0x04,
    0x17,
    0x15,
    0x35,
    0x07,
    0x2a,
    0x09,
    0x2b,
    0x3d,
    0x1f,
    0x3f,
};

const PaletteResource globalPalette = 
{
    PALETTE_RESOURCE_TYPE, 
    globalPaletteValues,
};
