#pragma once

#include <vector>
#include "..\Sprite.h"

#define TILE_WIDTH 8
#define TILE_HEIGHT 8


#define TILE_ATTR_FULL(pal, prio, flipV, flipH, index)   (((flipH) << 11) + ((flipV) << 12) + ((pal) << 13) + ((prio) << 15) + (index))

inline float myround(float val)
{
    return (float)floor(val + 0.5f);
}


void FindTopAndBottomExtents(BYTE* byteData, int width, int height, int* topMost, int* bottomMost, bool sliceSpritesOnGrid);
void FindLeftRightExtentsForSlice(BYTE* byteData, int width, int sliceTop, int sliceBottom, int& leftMost, int& rightMost, bool sliceSpritesOnGrid);
bool SpritesAreIdentical(const RawSprite& rawSprite, const std::vector<BYTE>& spriteData, int spriteWidth, int spriteHeight);
bool SpritesAreMirroredOnX(const RawSprite& rawSprite, const std::vector<BYTE>& spriteData, int spriteWidth, int spriteHeight);
bool SpritesAreMirroredOnY(const RawSprite& rawSprite, const std::vector<BYTE>& spriteData, int spriteWidth, int spriteHeight);
bool SpritesAreMirroredOnXY(const RawSprite& rawSprite, const std::vector<BYTE>& spriteData, int spriteWidth, int spriteHeight);
int FindRawSprite(const std::vector<RawSprite>& rawSprites, const std::vector<BYTE>& spriteData, int spriteWidth, int spriteHeight, bool checkFlipped, bool& verticalFlip, bool& horizontalFlip);
int FindSpriteProperties(const std::vector<SpriteProperties>& spriteProperties, const SpriteProperties& properties);
bool CopySpriteFromByteData(BYTE* byteData, int byteDataWidth, std::vector<BYTE>& spriteData, int& startPositionX, int& startPositionY, int& endPositionX, int& endPositionY, bool sliceOnGrid);
void CopyTileFromByteData(BYTE* byteData, int byteDataWidth, int byteDataHeight, std::vector<BYTE>& tileData, int startPositionX, int startPositionY);
void PrintSprite(const std::vector<BYTE>& spriteData, int spriteWidth, int spriteHeight);

void SliceImageIntoSprites(BYTE* byteData, 
						   int width, 
						   int height, 
						   int topMost, 
						   int bottomMost, 
						   std::vector<RawSprite>& rawSprites, 
						   std::vector<SpriteProperties>& spriteProperties,
						   std::vector<int>& spritePropertiesIndexes,
						   int& tileStartIndex,
						   int& tileCount,
						   bool sliceSpritesOnGrid,
						   int sliceWidth, 
						   int sliceHeight);

int FindSpriteArray(const std::vector<SpriteArray>& spriteArrays, const std::vector<int>& spritePropertiesIndexes);