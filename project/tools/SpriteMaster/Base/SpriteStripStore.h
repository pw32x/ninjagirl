#pragma once

#include "windows.h"
#include <vector>
#include <string>
#include "TileTypes.h"

namespace SpriteMaster
{

class SpriteStripStore
{
public:
	class SpriteStrip
	{
	public:
		int count;
		int tileStartIndex;
		std::vector<Tile> tiles;
	};

	SpriteStrip AddOrGetSpriteStrip(std::vector<Tile> stripTiles);

private:
	std::vector<SpriteStrip> m_spriteStrips;
};


}