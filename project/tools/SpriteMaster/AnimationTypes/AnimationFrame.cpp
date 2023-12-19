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

		TileSet tiles;

		int stripX = leftMost;

		bool startedStrip = FALSE;
		int stripStartX = 0;

		bool continueProcessing = TRUE;
		while (continueProcessing)
		{
			// get top and bottom 8x8 tiles for the 8x16 sprite.
			//
			Tile topTile;
			bool atLeastOnePixelInTopTile = SpriteUtils::CopyTileFromByteData(bitmap, 
																			bitmapWidth, 
																			bitmapHeight,
																			topTile, 
																			stripX, 
																			rowTop);

			Tile bottomTile;
			bool atLeastOnePixelInBottomTile = SpriteUtils::CopyTileFromByteData(bitmap, 
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