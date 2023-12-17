#pragma once

#define WIN32_LEAN_AND_MEAN
#include "..\Base\TileStore.h"
#include <fstream>
#include <string>
#include <vector>

namespace SpriteMaster
{
	class WriteUtils
	{
	public:
		static std::string BuildFrameName(const std::string& outputName, int frameNumber);
		static void OutputTilePlanar(std::ofstream& sourceFile, const Tile& tile);
	};
}
