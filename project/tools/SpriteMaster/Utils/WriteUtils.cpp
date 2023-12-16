#include "..\stdafx.h"
#include "WriteUtils.h"
#include <sstream>
#include "..\SMSCommon.h"

/*
DWORD SwitchEndian(DWORD value)
{
    unsigned char tempValue[4];
    tempValue[0] = (value >> 24) & 0xff;
    tempValue[1] = (value >> 16) & 0xff;
    tempValue[2] = (value >> 8) & 0xff;
    tempValue[3] = value & 0xff;

    DWORD tempDWORD = *(DWORD*)&tempValue;

    return (DWORD)tempDWORD;
}


std::string WriteDWORD(DWORD value)
{
    value = SwitchEndian(value);

    std::stringstream tempStringStream;

    tempStringStream << "0x";

    tempStringStream.width(8);
    tempStringStream.fill('0');
    tempStringStream << std::hex << value;

    return tempStringStream.str();
}

std::string WriteDWORDAsUShort(DWORD value)
{
    value = SwitchEndian(value);

    std::stringstream tempStringStream;


    unsigned short highValue = value >> 16;
    unsigned short lowValue = (unsigned short)(value & 0xffff);

    tempStringStream << "0x";
    tempStringStream.width(4);
    tempStringStream.fill('0');
    tempStringStream << std::hex << highValue;

    tempStringStream.width(4);
    tempStringStream.fill('0');
    tempStringStream << ", 0x" << std::hex << lowValue;

    return tempStringStream.str();
}


DWORD ConvertToTileDataRow(int x, int y, int tileWidth, const BYTE* spriteImageData)
{
    BYTE rowData[8];

    for (int loop = 0; loop <  8; loop++)
    {
        BYTE value = spriteImageData[(x + loop) + (y * tileWidth * 8)];

        rowData[loop] = value;
    }

    DWORD a, b, c, d;

    a = rowData[1] + (rowData[0] << 4);
    b = rowData[3] + (rowData[2] << 4);
    c = rowData[5] + (rowData[4] << 4);
    d = rowData[7] + (rowData[6] << 4);

    return a + (b << 8) + (c << 16) + (d << 24);
}


void OutputTile(std::ofstream& sourceFile, int tileCount, int tileX, int tileY, int tileWidth, const BYTE* spriteImageData)
{
    sourceFile << "// tile: " << tileCount << "\n";

    int tileStartX = tileX * 8;
    int tileEndX = tileStartX + 8;
    int tileStartY = tileY * 8;
    int tileEndY = tileStartY + 8;

    for (int loopy = tileStartY; loopy < tileEndY; loopy++)
    {
        DWORD tileDataRow = ConvertToTileDataRow(tileStartX, loopy, tileWidth, spriteImageData);

        sourceFile << "    " << WriteDWORDAsUShort(tileDataRow) <<",\n";
    }
}


void WriteIndividualTileData(std::ofstream& sourceFile, const std::vector<RawSprite>& sprites)
{
	int tileCount = 0;

    for (unsigned int spritesLoop = 0; spritesLoop < sprites.size(); spritesLoop++)
    {
		const RawSprite& rawSprite = sprites[spritesLoop];

        for (int loopx = 0; loopx < rawSprite.tileWidth; loopx++)
        {
            for (int loopy = 0; loopy < rawSprite.tileHeight; loopy++)
            {
                OutputTile(sourceFile, tileCount, loopx, loopy, rawSprite.tileWidth, rawSprite.imageData.data());
				tileCount++;
            }
        }
    }
}

void WriteTileData(const std::string& outputName, std::ofstream& sourceFile, const std::vector<RawSprite>& sprites)
{
	std::string outputTileDataName = outputName + "TileData";

    int tileIndex = 0;
    int totalTiles = 0;
    sourceFile << "unsigned short const " << outputTileDataName << "[" << sprites.size() * 16 << "] = \n";
    sourceFile << "{\n";

	WriteIndividualTileData(sourceFile, sprites);

    sourceFile << "};\n\n";
}
*/
std::string BuildFrameName(const std::string& outputName, int frameNumber)
{
    std::stringstream stringStream;
    stringStream << outputName << "Frame" << frameNumber;

    return stringStream.str();
}
/*
std::string BuildSpriteArrayName(const std::string& outputName, int index)
{
    std::stringstream stringStream;
    stringStream << outputName << "SpriteArray" << index;

    return stringStream.str();
}


std::string BuildSpriteName(const std::string outputName, int spritenumber)
{
    std::stringstream stringStream; 
    stringStream << outputName << "Sprite" << spritenumber;

    return stringStream.str();
}
*/

namespace SpriteMaster
{

// SMS
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

    for (int loop = 0; loop < SMS_TILE_WIDTH; loop++)
    {
        BYTE value = tileData[loop + (row * SMS_TILE_WIDTH)];

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

void OutputTilePlanar(std::ofstream& sourceFile, const Tile& tile)
{
    for (int row = 0; row < SMS_TILE_HEIGHT; row++)
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

void WriteTileStore(const std::string& outputName, std::ofstream& sourceFile, const std::vector<Tile>& tileStore)
{
	std::string outputTileDataName = outputName + "TileData";

    int tileIndex = 0;
    int totalTiles = 0;
    sourceFile << "unsigned char const " << outputTileDataName << "[" << tileStore.size() * 32 << "] = // " << tileStore.size() << "tiles x " << "32 bytes" << "\n";
    sourceFile << "{\n";

	int tileCount = 0;

    for (const auto& tile : tileStore)
    {
        sourceFile << "// tile: " << tileCount << "\n";
		tileCount++;

        OutputTilePlanar(sourceFile, tile);
    }

    sourceFile << "};\n\n";
}
}