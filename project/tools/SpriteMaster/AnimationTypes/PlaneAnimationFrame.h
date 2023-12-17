#pragma once

#include <vector>
#include "..\Base\Sprite.h"
#include "..\Base\TileStore.h"

#define PALETTE_SIZE 16

namespace SpriteMaster
{
class GraphicsGaleObject;

class GGPlaneAnimationFrame
{
public:
	GGPlaneAnimationFrame();
	void Init(int frameNumber, 
			  const GraphicsGaleObject& ggo, 
			  TileStore& tileStore, 
			  int& uniqueTileCount, 
			  int& maxUniqueTileCountPerFrame);

	int frameNumber() const { return m_FrameNumber; }
	int tileWidth() const { return m_tileWidth; }
	int tileHeight() const { return m_tileHeight; } 
	int getFrameDelayTime() const { return m_FrameDelayTime; }
	const std::vector<unsigned short>& frameData() const { return m_frame; }

	bool hasSameFrameData(const GGPlaneAnimationFrame* frame);

	const PALETTEENTRY* getPalette() const { return m_palette; } 

private:
	void GetFrameDelayTime(const GraphicsGaleObject& ggo);
	void BuildFrame(const GraphicsGaleObject& ggo, 
					TileStore& tileStore, 
					int& uniqueTileCount, 
					int& maxUniqueTileCountPerFrame);

private:
	int							m_FrameNumber;
	LONG						m_FrameDelayTime;
	int							m_uniqueTileCount;
	std::vector<unsigned short> m_frame;
	int							m_tileWidth;
	int							m_tileHeight;

	PALETTEENTRY				m_palette[PALETTE_SIZE];
};

}