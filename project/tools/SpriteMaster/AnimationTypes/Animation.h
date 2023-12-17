#pragma once

#include "AnimationFrame.h"

#include "..\Base\TileStore.h"
#include "AnimationProperties.h"
#include "AnimationTypes.h"
#include <string>

namespace SpriteMaster
{

class GraphicsGaleObject;

class GGAnimation : public IAnimation
{
public:
	GGAnimation(const GraphicsGaleObject& ggo, 
				AnimationType animationType, 
				AnimationProperties& animationProperties);

	void Write(const std::string& outputFolder, const std::string& outputName, const std::string& bank);

	int GetTileCount() { return m_tileStore.GetStoreTileCount(); }

	const BITMAP& GetGeneralBitmapInfo() { return  m_generalBitmapInfo; }

private:
	void WriteSprites(const std::string& outputName, std::ofstream& sourceFile);
	void WriteSpritesBatched(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrames(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFramesBatched(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrameArray(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrameArrayBatched(const std::string& outputName, std::ofstream& sourceFile);
	void WriteAnimationStruct(const std::string& outputName, std::ofstream& sourceFile, const std::string& bank);
	void WriteAnimationStructBatched(const std::string& outputName, std::ofstream& sourceFile, const std::string& bank);

	void WriteGGAnimationHeaderFile(const std::string& outputFolder, const std::string& outputName, const std::string& bank);
	void WriteGGAnimationSourceFile(const std::string& outputFolder, const std::string& outputName, const std::string& bank);

private:
	const GraphicsGaleObject&		m_ggo;

	std::vector<GGAnimationFrame>	m_frames;
	TileStore						m_tileStore;
	int								m_totalFrameTime = 0;
	bool							m_isStreamed;
	AnimationProperties&			m_animationProperties;
	BITMAP							m_generalBitmapInfo;
	int								m_maxTilesInFrame;
};

}

