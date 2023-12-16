#include "..\stdafx.h"
#include "SpriteUtils.h"

//#define MAX_SPRITE_SIZE 32

void FindTopAndBottomExtents(BYTE* byteData, int width, int height, int* topMost, int* bottomMost, bool sliceSpritesOnGrid)
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


void FindLeftRightExtentsForSlice(BYTE* byteData, int width, int sliceTop, int sliceBottom, int& leftMost, int& rightMost, bool sliceSpritesOnGrid)
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

bool SpritesAreIdentical(const RawSprite& rawSprite, const std::vector<BYTE>& spriteData, int spriteWidth, int spriteHeight)
{
	if (rawSprite.width != spriteWidth || rawSprite.height != spriteHeight)
	{
		return false;
	}

	return std::equal(rawSprite.imageData.begin(), rawSprite.imageData.end(), spriteData.begin());
}

bool SpritesAreMirroredOnX(const RawSprite& rawSprite, const std::vector<BYTE>& spriteData, int spriteWidth, int spriteHeight)
{
	if (rawSprite.width != spriteWidth || rawSprite.height != spriteHeight)
	{
		return false;
	}

	for (int loopy = 0; loopy < spriteHeight; loopy++)
	{
		for (int loopx = 0; loopx < spriteWidth; loopx++)
		{
			if (rawSprite.imageData[((spriteWidth - 1) - loopx) + (loopy * spriteWidth)] != spriteData[loopx + (loopy * spriteWidth)])
			{
				return false;
			}
		}
	}

	return true;
}


bool SpritesAreMirroredOnY(const RawSprite& rawSprite, const std::vector<BYTE>& spriteData, int spriteWidth, int spriteHeight)
{
	if (rawSprite.width != spriteWidth || rawSprite.height != spriteHeight)
	{
		return false;
	}

	for (int loopy = 0; loopy < spriteHeight; loopy++)
	{
		for (int loopx = 0; loopx < spriteWidth; loopx++)
		{
			if (rawSprite.imageData[loopx + (((spriteHeight - 1) - loopy) * spriteWidth)] != spriteData[loopx + (loopy * spriteWidth)])
			{
				return false;
			}
		}
	}

	return true;
}

bool SpritesAreMirroredOnXY(const RawSprite& rawSprite, const std::vector<BYTE>& spriteData, int spriteWidth, int spriteHeight)
{
	if (rawSprite.width != spriteWidth || rawSprite.height != spriteHeight)
	{
		return false;
	}

	for (int loopy = 0; loopy < spriteHeight; loopy++)
	{
		for (int loopx = 0; loopx < spriteWidth; loopx++)
		{
			if (rawSprite.imageData[((spriteWidth - 1) - loopx) + (((spriteHeight - 1) - loopy) * spriteWidth)] != spriteData[loopx + (loopy * spriteWidth)])
			{
				return false;
			}
		}
	}

	return true;
}


int FindRawSprite(const std::vector<RawSprite>& rawSprites, 
				  const std::vector<BYTE>& spriteData, 
				  int spriteWidth, 
				  int spriteHeight, 
				  bool checkFlipped,
				  bool& verticalFlip, 
				  bool& horizontalFlip)
{
	verticalFlip = false;
	horizontalFlip = false;


	for (size_t loop = 0; loop < rawSprites.size(); loop++)
	{
		const RawSprite& rawSprite = rawSprites[loop];
		
		if (rawSprite.width != spriteWidth || rawSprite.height != spriteHeight)
		{
			continue;
		}

		if (SpritesAreIdentical(rawSprite, spriteData, spriteWidth, spriteHeight))
		{
			return loop;
		} 
		
		if (!checkFlipped)
			continue;

		if (SpritesAreMirroredOnX(rawSprite, spriteData, spriteWidth, spriteHeight))
		{
			horizontalFlip = true;
			return loop;
		}

		if (SpritesAreMirroredOnY(rawSprite, spriteData, spriteWidth, spriteHeight))
		{
			verticalFlip = true;
			return loop;
		}

		if (SpritesAreMirroredOnXY(rawSprite, spriteData, spriteWidth, spriteHeight))
		{
			verticalFlip = true;
			horizontalFlip = true;
			return loop;
		}
	}

	return -1;
}

int FindSpriteProperties(const std::vector<SpriteProperties>& spriteProperties, const SpriteProperties& properties)
{
	for (size_t loop = 0; loop < spriteProperties.size(); loop++)
	{
		const SpriteProperties& sp = spriteProperties[loop];

		if (sp.rawSprite == properties.rawSprite &&
		    sp.xPositionOffset == properties.xPositionOffset &&
			sp.yPositionOffset == properties.yPositionOffset &&
			sp.verticalFlip == properties.verticalFlip &&
			sp.horizontalFlip == properties.horizontalFlip)
		{
			return loop;
		}
	}

	return -1;
}

void CopyTileFromByteData(BYTE* byteData, int byteDataWidth, int byteDataHeight, std::vector<BYTE>& tileData, int startPositionX, int startPositionY)
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

