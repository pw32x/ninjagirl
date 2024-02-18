#include "globalPalette.h"

const u8 globalPaletteValues[16] = 
{
    0x00,
    0x01,
    0x10,
    0x14,
    0x06,
    0x04,
    0x13,
    0x36,
    0x39,
    0x1b,
    0x29,
    0x08,
    0x2b,
    0x3a,
    0x1f,
    0x3f,
};

const PaletteResource globalPalette = 
{
    PALETTE_RESOURCE_TYPE, 
    globalPaletteValues,
};
