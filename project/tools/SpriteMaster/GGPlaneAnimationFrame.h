#pragma once

#include "galefile151119\galefile.h"
#include <vector>
#include "Options.h"
#include "Sprite.h"

typedef RawSprite Tile;

#define PALETTE_SIZE 16

class GGPlaneAnimationFrame
{
public:
	GGPlaneAnimationFrame();
	void Init(int frameNumber, LPVOID galeFile, std::vector<Tile>& tiles, const Options& options, int& uniqueTileCount, int& maxUniqueTileCountPerFrame);

	int frameNumber() const { return m_FrameNumber; }
	int tileWidth() const { return m_tileWidth; }
	int tileHeight() const { return m_tileHeight; } 
	int getFrameDelayTime() const { return m_FrameDelayTime; }
	const std::vector<unsigned short>& frameData() const { return m_frame; }

	bool hasSameFrameData(const GGPlaneAnimationFrame* frame);

	const PALETTEENTRY* getPalette() const { return m_palette; } 

private:
	void GetFrameDelayTime(LPVOID galeFile);
	void BuildFrame(LPVOID galeFile, std::vector<Tile>& tiles, const Options& options, int& uniqueTileCount, int& maxUniqueTileCountPerFrame);

private:
	int							m_FrameNumber;
	LONG						m_FrameDelayTime;
	int							m_uniqueTileCount;
	std::vector<unsigned short> m_frame;
	int							m_tileWidth;
	int							m_tileHeight;

	PALETTEENTRY				m_palette[PALETTE_SIZE];
};
