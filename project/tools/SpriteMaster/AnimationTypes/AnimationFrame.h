#pragma once

#include "..\Base\Sprite.h"
#include "..\Base\TileStore.h"
#include "..\Base\SpriteStripStore.h"
#include "AnimationProperties.h"
#include "AnimationTypes.h"
#include <vector>

namespace SpriteMaster
{

class GraphicsGaleObject;


class GGAnimationFrame : public AnimationFrameBase
{
public:
	struct Sprite
	{
	public:
		Sprite(int xPositionOffset,
			   int yPositionOffset,
			   const SpriteStripStore::SpriteStrip& spriteStrip)
			: m_xPositionOffset(xPositionOffset)
			, m_yPositionOffset(yPositionOffset)
			, m_spriteStrip(spriteStrip)
		{}

		int m_xPositionOffset;
		int m_yPositionOffset;
		const SpriteStripStore::SpriteStrip m_spriteStrip;
	};

public:
	GGAnimationFrame();

	void Init(int frameNumber, 
			  const GraphicsGaleObject& ggo, 
			  SpriteStripStore& spriteStripStore,
			  AnimationProperties& animationProperties);

	const std::vector<Sprite>& getSprites() const { return m_sprites; }

	int GetMaxTilesInAFrame();

private:
	void BuildFrame(const GraphicsGaleObject& ggo, 
					SpriteStripStore& spriteStripStore,
					std::vector<Sprite>& sprites);

	void SliceImageIntoStrips(BYTE* bitmap, 
							  int bitmapWidth, 
							  int bitmapHeight, 
							  SpriteStripStore& spriteStripStore,
							  std::vector<Sprite>& sprites);

private:
	std::vector<Sprite> m_sprites;
};
}