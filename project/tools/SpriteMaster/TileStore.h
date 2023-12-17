#pragma once

#include "windows.h"
#include <vector>
#include <string>

namespace SpriteMaster
{

typedef std::vector<BYTE> Tile;

class TileStore
{
public:
	bool StoreContainsIdenticalOrMirroredTile(const Tile& tileToFind) const;

	void AddTile(const Tile& tile) { m_store.push_back(tile); }
	int AddOrGetTileInStore(const Tile& tileToFind, bool removeDuplicates = true);

	int GetStoreTileCount() const { return m_store.size(); }

	const std::vector<Tile>& GetTiles() const { return m_store; }

private:
	std::vector<Tile>	m_store;
};



}