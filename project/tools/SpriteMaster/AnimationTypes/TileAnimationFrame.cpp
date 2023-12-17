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
: mFrameDelayTime(-1)
, mFrameNumber(-1)
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

void GGTileAnimationFrame::GetGGInfo(const GraphicsGaleObject& ggo, AnimationProperties& animationProperties)
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