bool CopySpriteFromByteData(BYTE* byteData, 
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

void PrintSprite(const std::vector<BYTE>& spriteData, int spriteWidth, int spriteHeight)
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
						   int sliceHeight)
{
    int rectHeight = (bottomMost - topMost);	

    int numberOfSlices = 0;
    if (rectHeight % sliceHeight != 0)
    {
        numberOfSlices = (rectHeight / sliceHeight) + 1;
    }
    else
    {
        numberOfSlices = (rectHeight / sliceHeight);
    }


    // cut the image into slices, then sprites.
    for (int sliceLoop = 0; sliceLoop < numberOfSlices; sliceLoop++)
    {
        // find left and right extents for slice.
        int sliceTop = (sliceLoop * sliceHeight) + topMost;
        int sliceBottom = sliceTop + sliceHeight;
        if (sliceBottom > bottomMost)
        {
            sliceBottom = bottomMost;
        }

        int leftMost;
        int rightMost;

		FindLeftRightExtentsForSlice(byteData, width, sliceTop, sliceBottom, leftMost, rightMost, sliceSpritesOnGrid);
		
        //printf("\nLeft/Right Extents - Left: %d, Right: %d\n", leftMost, rightMost);

        int rectWidth = (rightMost - leftMost);

        // no pixels detected, just skip.
        if (rectWidth < 0)
        {
            continue;
        }

        int maxNumberOfSpritesInSlice = 0;
        
        if (rectWidth % sliceWidth != 0)
        {
            maxNumberOfSpritesInSlice = (rectWidth / sliceWidth) + 1;
        }
        else
        {
            maxNumberOfSpritesInSlice = (rectWidth / sliceWidth);
        }

        for (int spriteLoop = 0; spriteLoop < maxNumberOfSpritesInSlice; spriteLoop++)
        {
			// Start with a full sliceWidth x sliceHeight area.
            int startPositionX = leftMost + (spriteLoop * sliceWidth);
            int endPositionX = startPositionX + sliceWidth;

            if (endPositionX > rightMost)
            {
                endPositionX = rightMost;
            }

            int startPositionY = sliceTop;
            int endPositionY = sliceBottom;

            if (endPositionY > bottomMost)
            {
                endPositionY = bottomMost;
            }

			// Get the sprite. This also modifies the start and end positions to the area actually copied.
			std::vector<BYTE> spriteData;
			bool atLeastOnePixel = CopySpriteFromByteData(byteData, width, spriteData, startPositionX, startPositionY, endPositionX, endPositionY, sliceSpritesOnGrid);

            if (!atLeastOnePixel)
            {
				continue;
			}

			int spriteWidth = endPositionX - startPositionX;
			int spriteHeight = endPositionY - startPositionY;

			// See if the sprite already exists.
			bool verticalFlip = false;
			bool horizontalFlip = false;
			int rawSpriteIndex = FindRawSprite(rawSprites, spriteData, spriteWidth, spriteHeight, true, verticalFlip, horizontalFlip);

			if (rawSpriteIndex == -1)
			{
				//PrintSprite(spriteData, spriteWidth, spriteHeight);

				// Sprite didn't exist already so create one.
				rawSprites.push_back(RawSprite());
				RawSprite& sprite = rawSprites.back();
				sprite.imageData.assign(spriteData.begin(), spriteData.end());
				sprite.width = spriteWidth;
				sprite.height = spriteHeight;
				sprite.tileWidth = spriteWidth / 8;
				sprite.tileHeight = spriteHeight / 8;
				sprite.tileStartIndex = tileStartIndex;
				rawSpriteIndex = rawSprites.size() - 1;

				// We've added a new raw sprite, so update statistics
				int tilesPerSprite = rawSprites[rawSpriteIndex].tileWidth * rawSprites[rawSpriteIndex].tileHeight;
				tileStartIndex += tilesPerSprite;
				tileCount += tilesPerSprite;
			}

			// Create sprite properties
			SpriteProperties properties;
			properties.rawSprite = rawSpriteIndex;;
			properties.xPositionOffset = startPositionX;
			properties.yPositionOffset = startPositionY;
			properties.verticalFlip = verticalFlip;
			properties.horizontalFlip = horizontalFlip;

			properties.xFlippedPositionOffset = width - endPositionX;
			//spritesToExport[spritesLoop].xFlippedPositionOffset = generalBitmapInfo.bmWidth - (spritesToExport[spritesLoop].xPositionOffset + spriteWidth);

			int spritePropertiesIndex = FindSpriteProperties(spriteProperties, properties);

			if (spritePropertiesIndex == -1)
			{
				spriteProperties.push_back(properties);
				spritePropertiesIndex = spriteProperties.size() - 1;
			}

			spritePropertiesIndexes.push_back(spritePropertiesIndex);
        }
    }
}

int FindSpriteArray(const std::vector<SpriteArray>& spriteArrays, const std::vector<int>& spritePropertiesIndexes)
{
	for (size_t loop = 0; loop < spriteArrays.size(); loop++)
	{
		const SpriteArray& array = spriteArrays[loop];

		if (array.size() != spritePropertiesIndexes.size())
		{
			continue;
		}

		if (std::equal(array.begin(), array.end(), spritePropertiesIndexes.begin()))
		{
			return loop;
		}
	}

	return -1;
}

