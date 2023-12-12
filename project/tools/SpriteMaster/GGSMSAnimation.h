#pragma once

#include "GGSMSAnimationFrame.h"
#include <string>
#include "AnimationProperties.h"

namespace sms
{

class GGAnimation
{
public:
	GGAnimation(LPVOID galeFileHandle, const Options& options, AnimationProperties& animationProperties);
	void Write(const std::string& outputFolder, const std::string& outputName, const std::string& bank);

	int GetTileCount() { return m_tileStore.size(); }

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
	LPVOID m_galeFileHandle;

	std::vector<GGAnimationFrame>	m_frames;
	std::vector<Tile>				m_tileStore;
	int								m_totalFrameTime = 0;
	const Options&					m_options;
	AnimationProperties&			m_animationProperties;
	BITMAP							m_generalBitmapInfo;
	int								m_maxTilesInFrame;
};

}

