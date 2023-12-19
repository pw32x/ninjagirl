#pragma once

#include <vector>
#include "..\Base\Sprite.h"
#include "..\Base\TileTypes.h"

#define TILE_WIDTH 8
#define TILE_HEIGHT 8

// sms sprites are assumed to be configured to 8x16
#define SPRITE_WIDTH 8
#define SPRITE_HEIGHT 16

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
										int& topMost, 
										int& bottomMost, 
										bool sliceSpritesOnGrid);

	static void FindLeftRightExtentsForSlice(BYTE* byteData, 
											 int width, 
											 int sliceTop, 
											 int sliceBottom, 
											 int& leftMost, 
											 int& rightMost, 
											 bool sliceSpritesOnGrid);

	static bool CopyTileFromByteData(BYTE* byteData, 
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