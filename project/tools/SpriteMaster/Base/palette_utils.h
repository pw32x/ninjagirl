#pragma once

#include <string>
#include <windows.h>

void WritePalette(HPALETTE palette, const std::string& outputFolder, const std::string& outputName);
void GetPaletteData(HPALETTE hPalette, PALETTEENTRY* paletteEntries);