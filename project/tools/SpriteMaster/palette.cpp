#include "palette.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <wtypes.h>

void WritePaletteHeaderFile(const std::string& outputFolder, const std::string& outputName)
{
	std::string headerFilename = outputName + ".h";
	std::ofstream headerfile(outputFolder + headerFilename);

    // header guard
    std::string headerGuard = outputName + "_INCLUDE_H";
    std::transform(headerGuard.begin(), headerGuard.end(), headerGuard.begin(), ::toupper);
    headerfile << "// File generated by SpriteMaster. https://github.com/pw32x/ninjagirl\n";
    headerfile << "#ifndef " << headerGuard << "\n";
    headerfile << "#define " << headerGuard << "\n";
    headerfile << "\n";

	// includes
    headerfile << "\n";

	// exported types
    headerfile << "extern unsigned short " << outputName << "[16];\n"; 
    headerfile << "\n";

    // end header guard
    headerfile << "#endif\n\n";
    headerfile.close();
}

void GetPaletteData(HPALETTE hPalette, PALETTEENTRY* paletteEntries)
{
    // Determine the number of entries in the palette
    WORD numEntries;
    GetObject(hPalette, sizeof(WORD), &numEntries);

    // Retrieve the palette entries
    GetPaletteEntries(hPalette, 0, numEntries, paletteEntries);

    // Process the palette data
    for (int i = 0; i < numEntries; ++i)
    {
        PALETTEENTRY entry = paletteEntries[i];
        // Access individual palette entry values (entry.peRed, entry.peGreen, entry.peBlue, entry.peFlags)
        // Perform desired operations with the palette data
    }
}

void WritePaletteSourceFile(HPALETTE palette, const std::string& outputFolder, const std::string& outputName)
{
    const unsigned int numEntries = 16;

    PALETTEENTRY paletteEntries[numEntries];

    GetPaletteData(palette, paletteEntries);

	std::ofstream sourceFile(outputFolder + outputName + ".c");

    // includes
    sourceFile << "// File generated by SpriteMaster. https://github.com/pw32x/ninjagirl\n";
    sourceFile << "#include \"" << outputName << ".h\"\n";
    sourceFile << "\n";
    sourceFile << "\n";

    sourceFile << "unsigned short " << outputName << "[16] = \n"; 
    sourceFile << "{\n";

    for (int loop = 0; loop < numEntries; loop++)
    {
        PALETTEENTRY* paletteEntry = &paletteEntries[loop];

        unsigned short red = (unsigned short)((float)paletteEntry->peRed / 256 * 8);
        unsigned short green = (unsigned short)((float)paletteEntry->peGreen / 256 * 8);
        unsigned short blue = (unsigned short)((float)paletteEntry->peBlue / 256 * 8);
        unsigned short paletteValue = (unsigned short)((red << 1) | (green << 5) | (blue << 9));

        sourceFile << "    0x" << std::hex << paletteValue << ", \n";
    }

    sourceFile << "};\n";

    sourceFile.close();
}

void WritePalette(HPALETTE palette, const std::string& outputFolder, const std::string& outputName)
{
    std::string paletteOutputName = outputName + "_palette";

	WritePaletteHeaderFile(outputFolder, paletteOutputName);
	WritePaletteSourceFile(palette, outputFolder, paletteOutputName);
}


