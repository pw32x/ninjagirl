#pragma once

#include "..\Base\Sprite.h"
#include "..\Base\TileStore.h"
#include "AnimationProperties.h"
#include "AnimationTypes.h"
#include <vector>

namespace SpriteMaster
{

class GraphicsGaleObject;

class GGTileAnimationFrame : public AnimationFrameBase
{
public:
	GGTileAnimationFrame();

	void Init(int frameNumber, 
			  const GraphicsGaleObject& ggo, 
	          TileStore& tileStore, 
			  AnimationProperties& animationProperties);

	int GetTileDataIndex() const { return mTileDataIndex; }
	int GetTilesInFrame() const { return mTilesInFrame; }

private:

	void BuildFrame(const GraphicsGaleObject& ggo, 
					TileStore& tileStore);

private:


	int				mTileDataIndex;
	int				mTilesInFrame;

};

}