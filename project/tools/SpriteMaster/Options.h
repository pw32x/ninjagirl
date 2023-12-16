#pragma once

#include <string>

namespace SpriteMaster
{

class Options
{
public:
	const static int VDP_SIZE = 1535 - 1;
	const static int DEFAULT_SLICE_SIZE = 32;
	Options();
	void ProcessOptions(const std::string& filename);

public:

	bool mSliceSpritesOnGrid;
	int mSliceWidth;
	int mSliceHeight;
	bool mBackgroundPlaneAnimation;
	bool mCutSliceAsFrame;
	bool mSMS8x16Sprites = false;
	bool mSMSBatchedSprites = false;
	bool mRemoveDuplicates = true;
	bool mStreamed = false;
	bool mTileAnimation = false;
};

}