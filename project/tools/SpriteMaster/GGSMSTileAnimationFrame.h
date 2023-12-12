#pragma once

#include "galefile151119\galefile.h"
#include <vector>
#include "Options.h"
#include "Sprite.h"
#include "AnimationProperties.h"
#include "SMSCommon.h"

namespace sms
{

class GGTileAnimationFrame
{
public:
	GGTileAnimationFrame();

	void Init(int frameNumber, 
			  LPVOID galeFile, 
	          std::vector<Tile>& tileStore, 
			  const Options& options, 
			  AnimationProperties& animationProperties);

	LONG GetFrameDelayTime() const { return mFrameDelayTime; }

	int GetTileDataIndex() const { return mTileDataIndex; }
	int GetTilesInFrame() const { return mTilesInFrame; }

	int getFrameNumber() const { return mFrameNumber; }

	void setNextFrameIndex(int nextFrame) { mNextFrame = nextFrame; }
	int getNextFrameIndex() const { return mNextFrame; }

	bool startsAnimation() const { return m_startsAnimation; }

private:

	void GetGGInfo(LPVOID galeFile, AnimationProperties& animationProperties);
	void BuildFrame(LPVOID galeFile, 
					std::vector<Tile>& tileStore, 
					const Options& options);

private:
	LONG			mFrameDelayTime;
	int				mFrameNumber;

	int				mTileDataIndex;
	int				mTilesInFrame;

	int				mNextFrame = NEXT_FRAME_NOT_SET;

	bool m_startsAnimation = false;
};

}