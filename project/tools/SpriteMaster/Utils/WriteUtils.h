#pragma once

#define WIN32_LEAN_AND_MEAN
#include "..\TileStore.h"
#include <fstream>
#include <string>
#include <vector>

namespace SpriteMaster
{
	std::string BuildFrameName(const std::string& outputName, int frameNumber);

	void WriteTileStore(const std::string& outputName, 
						std::ofstream& sourceFile, 
						const TileStore& tileStore);
}
