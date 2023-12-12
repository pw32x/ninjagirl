#include "stdafx.h"
#include "GGAnimationFrame.h"
#include "BitmapUtils.h"
#include "SpriteUtils.h"

//#define MAX_SPRITE_SIZE 32

GGAnimationFrame::GGAnimationFrame() 
: mFrameDelayTime(-1),
  mFrameNumber(-1),
  mTileCount(0)
{
}

void GGAnimationFrame::Init(int frameNumber, 
							LPVOID galeFile, 
							std::vector<RawSprite>& rawSprites, 
							std::vector<SpriteProperties>& spriteProperties, 
							std::vector<SpriteArray>& spriteArrays,
							const Options& options, 
							AnimationProperties& animationProperties,
							int& tileStartIndex)
{
	mFrameNumber = frameNumber;
	BuildFrame(galeFile, animationProperties);
	BuildSprites(galeFile, rawSprites, spriteProperties, spriteArrays, options, tileStartIndex);
}

void GGAnimationFrame::BuildFrame(LPVOID galeFile, AnimationProperties& animationProperties)
{
	LONG ggFrameDelayTime = ggGetFrameInfo(galeFile, mFrameNumber, 2); // the 2 means frame time?
	mFrameDelayTime = (LONG)(myround((float)ggFrameDelayTime / 17.0f)); // 17 ms per frame

	const int length =  256;
	char frameName[length];
	ggGetFrameName(galeFile, mFrameNumber, frameName, length);

	if (strstr(frameName, "FRAME_TRIGGER_SPAWN"))
	{
		char* token = strtok(frameName, " "); 
 		mFrameTriggerData.push_back(token);

		char number[256];

		token = strtok(NULL, " "); 
		int spawnX = atoi(token) - animationProperties.mOffsetX;
		_itoa(spawnX, number, 10);

		mFrameTriggerData.push_back(number);

		token = strtok(NULL, " "); 
		int spawnY = atoi(token) - animationProperties.mOffsetY;
		_itoa(spawnY, number, 10);

		mFrameTriggerData.push_back(number);
	}
	else if (strstr(frameName, "ANIMPROP_"))
	{
		char* token = strtok(frameName, " "); 

		if (strcmp(frameName, "ANIMPROP_OFFSET") == 0)
		{
			token = strtok(NULL, " "); 
			animationProperties.mOffsetX = atoi(token);

			token = strtok(NULL, " "); 
			animationProperties.mOffsetY = atoi(token);
		}
	}
}


void GGAnimationFrame::BuildSprites(LPVOID galeFile, 
						 std::vector<RawSprite>& rawSprites, 
						 std::vector<SpriteProperties>& spriteProperties, 
						 std::vector<SpriteArray>& spriteArrays,
						 const Options& options, 
						 int& tileStartIndex)
{
	HBITMAP				hBitmap;
	BITMAP				bitmapInfo;

	hBitmap = ggGetBitmap(galeFile, mFrameNumber, 0);
	GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);
	BYTE* byteData = CreateByteDataFromBitmap(bitmapInfo);

	int topMost;
	int bottomMost;

	FindTopAndBottomExtents(byteData, 
							bitmapInfo.bmWidth, 
							bitmapInfo.bmHeight, 
							&topMost, 
							&bottomMost, 
							options.mSliceSpritesOnGrid);

	std::vector<int> spritePropertiesIndexes;

	SliceImageIntoSprites(byteData, 
						  bitmapInfo.bmWidth, 
						  bitmapInfo.bmHeight, 
						  topMost, 
						  bottomMost, 
						  rawSprites, 
						  spriteProperties, 
						  spritePropertiesIndexes, 
						  tileStartIndex, 
						  mTileCount, 
						  options.mSliceSpritesOnGrid,
						  options.mSliceWidth,
						  options.mSliceHeight);

	int spriteArrayIndex = FindSpriteArray(spriteArrays, spritePropertiesIndexes);

	if (spriteArrayIndex == -1)
	{
		spriteArrays.push_back(spritePropertiesIndexes);
		spriteArrayIndex = spriteArrays.size() - 1;
	}

	mSpriteArrayIndex = spriteArrayIndex;

	delete [] byteData;
}