#include "..\stdafx.h"
#include "SpriteStripStore.h"

#include "..\Utils\WriteUtils.h"
#include <ostream>

namespace SpriteMaster
{

const SpriteStripStore::SpriteStrip& SpriteStripStore::AddOrGetSpriteStrip(const std::vector<Tile>& stripTiles)
{
	SpriteStrip spriteStrip;
	spriteStrip.count = stripTiles.size() / 2;
	spriteStrip.tileStartIndex = m_tileCount;
	spriteStrip.tiles = stripTiles;

	m_tileCount += stripTiles.size();

	m_spriteStrips.push_back(spriteStrip);

	return m_spriteStrips.back();
}

void SpriteStripStore::WriteTileStore(const std::string& outputName, 
									  std::ofstream& sourceFile) const
{
	std::string outputTileDataName = outputName + "TileData";

	int tileIndex = 0;
	int totalTiles = 0;
	sourceFile << "unsigned char const " << outputTileDataName << "[" << GetTileCount() * 32 << "] = // " << GetTileCount() << "tiles x " << "32 bytes" << "\n";
	sourceFile << "{\n";

	int tileCount = 0;

	for (const auto& spriteStrip : m_spriteStrips)
	{
		for (const auto& tile : spriteStrip.tiles)
		{
			sourceFile << "// tile: " << tileCount << "\n";
			tileCount++;

			WriteUtils::OutputTilePlanar(sourceFile, tile);
		}
	}

	sourceFile << "};\n\n";
}


}
