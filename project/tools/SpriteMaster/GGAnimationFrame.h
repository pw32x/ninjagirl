#pragma once

#include "galefile151119\galefile.h"
#include <vector>
#include "Options.h"
#include "Sprite.h"
#include "AnimationProperties.h"

class GGAnimationFrame
{
public:
	GGAnimationFrame();

	void Init(int frameNumber, 
			  LPVOID galeFile, 
	          std::vector<RawSprite>& rawSprites, 
			  std::vector<SpriteProperties>& spriteProperties, 
			  std::vector<SpriteArray>& spriteArrays,
			  const Options& options, 
			  AnimationProperties& animationProperties,
			  int& tileStartIndex);

	int GetSpriteArrayIndex() const { return mSpriteArrayIndex; }
	const std::vector<std::string>& GetFrameTriggerData() const { return mFrameTriggerData; }
	LONG GetFrameDelayTime() const { return mFrameDelayTime; }
	int	GetTileCount() const { return mTileCount; }

private:

	void BuildFrame(LPVOID galeFile, AnimationProperties& animationProperties);
	void BuildSprites(LPVOID galeFile, 
	                  std::vector<RawSprite>& rawSprites, 
					  std::vector<SpriteProperties>& spriteProperties, 
					  std::vector<SpriteArray>& spriteArrays,
					  const Options& options, 
					  int& tileStartIndex);

private:
	LONG			mFrameDelayTime;
	int				mSpriteArrayIndex;
	int				mFrameNumber;
	int				mTileCount;

	std::vector<std::string>	mFrameTriggerData;
};