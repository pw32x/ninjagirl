#pragma once

#include "..\Base\Sprite.h"
#include "..\Base\TileStore.h"
#include "AnimationProperties.h"
#include "AnimationTypes.h"
#include <vector>

namespace SpriteMaster
{

class GraphicsGaleObject;

struct Sprite
{
	Sprite() :
		tileStoreIndex(-1),
		xPositionOffset(0),
		yPositionOffset(0)
	{

	}

	int tileStoreIndex;
    int xPositionOffset;
    int yPositionOffset;
};

struct AdjoiningSprite
{
	AdjoiningSprite() : adjoiningCount(0) {}

	int adjoiningCount;
	const Sprite* sprite;
};


class GGAnimationFrame
{
public:
	GGAnimationFrame();

	void Init(int frameNumber, 
			  const GraphicsGaleObject& ggo, 
	          TileStore& tileStore, 
			  AnimationProperties& animationProperties);

	LONG GetFrameDelayTime() const { return mFrameDelayTime; }

	const std::vector<Sprite>& getSprites() const { return m_sprites; }
	const std::vector<AdjoiningSprite>& getAdjoiningSprites() const { return m_adjoiningSprites; }

	int getFrameNumber() const { return mFrameNumber; }

	void setNextFrameIndex(int nextFrame) { mNextFrame = nextFrame; }
	int getNextFrameIndex() const { return mNextFrame; }

	bool startsAnimation() const { return m_startsAnimation; }

private:

	void GetGGInfo(const GraphicsGaleObject& ggo,  AnimationProperties& animationProperties);
	void BuildFrame(const GraphicsGaleObject& ggo, 
					TileStore& tileStore, 
					std::vector<Sprite>& sprites);

	void BuildAdjoiningSprites();

private:
	LONG			mFrameDelayTime;
	int				mFrameNumber;

	int				mNextFrame = NEXT_FRAME_NOT_SET;

	std::vector<Sprite> m_sprites;
	std::vector<AdjoiningSprite> m_adjoiningSprites;

	bool m_startsAnimation = false;
};
}