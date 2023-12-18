#include "..\stdafx.h"
#include "TileAnimationFrame.h"

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

GGTileAnimationFrame::GGTileAnimationFrame() 

{
}

void GGTileAnimationFrame::Init(int frameNumber, 
								const GraphicsGaleObject& ggo, 
								TileStore& tileStore, 
								AnimationProperties& animationProperties)
{
	mFrameNumber = frameNumber;
	GetGGInfo(ggo, animationProperties);
	BuildFrame(ggo, tileStore);
}


void CopyTileFromByteData(BYTE* byteData, 
						  int byteDataWidth, 
						  std::vector<BYTE>& tileData, 
						  int startPositionX, 
						  int startPositionY, 
						  int tileWidth, 
						  int tileHeight)
{
    for (int loopy = 0; loopy < tileHeight; loopy++)
    {
        for (int loopx = 0; loopx < tileWidth; loopx++)
        {
            BYTE byte = byteData[(startPositionX + loopx) + ((loopy + startPositionY) * byteDataWidth)];

            tileData[loopx + (loopy * tileWidth)] = byte;
        }
    }
}


int SliceImageIntoTiles(BYTE* byteData, 
						 int width, 
						 int height, 
						 TileStore& tileStore)
{

	// SMS tiles are always 8x8
	int tileWidth = 8;
	int tileHeight = 8;

	int tileCountX = width / tileWidth;
    int tileCountY = height / tileHeight;

	TileStore frameTileStore;

    // cut the image into slices, then sprites.
    for (int loopy = 0; loopy < tileCountY; loopy++)
    {
        for (int loopx = 0; loopx < tileCountX; loopx++)
        {
			// Get the tile
			Tile tileData(tileWidth * tileHeight);
			CopyTileFromByteData(byteData, 
								 width, 
								 tileData, 
								 loopx * tileWidth, 
								 loopy * tileHeight, 
								 tileWidth,
								 tileHeight);

			if (!frameTileStore.StoreContainsIdenticalOrMirroredTile(tileData))
				frameTileStore.AddTile(tileData);
        }
    }

	for (auto& tile : frameTileStore.GetTiles())
	{
		tileStore.AddTile(tile);
	}

	return frameTileStore.GetStoreTileCount();
}

void GGTileAnimationFrame::BuildFrame(const GraphicsGaleObject& ggo, 
									  TileStore& tileStore)
{
	HBITMAP				hBitmap;
	BITMAP				bitmapInfo;

	hBitmap = ggo.getBitmap(mFrameNumber, 0);
	GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);
	BYTE* byteData = BitmapUtils::CreateByteDataFromBitmap(bitmapInfo);

	mTileDataIndex = tileStore.GetStoreTileCount();

	mTilesInFrame = SliceImageIntoTiles(byteData, 
										bitmapInfo.bmWidth, 
										bitmapInfo.bmHeight, 
										tileStore);



	delete [] byteData;
}

}