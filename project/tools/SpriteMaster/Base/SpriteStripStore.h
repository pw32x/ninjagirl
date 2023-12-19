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

	const SpriteStrip& AddOrGetSpriteStrip(const std::vector<Tile>& stripTiles);

	int GetTileCount() const { return m_tileCount; }

	void WriteTileStore(const std::string& outputName, 
						std::ofstream& sourceFile) const;

private:
	std::vector<SpriteStrip> m_spriteStrips;
	int m_tileCount = 0;
};


}