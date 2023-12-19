#include "..\stdafx.h"
#include "SpriteStripStore.h"

#include "..\Utils\WriteUtils.h"
#include <ostream>

namespace SpriteMaster
{

bool TileSetsAreTheSame(TileSet left, TileSet right)
{
	if (left.size() != right.size())
		return false;

	for (int loop = 0; loop < left.size(); loop++)
	{
		const Tile& leftTile = left[loop];
		const Tile& rightTile = right[loop];

		if (leftTile.size() != rightTile.size())
			return false;

		if (!std::equal(leftTile.begin(), leftTile.end(), rightTile.begin()))
			return false;
	}

	return true;
}

const SpriteStripStore::SpriteStrip& SpriteStripStore::AddOrGetSpriteStrip(const TileSet& stripTiles, 
																		   bool removeDuplicates)
{
	if (removeDuplicates)
	{
		// search the existing strips. if we don't find
		// one, fall through.
		for (const auto& spriteStrip : m_spriteStrips)
		{
			if (TileSetsAreTheSame(stripTiles, spriteStrip.tiles))
				return spriteStrip;
		}
	}

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
