#pragma once

#include <vector>
#include "..\Sprite.h"
#include "AnimationTypes.h"
#include "AnimationProperties.h"
#include "..\TileStore.h"

namespace SpriteMaster
{

class GraphicsGaleObject;

class GGTileAnimationFrame
{
public:
	GGTileAnimationFrame();

	void Init(int frameNumber, 
			  const GraphicsGaleObject& ggo, 
	          TileStore& tileStore, 
			  AnimationProperties& animationProperties);

	LONG GetFrameDelayTime() const { return mFrameDelayTime; }

	int GetTileDataIndex() const { return mTileDataIndex; }
	int GetTilesInFrame() const { return mTilesInFrame; }

	int getFrameNumber() const { return mFrameNumber; }

	void setNextFrameIndex(int nextFrame) { mNextFrame = nextFrame; }
	int getNextFrameIndex() const { return mNextFrame; }

	bool startsAnimation() const { return m_startsAnimation; }

private:

	void GetGGInfo(const GraphicsGaleObject& ggo, AnimationProperties& animationProperties);
	void BuildFrame(const GraphicsGaleObject& ggo, 
					TileStore& tileStore);

private:
	LONG			mFrameDelayTime;
	int				mFrameNumber;

	int				mTileDataIndex;
	int				mTilesInFrame;

	int				mNextFrame = NEXT_FRAME_NOT_SET;

	bool m_startsAnimation = false;
};

}