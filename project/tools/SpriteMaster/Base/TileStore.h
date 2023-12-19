#pragma once

#include "windows.h"
#include <vector>
#include <string>
#include "TileTypes.h"

namespace SpriteMaster
{

class TileStore
{
public:
	bool StoreContainsIdenticalOrMirroredTile(const Tile& tileToFind) const;

	void AddTile(const Tile& tile) { m_store.push_back(tile); }
	int AddOrGetTileInStore(const Tile& tileToFind, bool removeDuplicates = true);

	int GetStoreTileCount() const { return m_store.size(); }

	const TileSet& GetTiles() const { return m_store; }


	void WriteTileStore(const std::string& outputName, 
					    std::ofstream& sourceFile) const;
private:
	TileSet	m_store;
};


}