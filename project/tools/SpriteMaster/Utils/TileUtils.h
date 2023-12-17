#pragma once

#include <vector>
#include "..\Base\TileStore.h"

namespace SpriteMaster
{
	class TileUtils
	{
	public:
		static bool TilesAreIdentical(const Tile& firstTile, const Tile& secondTile);
		static bool TilesAreMirroredOnX(const Tile& firstTile, const Tile& secondTile);
		static bool TilesAreMirroredOnY(const Tile& firstTile, const Tile& secondTile);
		static bool TilesAreMirroredOnXY(const Tile& firstTile, const Tile& secondTile);
		static bool TilesAreIdenticalOrMirrored(const Tile& firstTile, const Tile& secondTile);
	};
}