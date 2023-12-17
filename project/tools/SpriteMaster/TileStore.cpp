#include "TileStore.h"

#include "Utils/TileUtils.h"
#include <algorithm>


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

}
