#include "..\stdafx.h"
#include "TileStore.h"

#include "../Utils/TileUtils.h"
#include "../Utils/WriteUtils.h"
#include <algorithm>
#include <ostream>


namespace SpriteMaster
{

bool TileStore::StoreContainsIdenticalOrMirroredTile(const Tile& tileToFind) const
{
	for (auto& storedTile : m_store)
	{
		if (TileUtils::TilesAreIdenticalOrMirrored(storedTile, tileToFind))
		{
			return true;
		}
	}

	return false;
}

int TileStore::AddOrGetTileInStore(const Tile& tileToFind, bool removeDuplicates)
{
	if (removeDuplicates)
	{
		for (size_t loop = 0; loop < m_store.size(); loop++)
		{
			const Tile& storedTile = m_store[loop];

			if (std::equal(storedTile.begin(), storedTile.end(), tileToFind.begin()))
			{
				return loop;
			}
		}
	}

	// Tile didn't exist already so create one.
	m_store.push_back(tileToFind);

	return m_store.size() - 1;
}

void TileStore::WriteTileStore(const std::string& outputName, 
							   std::ofstream& sourceFile) const
{
	std::string outputTileDataName = outputName + "TileData";

	int tileIndex = 0;
	int totalTiles = 0;
	sourceFile << "unsigned char const " << outputTileDataName << "[" << GetStoreTileCount() * 32 << "] = // " << GetStoreTileCount() << "tiles x " << "32 bytes" << "\n";
	sourceFile << "{\n";

	int tileCount = 0;

	for (const auto& tile : m_store)
	{
		sourceFile << "// tile: " << tileCount << "\n";
		tileCount++;

		WriteUtils::OutputTilePlanar(sourceFile, tile);
	}

	sourceFile << "};\n\n";
}

}
