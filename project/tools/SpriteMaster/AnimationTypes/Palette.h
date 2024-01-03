#pragma once

#include "AnimationFrame.h"

#include "..\Base\TileStore.h"
#include "AnimationProperties.h"
#include "AnimationTypes.h"
#include <string>
#include "../Base/SpriteStripStore.h"

namespace SpriteMaster
{

class GraphicsGaleObject;

class GGPalette : public AnimationBase
{
public:
	GGPalette(const GraphicsGaleObject& ggo);
	void Write(const std::string& outputFolder, const std::string& outputName, const std::string& bank);

private:

	void WritePaletteValues(const std::string& outputName, std::ofstream& sourceFile);
	void WritePaletteResource(const std::string& outputName, std::ofstream& sourceFile, const std::string& bank);

	void WriteGGPaletteHeaderFile(const std::string& outputFolder, const std::string& outputName, const std::string& bank);
	void WriteGGPaletteSourceFile(const std::string& outputFolder, const std::string& outputName, const std::string& bank);

private:
	const GraphicsGaleObject&		m_ggo;
	byte m_palette[16];
};

}

