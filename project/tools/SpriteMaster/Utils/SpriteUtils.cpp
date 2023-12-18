#include "..\stdafx.h"
#include "SpriteUtils.h"

//#define MAX_SPRITE_SIZE 32

namespace SpriteMaster
{

void SpriteUtils::FindTopAndBottomExtents(BYTE* byteData, 
										  int width, 
										  int height, 
										  int* topMost, 
										  int* bottomMost, 
										  bool sliceSpritesOnGrid)
{
    //printf("\n\n Byte Array:\n");

	if (sliceSpritesOnGrid)
	{
		*topMost = 0;
		*bottomMost = height;
		return;
	}

    // find top and bottom extents of image within bitmap
    *topMost = height;
    *bottomMost = 0;

    for (int loopy = 0; loopy < height; loopy++)
    {
        for (int loopx = 0; loopx < width; loopx++)
        {
            BYTE byte = byteData[loopx + (loopy * width)];

            //  printf("%02d,", byte);

            if (byte > 0)
            {
                if (loopy < *topMost) *topMost = loopy;
                if (loopy > *bottomMost) *bottomMost = loopy;
            }
        }
        //printf("\n");
    }

    (*bottomMost)++;

    //printf("\nTop/Bottom Extents - Top: %d, Bottom: %d\n", *topMost, *bottomMost);
}


void SpriteUtils::FindLeftRightExtentsForSlice(BYTE* byteData, int width, int sliceTop, int sliceBottom, int& leftMost, int& rightMost, bool sliceSpritesOnGrid)
{
	// Determine the width of the slice.
	if (sliceSpritesOnGrid)
	{
		// if slicing on the grid, then the width is the full width of the image.
		leftMost = 0;
		rightMost = width;
	}
	else
	{
		leftMost = width;
		rightMost = 0;

		// find the smallest width taken up by the pixel data and so to later cut that
		// into 32x32.
		for (int loopy = sliceTop; loopy < sliceBottom; loopy++)
		{
			for (int loopx = 0; loopx < width; loopx++)
			{
				BYTE byte = byteData[loopx + (loopy * width)];

				if (byte > 0)
				{
					if (loopx < leftMost) leftMost = loopx;
					if (loopx > rightMost) rightMost = loopx;
				}
			}
		}

		rightMost++;
	}
}

void SpriteUtils::CopyTileFromByteData(BYTE* byteData, int byteDataWidth, int byteDataHeight, std::vector<BYTE>& tileData, int startPositionX, int startPositionY)
{
	int endPositionX = startPositionX + TILE_WIDTH; 
	int endPositionY = startPositionY + TILE_HEIGHT;

	if (endPositionX > byteDataWidth)
	{
		endPositionY = byteDataWidth;
	}

	if (endPositionY > byteDataHeight)
	{
		endPositionY = byteDataHeight;
	}


	int left = startPositionX;
	int top = startPositionY;
	int right = endPositionX;
	int bottom = endPositionY;

	tileData.resize(TILE_WIDTH * TILE_HEIGHT);

    int j = 0;

    bool atLeastOnePixel = false;

    for (int loopy = top; loopy < bottom; loopy++, j++)
    {
        int i = 0;
        for (int loopx = left; loopx < right; loopx++, i++)
        {
            BYTE byte = byteData[loopx + (loopy * byteDataWidth)];

            tileData[i + (j * TILE_WIDTH)] = byte;
        }
    }
}

bool SpriteUtils::CopySpriteFromByteData(BYTE* byteData, 
										 int byteDataWidth, 
										 std::vector<BYTE>& spriteData, 
										 int& startPositionX, 
										 int& startPositionY, 
										 int& endPositionX, 
										 int& endPositionY, 
										 bool sliceOnGrid)
{
    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;

	if (sliceOnGrid)
	{
		left = startPositionX;
		top = startPositionY;
		right = endPositionX - 1;
		bottom = endPositionY - 1;
	}
	else
	{
		right = 0;
		bottom = 0;
		left = endPositionX;
		top = endPositionY;

		// Find area actually used.
		for (int loopy = startPositionY; loopy < endPositionY; loopy++)
		{
			for (int loopx = startPositionX; loopx < endPositionX; loopx++)
			{
				BYTE byte = byteData[loopx + (loopy * byteDataWidth)];

				if (byte > 0)
				{
					if (loopx < left) left = loopx;
					if (loopy < top) top = loopy;
					if (loopx > right) right = loopx;
					if (loopy > bottom) bottom = loopy;
				}
			}
		}
	}

	// sprite width needs to be multiple of 8.
	int spriteWidth = ((right - left) / 8) * 8 + 8;
	int spriteHeight = ((bottom - top) / 8) * 8 + 8;


	spriteData.resize(spriteWidth * spriteHeight);
	std::fill(spriteData.begin(), spriteData.end(), 0);

    int j = 0;

    bool atLeastOnePixel = false;

    for (int loopy = top; loopy <= bottom; loopy++, j++)
    {
        int i = 0;
        for (int loopx = left; loopx <= right; loopx++, i++)
        {
            BYTE byte = byteData[loopx + (loopy * byteDataWidth)];

            if (byte > 0)
            {
                atLeastOnePixel = true;
            }

            spriteData[i + (j * spriteWidth)] = byte;
        }
    }

	startPositionX = left;
	startPositionY = top;
	endPositionX = left + spriteWidth;
	endPositionY = top + spriteHeight;

	return atLeastOnePixel;
}

void SpriteUtils::PrintSprite(const std::vector<BYTE>& spriteData, int spriteWidth, int spriteHeight)
{
	FILE* file;
	int error = fopen_s(&file, "output.txt", "a");

	for (int loopy = 0; loopy < spriteHeight; loopy++)
	{
		for (int loopx = 0; loopx < spriteWidth; loopx++)
		{
			BYTE pixel = spriteData[loopx + (loopy * spriteWidth)];

			if (pixel > 0)
				fprintf(file, "%02x", pixel);
			else
				fprintf(file, "..");
		}

		fprintf(file, "\n");
	}

	fprintf(file, "                                                                     \n");

	fclose(file);
}


}