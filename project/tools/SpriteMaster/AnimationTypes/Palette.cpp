#include "..\stdafx.h"
#include "Palette.h"

#include "..\Base\TileStore.h"
#include "..\GraphicsGale\GraphicsGaleObject.h"
#include "..\Utils\StringUtils.h"
#include "..\Utils\WriteUtils.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace SpriteMaster
{

GGPalette::GGPalette(const GraphicsGaleObject& ggo)
: m_ggo(ggo)
{
    HPALETTE hPalette = m_ggo.getPalette(0);

    int numEntries = GetPaletteEntries(hPalette, 0, 0, NULL);

    PALETTEENTRY paletteEntries[16];

    GetPaletteEntries(hPalette, 0, 16, paletteEntries);

    for (int loop = 0; loop < numEntries; loop++)
    {
        PALETTEENTRY* paletteEntry = &paletteEntries[loop];

        byte red = (byte)((float)(paletteEntry->peRed + 8) / 255.0f * 3.0f);
        byte green = (byte)((float)(paletteEntry->peGreen + 8) / 255.0f * 3.0f);
        byte blue = (byte)((float)(paletteEntry->peBlue + 8) / 255.0f * 3.0f);
        m_palette[loop] = red | (green << 2) | (blue << 4);
    }
}

void GGPalette::Write(const std::string& outputFolder, const std::string& outputName, const std::string& bank)
{
	WriteGGPaletteHeaderFile(outputFolder, outputName, bank);
	WriteGGPaletteSourceFile(outputFolder, outputName, bank);
}


void GGPalette::WriteGGPaletteHeaderFile(const std::string& outputFolder, 
                                             const std::string& outputName,
                                             const std::string& bank)
{
	std::string headerFilename = outputName + ".h";
	std::ofstream headerfile(outputFolder + headerFilename, std::ios::trunc);

    // header guard
    std::string headerGuard = outputName + "_PALETTE_INCLUDE_H";
    std::transform(headerGuard.begin(), headerGuard.end(), headerGuard.begin(), ::toupper);
    headerfile << "// File generated by SpriteMaster. https://github.com/pw32x/ninjagirl\n";
    headerfile << "#ifndef " << headerGuard << "\n";
    headerfile << "#define " << headerGuard << "\n";
    headerfile << "\n";

	// includes
    headerfile << "#include \"palette_types.h\"\n";
    headerfile << "#include \"resource_types.h\"\n";
    headerfile << "\n";

	// exported types

    headerfile << "RESOURCE(" << bank << ") extern const PaletteResource " << outputName << ";\n"; 
    headerfile << "\n";

    // end header guard
    headerfile << "#endif\n\n";
    headerfile.close();
}

void GGPalette::WritePaletteValues(const std::string& outputName, std::ofstream& sourceFile)
{

    sourceFile << "const u8 " << outputName << "Values[16] = \n";
    sourceFile << "{\n";

    for (size_t loop = 0; loop < 16; loop++)
    {
        sourceFile << "    0x" << std::setw(2) << std::setfill('0') << std::hex << (int)m_palette[loop] << ",\n";
    }

    sourceFile << "};\n\n";
}

void GGPalette:: WritePaletteResource(const std::string& outputName, 
                                      std::ofstream& sourceFile,
                                      const std::string& bank)
{
    // final struct
    sourceFile << "const PaletteResource " << outputName << " = \n";
    sourceFile << "{\n";
    sourceFile << "    PALETTE_RESOURCE_TYPE, \n";
    sourceFile << "    " << outputName << "Values,\n";
    sourceFile << "};\n";
}

void GGPalette::WriteGGPaletteSourceFile(const std::string& outputFolder, 
                                             const std::string& outputName,
                                             const std::string& bank)
{
	std::ofstream sourceFile(outputFolder + outputName + ".c");

    // includes
    sourceFile << "#include \"" << outputName << ".h\"\n";
    sourceFile << "\n";

    WritePaletteValues(outputName, sourceFile);
    WritePaletteResource(outputName, sourceFile, bank);

    sourceFile.close();
}


}