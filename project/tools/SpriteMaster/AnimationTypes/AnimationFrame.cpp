#include "..\stdafx.h"
#include "AnimationFrame.h"

#include "..\Base\TileStore.h"
#include "..\Base\SpriteStripStore.h"
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
{
}

void GGAnimationFrame::Init(int frameNumber, 
							const GraphicsGaleObject& ggo, 
							SpriteStripStore& spriteStripStore,
							AnimationProperties& animationProperties)
{
	mFrameNumber = frameNumber;
	GetGGInfo(ggo, animationProperties);
	BuildFrame(ggo, spriteStripStore, m_sprites);
}

/*
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
*/

int GGAnimationFrame::GetMaxTilesInAFrame()
{
	int maxTilesInAFrame = 0;

	for (const auto& sprite : m_sprites)
	{
		maxTilesInAFrame += sprite.m_spriteStrip.count * 2;
	}

	return maxTilesInAFrame;
}

void GGAnimationFrame::SliceImageIntoStrips(BYTE* bitmap, 
											int bitmapWidth, 
											int bitmapHeight, 
											SpriteStripStore& spriteStripStore,
											std::vector<GGAnimationFrame::Sprite>& sprites)
{
	int topMost;
	int bottomMost;

	SpriteUtils::FindTopAndBottomExtents(bitmap, 
										 bitmapWidth, 
										 bitmapHeight, 
										 topMost, 
										 bottomMost, 
										 false);

	int rectHeight = (bottomMost - topMost);	

	int numberOfRows = 0;
	if (rectHeight % SPRITE_HEIGHT != 0)
	{
		numberOfRows = (rectHeight / SPRITE_HEIGHT) + 1;
	}
	else
	{
		numberOfRows = (rectHeight / SPRITE_HEIGHT);
	}


	// go through the sprite row-by-row, cutting the row into sprite slices
	for (int rowLoop = 0; rowLoop < numberOfRows; rowLoop++)
	{
		// compute the row's top and bottom y positions in the bitmap
		int rowTop = topMost + (rowLoop * SPRITE_HEIGHT);
		int rowBottom = rowTop + SPRITE_HEIGHT;
		if (rowBottom > bottomMost)
		{
			rowBottom = bottomMost;
		}

		// get the left and right most positions for the row.
		int leftMost;
		int rightMost;

		SpriteUtils::FindLeftRightExtentsForSlice(bitmap, 
												  bitmapWidth, 
												  rowTop, 
												  rowBottom, 
												  leftMost, 
												  rightMost, 
												  false);

		int rectWidth = (rightMost - leftMost);

		// no pixels detected, skip this row.
		if (rectWidth < 0)
		{
			continue;
		}

		// Go through the row's sprites, building strips along the way
		int rowSpriteCounter = 0;
		int stripSpriteCounter = 0;
		int stripMaxSpriteCount = 4;
		int numSprites = 0;
		if (rectWidth % SPRITE_WIDTH != 0)
		{
			numSprites = (rectWidth / SPRITE_WIDTH) + 1;
		}
		else
		{
			numSprites = (rectWidth / SPRITE_WIDTH);
		}

		std::vector<Tile> tiles;

		int stripX = leftMost;

		bool startedStrip = FALSE;
		int stripStartX = 0;

		bool continueProcessing = TRUE;
		while (continueProcessing)
		{
			// get top and bottom 8x8 tiles for the 8x16 sprite.
			//
			Tile topTile;
			bool atLeastOnePixelInTopTile = SpriteUtils::CopyTileFromBitmap(bitmap, 
																			bitmapWidth, 
																			bitmapHeight,
																			topTile, 
																			stripX, 
																			rowTop);

			Tile bottomTile;
			bool atLeastOnePixelInBottomTile = SpriteUtils::CopyTileFromBitmap(bitmap, 
																			   bitmapWidth, 
																			   bitmapHeight,
																			   bottomTile, 
																			   stripX, 
																			   rowTop + TILE_HEIGHT);

			bool foundAtLeastOnePixel = atLeastOnePixelInTopTile || atLeastOnePixelInBottomTile;

			if (foundAtLeastOnePixel && !startedStrip)
			{
				startedStrip = TRUE;
				stripStartX = stripX;
			}

			bool finishStrip = FALSE;

			// we're in the middle of building a strip
			if (startedStrip)
			{
				if (foundAtLeastOnePixel)
				{
					tiles.push_back(topTile);
					tiles.push_back(bottomTile);

					stripSpriteCounter++;
				}
				else
				{
					finishStrip = TRUE;
				}
			}

			// increment counters
			stripX += SPRITE_WIDTH;
			rowSpriteCounter++;

			// check limits
			bool finishRow = FALSE;

			if (rowSpriteCounter > numSprites - 1)
			{
				finishStrip = TRUE;
				finishRow = TRUE;
			}

			if (stripSpriteCounter > stripMaxSpriteCount - 1)
			{
				stripSpriteCounter = 0;
				finishStrip = TRUE;
			}

			if (finishStrip)
			{
				Sprite sprite(stripStartX, 
							  rowTop, 
							  spriteStripStore.AddOrGetSpriteStrip(tiles));
				m_sprites.push_back(sprite);

				tiles.clear();
				stripSpriteCounter = 0;
				startedStrip = FALSE;
			}

			if (finishRow)
			{
				continueProcessing = FALSE;
			}
		}
	}
}

void GGAnimationFrame::BuildFrame(const GraphicsGaleObject& ggo, 
								  SpriteStripStore& spriteStripStore,
								  std::vector<Sprite>& sprites)
{
	HBITMAP				hBitmap;
	BITMAP				bitmapInfo;

	hBitmap = ggo.getBitmap(mFrameNumber, 0);
	GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);
	BYTE* byteData = BitmapUtils::CreateByteDataFromBitmap(bitmapInfo);

	SliceImageIntoStrips(byteData, 
						 bitmapInfo.bmWidth, 
						 bitmapInfo.bmHeight, 
						 spriteStripStore,
						 m_sprites);

	delete [] byteData;
}
}