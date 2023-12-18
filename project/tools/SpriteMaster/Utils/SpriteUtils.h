#pragma once

#include <vector>
#include "..\Base\Sprite.h"

#define TILE_WIDTH 8
#define TILE_HEIGHT 8

#define TILE_ATTR_FULL(pal, prio, flipV, flipH, index)   (((flipH) << 11) + ((flipV) << 12) + ((pal) << 13) + ((prio) << 15) + (index))

inline float myround(float val)
{
    return (float)floor(val + 0.5f);
}

namespace SpriteMaster
{

class SpriteUtils
{
public:
	static void FindTopAndBottomExtents(BYTE* byteData, 
										int width, 
										int height, 
										int* topMost, 
										int* bottomMost, 
										bool sliceSpritesOnGrid);

	static void FindLeftRightExtentsForSlice(BYTE* byteData, 
											 int width, 
											 int sliceTop, 
											 int sliceBottom, 
											 int& leftMost, 
											 int& rightMost, 
											 bool sliceSpritesOnGrid);

	static bool CopySpriteFromByteData(BYTE* byteData, 
									   int byteDataWidth, 
									   std::vector<BYTE>& spriteData, 
									   int& startPositionX, 
									   int& startPositionY, 
									   int& endPositionX, 
									   int& endPositionY, 
									   bool sliceOnGrid);

	static void CopyTileFromByteData(BYTE* byteData, 
									 int byteDataWidth, 
									 int byteDataHeight, 
									 std::vector<BYTE>& tileData, 
									 int startPositionX, 
									 int startPositionY);

	static void PrintSprite(const std::vector<BYTE>& spriteData, 
							int spriteWidth, 
							int spriteHeight);
};

}