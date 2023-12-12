#include "stdafx.h"
#include "GGSMSPlaneAnimationFrame.h"
#include "BitmapUtils.h"
#include "SpriteUtils.h"
#include "TileUtils.h"
#include <set>
#include "palette.h"


namespace sms
{

GGPlaneAnimationFrame::GGPlaneAnimationFrame()
: m_FrameDelayTime(-1),
  m_FrameNumber(-1),
  m_uniqueTileCount(0)
{
}

void GGPlaneAnimationFrame::Init(int frameNumber, 
								 LPVOID galeFile, 
								 std::vector<Tile>& tiles, 
								 const Options& options, 
								 int& uniqueTileCount,
								 int& maxUniqueTileCountPerFrame)
{
	m_FrameNumber = frameNumber;
	GetFrameDelayTime(galeFile);
	BuildFrame(galeFile, tiles, options, uniqueTileCount, maxUniqueTileCountPerFrame);

	HPALETTE palette = ggGetPalette(galeFile, m_FrameNumber);

	GetPaletteData(palette, m_palette);
}

void GGPlaneAnimationFrame::GetFrameDelayTime(LPVOID galeFile)
{
	LONG ggFrameDelayTime = ggGetFrameInfo(galeFile, m_FrameNumber, 2); // the 2 means frame time?
	m_FrameDelayTime = (LONG)(myround((float)ggFrameDelayTime / 17.0f)); // 17 ms per frame
}

void GGPlaneAnimationFrame::BuildFrame(LPVOID galeFile, 
									   std::vector<Tile>& tileStore, 
									   const Options& options, 
									   int& uniqueTileCount, 
									   int& maxUniqueTileCountPerFrame)
{
	HBITMAP				hBitmap;
	BITMAP				bitmapInfo;

	hBitmap = ggGetBitmap(galeFile, m_FrameNumber, 0);
	GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);
	BYTE* byteData = CreateByteDataFromBitmap(bitmapInfo);

	m_tileWidth = (((bitmapInfo.bmWidth - 1) / TILE_WIDTH)) + 1;
	m_tileHeight = (((bitmapInfo.bmHeight - 1) / TILE_HEIGHT)) + 1;

	m_frame.resize(m_tileWidth * m_tileHeight);

	std::set<int> uniqueTilesUsed;

	// break apart into tiles/sprites
	for (int loopy = 0; loopy < m_tileHeight; loopy++)
	{
		for (int loopx = 0; loopx < m_tileWidth; loopx++)
		{
			std::vector<BYTE> tileData;
			int startPositionX = loopx * TILE_WIDTH;
			int startPositionY = loopy * TILE_HEIGHT;

			CopyTileFromByteData(byteData, 
								 bitmapInfo.bmWidth, 
								 bitmapInfo.bmHeight, 
								 tileData, 
								 startPositionX, 
								 startPositionY);

		

			
			// See if the sprite already exists.
			bool verticalFlip = false;
			bool horizontalFlip = false;

			int tileIndex = AddOrGetTileInStore(tileStore, tileData);
			uniqueTileCount++;

			/*
			int tileIndex = FindRawSprite(tiles, tileData, TILE_WIDTH, TILE_HEIGHT, true, verticalFlip, horizontalFlip);

			if (tileIndex == -1)
			{
				// Tile didn't exist already so create one.
				tiles.push_back(RawSprite());
				RawSprite& sprite = tiles.back();
				sprite.imageData.assign(tileData.begin(), tileData.end());
				sprite.width = TILE_WIDTH;
				sprite.height = TILE_HEIGHT;
				sprite.tileWidth = 1;
				sprite.tileHeight = 1;
				sprite.tileStartIndex = uniqueTileCount;

				// 
				tileIndex = uniqueTileCount;

				// We've added a new tile, so update statistics
				uniqueTileCount++;
			}
			*/

			uniqueTilesUsed.insert(tileIndex);

			//#define TILE_ATTR_FULL(pal, prio, flipV, flipH, index)   (((flipH) << 11) + ((flipV) << 12) + ((pal) << 13) + ((prio) << 15) + (index))
			m_frame[loopx + (loopy * m_tileWidth)] = TILE_ATTR_FULL(0, 0, (int)verticalFlip, (int)horizontalFlip, tileIndex);
		}
	}

	m_uniqueTileCount = uniqueTilesUsed.size();

	if (maxUniqueTileCountPerFrame < static_cast<int>(uniqueTilesUsed.size()))
	{
		maxUniqueTileCountPerFrame = uniqueTilesUsed.size();
	}

	delete [] byteData;
}


bool GGPlaneAnimationFrame::hasSameFrameData(const GGPlaneAnimationFrame* frame)
{
	return (m_frame.size() == frame->frameData().size()) && (std::equal(m_frame.begin(), m_frame.end(), frame->frameData().begin()));
}

}