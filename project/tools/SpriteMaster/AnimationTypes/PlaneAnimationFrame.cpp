#include "..\stdafx.h"
#include "PlaneAnimationFrame.h"
#include "..\Utils\BitmapUtils.h"
#include "..\Utils\SpriteUtils.h"
#include "..\Utils\TileUtils.h"
#include <set>
#include "..\Base\palette_utils.h"
#include "..\Base\TileStore.h"
#include "..\GraphicsGale\GraphicsGaleObject.h"

namespace SpriteMaster
{

GGPlaneAnimationFrame::GGPlaneAnimationFrame()
: m_FrameDelayTime(-1),
  m_FrameNumber(-1),
  m_uniqueTileCount(0),
  m_tileWidth(0),
  m_tileHeight(0),
  m_palette()
{
}

void GGPlaneAnimationFrame::Init(int frameNumber, 
								 const GraphicsGaleObject& ggo, 
								 TileStore& tileStore, 
								 int& uniqueTileCount,
								 int& maxUniqueTileCountPerFrame)
{
	m_FrameNumber = frameNumber;
	GetFrameDelayTime(ggo);
	BuildFrame(ggo, tileStore, uniqueTileCount, maxUniqueTileCountPerFrame);

	HPALETTE palette = ggo.getPalette(m_FrameNumber);

	GetPaletteData(palette, m_palette);
}

void GGPlaneAnimationFrame::GetFrameDelayTime(const GraphicsGaleObject& ggo)
{
	LONG ggFrameDelayTime = ggo.getFrameInfo(m_FrameNumber, 2); // the 2 means frame time?
	m_FrameDelayTime = (LONG)(myround((float)ggFrameDelayTime / 17.0f)); // 17 ms per frame
}

void GGPlaneAnimationFrame::BuildFrame(const GraphicsGaleObject& ggo, 
									   TileStore& tileStore, 
									   int& uniqueTileCount, 
									   int& maxUniqueTileCountPerFrame)
{
	HBITMAP				hBitmap;
	BITMAP				bitmapInfo;

	hBitmap = ggo.getBitmap(m_FrameNumber, 0);
	GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);
	BYTE* byteData = BitmapUtils::CreateByteDataFromBitmap(bitmapInfo);

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

			SpriteUtils::CopyTileFromByteData(byteData, 
											  bitmapInfo.bmWidth, 
											  bitmapInfo.bmHeight, 
											  tileData, 
											  startPositionX, 
											  startPositionY);

		

			
			// See if the sprite already exists.
			bool verticalFlip = false;
			bool horizontalFlip = false;

			int tileIndex = tileStore.AddOrGetTileInStore(tileData);
			uniqueTileCount++;

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