#include "..\stdafx.h"
#include "AnimationFrame.h"

#include "..\Base\TileStore.h"
#include "..\GraphicsGale\GraphicsGaleObject.h"
#include "..\Utils\BitmapUtils.h"
#include "..\Utils\SpriteUtils.h"
#include "..\Utils\TileUtils.h"

#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

namespace SpriteMaster
{

GGAnimationFrame::GGAnimationFrame() 
: mFrameDelayTime(-1)
, mFrameNumber(-1)
{
}

void GGAnimationFrame::Init(int frameNumber, 
							const GraphicsGaleObject& ggo, 
							TileStore& tileStore, 
							AnimationProperties& animationProperties)
{
	mFrameNumber = frameNumber;
	GetGGInfo(ggo, animationProperties);
	BuildFrame(ggo, tileStore, m_sprites);
	BuildAdjoiningSprites();
}

void GGAnimationFrame::BuildAdjoiningSprites()
{
	int batchY = 0xffffffff;
	int batchItemCount = 0;

	const Sprite* firstSpriteOfBatch = nullptr;

	for (const auto& sprite : m_sprites)
	{
		// first sprite
		if (batchY == 0xffffffff)
		{
			batchY = sprite.yPositionOffset;
			firstSpriteOfBatch = &sprite;
		}
		else if (sprite.yPositionOffset != batchY)
		{
			AdjoiningSprite adjoiningSprite;

			adjoiningSprite.adjoiningCount = batchItemCount;
			adjoiningSprite.sprite = firstSpriteOfBatch;

			batchItemCount = 0;

			m_adjoiningSprites.push_back(adjoiningSprite);
			batchY = sprite.yPositionOffset;
			firstSpriteOfBatch = &sprite;
		}

		batchItemCount++;
	}

	AdjoiningSprite adjoiningSprite;
	adjoiningSprite.adjoiningCount = batchItemCount;
	adjoiningSprite.sprite = firstSpriteOfBatch;
	m_adjoiningSprites.push_back(adjoiningSprite);
}

void GGAnimationFrame::GetGGInfo(const GraphicsGaleObject& ggo, 
								 AnimationProperties& animationProperties)
{
	LONG ggFrameDelayTime = ggo.getFrameInfo(mFrameNumber, 2); // the 2 means frame time?
	mFrameDelayTime = (LONG)(myround((float)ggFrameDelayTime / 17.0f)); // 17 ms per frame

	const int length =  1024;
	char frameName[length];
	ggo.getFrameName(mFrameNumber, frameName, length);


    std::istringstream iss(frameName);
    std::queue<std::string> tokens;
    std::string token;

    while (iss >> token) 
	{
        tokens.push(token);
    }

	while (!tokens.empty())
	{
		std::string token = tokens.front();
		tokens.pop();

		if (strstr(token.c_str(), "%") || 
			strstr(token.c_str(), "Copy_") ||
			strstr(token.c_str(), "Frame"))
			continue;

		if (strstr(token.c_str(), "OFFSET"))
		{
			token = tokens.front();
			animationProperties.mOffsetX = stoi(token);
			tokens.pop();

			token = tokens.front();
			animationProperties.mOffsetY = stoi(token);
			tokens.pop();
		}
		else if (token == "NOLOOP")
		{
			mNextFrame = NO_LOOP;
		}
		else if (token == "LOOP")
		{
			int lastFrameWithAnimationFrameName = 0;
			
			if (!animationProperties.animationFrameNames.empty())
				animationProperties.animationFrameNames.rbegin()->first;

			mNextFrame = lastFrameWithAnimationFrameName;
		}
		else if (token == "JUMPTO")
		{
			token = tokens.front();
			mNextFrame = stoi(token);
			tokens.pop();
		}
		else
		{
			animationProperties.animationFrameNames.insert({mFrameNumber, token});
			m_startsAnimation = true;
		}
	}


}



void SliceImageIntoTiles(BYTE* byteData, 
						 int width, 
						 int height, 
						 int topMost, 
						 int bottomMost, 
						 TileStore& tileStore, 
						 std::vector<Sprite>& sprites)
{

	// SMS tiles are always 8x8
	int sliceWidth = 8;
	int sliceHeight = 8;

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

		SpriteUtils::FindLeftRightExtentsForSlice(byteData, width, sliceTop, sliceBottom, leftMost, rightMost, false);
		
        //printf("\nLeft/Right Extents - Left: %d, Right: %d\n", leftMost, rightMost);

        int rectWidth = (rightMost - leftMost);

        // no pixels detected, just skip.
        if (rectWidth < 0)
        {
            continue;
        }

        int maxNumberOfTilesInSlice = 0;
        
        if (rectWidth % sliceWidth != 0)
        {
            maxNumberOfTilesInSlice = (rectWidth / sliceWidth) + 1;
        }
        else
        {
            maxNumberOfTilesInSlice = (rectWidth / sliceWidth);
        }

        for (int tileLoop = 0; tileLoop < maxNumberOfTilesInSlice; tileLoop++)
        {
			// Start with a full sliceWidth x sliceHeight area.
            int startPositionX = leftMost + (tileLoop * sliceWidth);
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
			std::vector<BYTE> tileData;
			bool atLeastOnePixel = SpriteUtils::CopySpriteFromByteData(byteData, width, tileData, startPositionX, startPositionY, endPositionX, endPositionY, false);

            if (!atLeastOnePixel)
            {
				continue;
			}

			// See if the sprite already exists.
			int tileStoreIndex = 0;
			
			tileStoreIndex = tileStore.AddOrGetTileInStore(tileData, true);

			// Create tile properties
			Sprite sprite;
			sprite.tileStoreIndex = tileStoreIndex;
			sprite.xPositionOffset = startPositionX;
			sprite.yPositionOffset = startPositionY;

			sprites.push_back(sprite);
        }
    }
}

						 
void SliceImageInto8x16Tiles(BYTE* byteData, 
						 int width, 
						 int height, 
						 int topMost, 
						 int bottomMost, 
						 TileStore& tileStore, 
						 std::vector<Sprite>& sprites)
{

	// Tall SMS tiles are 8x16
	int sliceWidth = 8;
	int sliceHeight = 16;

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

		SpriteUtils::FindLeftRightExtentsForSlice(byteData, width, sliceTop, sliceBottom, leftMost, rightMost, false);
		
        //printf("\nLeft/Right Extents - Left: %d, Right: %d\n", leftMost, rightMost);

        int rectWidth = (rightMost - leftMost);

        // no pixels detected, just skip.
        if (rectWidth < 0)
        {
            continue;
        }

        int maxNumberOfTilesInSlice = 0;
        
        if (rectWidth % sliceWidth != 0)
        {
            maxNumberOfTilesInSlice = (rectWidth / sliceWidth) + 1;
        }
        else
        {
            maxNumberOfTilesInSlice = (rectWidth / sliceWidth);
        }

        for (int tileLoop = 0; tileLoop < maxNumberOfTilesInSlice; tileLoop++)
        {
			// Start with a full sliceWidth x sliceHeight area.
            int startPositionX = leftMost + (tileLoop * sliceWidth);
            int endPositionX = startPositionX + sliceWidth;

            if (endPositionX > rightMost)
            {
                endPositionX = rightMost;
            }

			// top tile
            int startPositionY = sliceTop;
            int endPositionY = sliceTop + 8; // sliceBottom;

            if (endPositionY > bottomMost)
            {
                endPositionY = bottomMost;
            }

			// Get the sprite. This also modifies the start and end positions to the area actually copied.
			std::vector<BYTE> topTileData;
			bool atLeastOnePixelInTopTile = SpriteUtils::CopySpriteFromByteData(byteData, 
																				width, 
																				topTileData, 
																				startPositionX, 
																				startPositionY, 
																				endPositionX, 
																				endPositionY, 
																				true);

			// bottom tile
            startPositionX = leftMost + (tileLoop * sliceWidth);
            endPositionX = startPositionX + sliceWidth;

            if (endPositionX > rightMost)
            {
                endPositionX = rightMost;
            }

            startPositionY = sliceTop + 8;
            endPositionY = sliceBottom; 

            if (endPositionY > bottomMost)
            {
                endPositionY = bottomMost;
            }

			std::vector<BYTE> bottomTileData;
			bool atLeastOnePixelInBottomTile = SpriteUtils::CopySpriteFromByteData(byteData, 
																				   width, 
																				   bottomTileData, 
																				   startPositionX, 
																				   startPositionY, 
																				   endPositionX, 
																				   endPositionY, 
																				   true);



            if (!atLeastOnePixelInTopTile && !atLeastOnePixelInBottomTile)
            {
				continue;
			}

			// See if the sprite already exists.
			//int tileStoreIndex = AddOrGetTileInStore(tileStore, tileData);

			// TODO  check for duplicates of tile pairs.
			tileStore.AddTile(topTileData);
			tileStore.AddTile(bottomTileData);

			// Create tile properties
			Sprite sprite;
			sprite.tileStoreIndex = tileStore.GetStoreTileCount() - 2; // sprite index are even
			sprite.xPositionOffset = startPositionX;
			sprite.yPositionOffset = startPositionY - 8;

			sprites.push_back(sprite);
        }
    }
}


void GGAnimationFrame::BuildFrame(const GraphicsGaleObject& ggo, 
								  TileStore& tileStore, 
								  std::vector<Sprite>& sprites)
{
	HBITMAP				hBitmap;
	BITMAP				bitmapInfo;

	hBitmap = ggo.getBitmap(mFrameNumber, 0);
	GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);
	BYTE* byteData = BitmapUtils::CreateByteDataFromBitmap(bitmapInfo);

	int topMost;
	int bottomMost;

	SpriteUtils::FindTopAndBottomExtents(byteData, 
										 bitmapInfo.bmWidth, 
										 bitmapInfo.bmHeight, 
										 &topMost, 
										 &bottomMost, 
										 false);

	SliceImageInto8x16Tiles(byteData, 
							bitmapInfo.bmWidth, 
							bitmapInfo.bmHeight, 
							topMost, 
							bottomMost, 
							tileStore, 
							sprites);

	delete [] byteData;
}
}