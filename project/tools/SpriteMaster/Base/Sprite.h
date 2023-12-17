#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <vector>

struct RawSprite
{
	RawSprite():
		width(0),
		height(0),
		tileWidth(0),
		tileHeight(0)
	{
	}

    std::vector<BYTE> imageData;
	int width;
	int height;
    int tileWidth;
    int tileHeight;
	int tileStartIndex;
};

struct SpriteProperties
{
	SpriteProperties():
		rawSprite(-1),
		xPositionOffset(0),
		yPositionOffset(0),
		verticalFlip(0),
		horizontalFlip(0),
		xFlippedPositionOffset(0)
	{

	}

	int rawSprite;
    int xPositionOffset;
    int yPositionOffset;
	bool verticalFlip;
	bool horizontalFlip;
	int xFlippedPositionOffset;
};

typedef std::vector<int> SpriteArray;
