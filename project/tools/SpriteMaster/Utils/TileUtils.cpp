#include "..\stdafx.h"
#include "TileUtils.h"
#include "SpriteUtils.h"

namespace SpriteMaster
{

bool TileUtils::TilesAreIdentical(const Tile& firstTile, const Tile& secondTile)
{
	return std::equal(firstTile.begin(), firstTile.end(), secondTile.begin());
}

bool TileUtils::TilesAreMirroredOnX(const Tile& firstTile, const Tile& secondTile)
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


bool TileUtils::TilesAreMirroredOnY(const Tile& firstTile, const Tile& secondTile)
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

bool TileUtils::TilesAreMirroredOnXY(const Tile& firstTile, const Tile& secondTile)
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

bool TileUtils::TilesAreIdenticalOrMirrored(const Tile& firstTile, const Tile& secondTile)
{
	return TilesAreIdentical(firstTile, secondTile) ||
		   TilesAreMirroredOnX(firstTile, secondTile) ||
		   TilesAreMirroredOnY(firstTile, secondTile) ||
		   TilesAreMirroredOnXY(firstTile, secondTile);
}
}