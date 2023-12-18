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
							TileStore& tileStore, 
							SpriteStripStore& spriteStripStore,
							AnimationProperties& animationProperties)
{
	mFrameNumber = frameNumber;
	GetGGInfo(ggo, animationProperties);
	BuildFrame(ggo, tileStore, spriteStripStore, m_sprites);
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

void GGAnimationFrame::SliceImageIntoStrips(BYTE* bitmap, 
											int bitmapWidth, 
											int bitmapHeight, 
											TileStore& tileStore, 
											SpriteStripStore& spriteStripStore,
											std::vector<GGAnimationFrame::Sprite>& sprites)
{
	int topMost;
	int bottomMost;

	SpriteUtils::FindTopAndBottomExtents(bitmap, 
										 bitmapWidth, 
										 bitmapHeight, 
										 &topMost, 
										 &bottomMost, 
										 false);

// don't forget to not remove duplicates if m_
}

void GGAnimationFrame::BuildFrame(const GraphicsGaleObject& ggo, 
								  TileStore& tileStore, 
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
						 tileStore, 
						 spriteStripStore,
						 m_sprites);

	delete [] byteData;
}
}