#pragma once

#include "TileAnimationFrame.h"
#include <string>
#include "AnimationProperties.h"
#include "AnimationTypes.h"
#include "..\TileStore.h"

namespace SpriteMaster
{

class GraphicsGaleObject;

class GGTileAnimation : public IAnimation
{
public:
	GGTileAnimation(const GraphicsGaleObject& ggo, 
					AnimationProperties& animationProperties);

	void Write(const std::string& outputFolder, const std::string& outputName, const std::string& bank);

	int GetTileCount() { return m_tileStore.GetStoreTileCount(); }

	const BITMAP& GetGeneralBitmapInfo() { return  m_generalBitmapInfo; }

private:
	void WriteFrames(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrameArray(const std::string& outputName, std::ofstream& sourceFile);
	void WriteAnimationStruct(const std::string& outputName, std::ofstream& sourceFile, const std::string& bank);

	void WriteHeaderFile(const std::string& outputFolder, const std::string& outputName, const std::string& bank);
	void WriteSourceFile(const std::string& outputFolder, const std::string& outputName, const std::string& bank);

private:
	const GraphicsGaleObject& m_ggo;

	std::vector<GGTileAnimationFrame>	m_frames;
	TileStore							m_tileStore;
	int									m_totalFrameTime = 0;
	AnimationProperties&				m_animationProperties;
	BITMAP								m_generalBitmapInfo;
	int									m_tilesInFrame;
};

}

