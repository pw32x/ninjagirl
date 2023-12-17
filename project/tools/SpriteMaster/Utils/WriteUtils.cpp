#include "..\stdafx.h"
#include "WriteUtils.h"

#include "..\Base\TileStore.h"
#include "SpriteUtils.h"
#include <sstream>

namespace SpriteMaster
{

std::string WriteUtils::BuildFrameName(const std::string& outputName, int frameNumber)
{
    std::stringstream stringStream;
    stringStream << outputName << "Frame" << frameNumber;

    return stringStream.str();
}

void WriteToFourBytes(char value, char shift, BYTE bytes[4])
{
    bytes[0] |= ((value & 0x01) >> 0) << shift;
    bytes[1] |= ((value & 0x02) >> 1) << shift;
    bytes[2] |= ((value & 0x04) >> 2) << shift;
    bytes[3] |= ((value & 0x08) >> 3) << shift;
}

void ConvertToPlanar(int row, const BYTE* tileData, BYTE bytes[4])
{
    BYTE rowData[8];

    for (int loop = 0; loop < TILE_WIDTH; loop++)
    {
        BYTE value = tileData[loop + (row * TILE_WIDTH)];

        rowData[loop] = value;
    }

    for (int loop = 0; loop < 8; loop++)
    {
        WriteToFourBytes(rowData[loop], 7 - loop, bytes);
    }
}

std::string WriteByteAsHex(DWORD value)
{
    std::stringstream tempStringStream;

    tempStringStream << "0x";
    tempStringStream.width(2);
    tempStringStream.fill('0');
    tempStringStream << std::hex << value;

    return tempStringStream.str();
}

void WriteUtils::OutputTilePlanar(std::ofstream& sourceFile, const Tile& tile)
{
    for (int row = 0; row < TILE_HEIGHT; row++)
    {
        BYTE bytes[4];
        memset(bytes, 0, sizeof(bytes));
        ConvertToPlanar(row, tile.data(), bytes);

        sourceFile << "    ";

        for (int loop = 0; loop < 4; loop++)
        {
            sourceFile << WriteByteAsHex(bytes[loop]) <<", ";
        }

        sourceFile << "\n";
    }
}

}