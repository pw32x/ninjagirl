#include "stdafx.h"
#include "Options.h"
#include <string>

namespace SpriteMaster
{

Options::Options() 
: mSliceSpritesOnGrid(false),
  mSliceWidth(DEFAULT_SLICE_SIZE),
  mSliceHeight(DEFAULT_SLICE_SIZE),
  mCutSliceAsFrame(false),
  mBackgroundPlaneAnimation(false)
{

}

void Options::ProcessOptions(const std::string& filename)
{
	const char* sliceOnGridName = ".sliceongrid";
	int sliceOnGridIndex = filename.find(sliceOnGridName);
    mSliceSpritesOnGrid = (sliceOnGridIndex != std::string::npos);

	if (mSliceSpritesOnGrid)
	{
		mSliceWidth = 8;
		mSliceHeight = 8;
	}



	mBackgroundPlaneAnimation = (filename.find(".planeanim.") != std::string::npos);

	mCutSliceAsFrame = (filename.find(".cutsliceasframe.") != std::string::npos);

	mSMS8x16Sprites = (filename.find(".sms8x16.") != std::string::npos);

	if (mSMS8x16Sprites)
	{
		//mSliceSpritesOnGrid = true;
		mSliceWidth = 8;
		mSliceHeight = 16;
	}

	// store the sprites in such a way so that we can call the SMS_add****AdjoiningSprites functions
	// on them.
	mSMSBatchedSprites = (filename.find(".batch.") != std::string::npos) ||(filename.find(".batched.") != std::string::npos);

	mRemoveDuplicates = (filename.find(".nodedupe") == std::string::npos);

	// the animation will only be uploaded one frame at a time to the vdp. 
	// the vdp tile addresses in the sprites will start at 0 and not the index
	// of the sprite tiles location in the tile store.
	mStreamed = (filename.find(".streamed") != std::string::npos); 

	mTileAnimation = (filename.find(".animatedtileset") != std::string::npos); 
}

}