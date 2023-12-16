#include "..\stdafx.h"
#include "TileUtils.h"
#include "SpriteUtils.h"

namespace SpriteMaster
{

bool TilesAreIdentical(const Tile& firstTile, const Tile& secondTile)
{
	return std::equal(firstTile.begin(), firstTile.end(), secondTile.begin());
}

bool TilesAreMirroredOnX(const Tile& firstTile, const Tile& secondTile)
{
	for (int loopy = 0; loopy < TILE_HEIGHT; loopy++)
	{
		for (int loopx = 0; loopx < TILE_WIDTH; loopx++)
		{
			if (firstTile[((TILE_WIDTH - 1) - loopx) + (loopy * TILE_WIDTH)] != secondTile[loopx + (loopy * TILE_WIDTH)])
			{
				return false;
			}
		}
	}

	return true;
}


bool TilesAreMirroredOnY(const Tile& firstTile, const Tile& secondTile)
{
	for (int loopy = 0; loopy < TILE_HEIGHT; loopy++)
	{
		for (int loopx = 0; loopx < TILE_WIDTH; loopx++)
		{
			if (firstTile[loopx + (((TILE_HEIGHT - 1) - loopy) * TILE_WIDTH)] != secondTile[loopx + (loopy * TILE_WIDTH)])
			{
				return false;
			}
		}
	}

	return true;
}

bool TilesAreMirroredOnXY(const Tile& firstTile, const Tile& secondTile)
{
	for (int loopy = 0; loopy < TILE_HEIGHT; loopy++)
	{
		for (int loopx = 0; loopx < TILE_WIDTH; loopx++)
		{
			if (firstTile[((TILE_WIDTH - 1) - loopx) + (((TILE_HEIGHT - 1) - loopy) * TILE_WIDTH)] != secondTile[loopx + (loopy * TILE_WIDTH)])
			{
				return false;
			}
		}
	}

	return true;
}

bool TilesAreIdenticalOrMirrored(const Tile& firstTile, const Tile& secondTile)
{
	return TilesAreIdentical(firstTile, secondTile) ||
		   TilesAreMirroredOnX(firstTile, secondTile) ||
		   TilesAreMirroredOnY(firstTile, secondTile) ||
		   TilesAreMirroredOnXY(firstTile, secondTile);
}

bool StoreContainsIdenticalOrMirroredTile(std::vector<Tile>& tileStore, const Tile& tileToFind)
{
	for (auto& storedTile : tileStore)
	{
		if (TilesAreIdenticalOrMirrored(storedTile, tileToFind))
		{
			return true;
		}
	}

	return false;
}

int AddOrGetTileInStore(std::vector<Tile>& tileStore, const Tile& tileToFind, bool removeDuplicates)
{
	if (removeDuplicates)
	{
		for (size_t loop = 0; loop < tileStore.size(); loop++)
		{
			const Tile& storedTile = tileStore[loop];

			if (std::equal(storedTile.begin(), storedTile.end(), tileToFind.begin()))
			{
				return loop;
			}
		}
	}

	// Tile didn't exist already so create one.
	tileStore.push_back(tileToFind);

	return tileStore.size() - 1;
}

}