#pragma once

#include "GGSMSTileAnimationFrame.h"
#include <string>
#include "AnimationProperties.h"

namespace sms
{

class GGTileAnimation
{
public:
	GGTileAnimation(LPVOID galeFileHandle, const Options& options, AnimationProperties& animationProperties);
	void Write(const std::string& outputFolder, const std::string& outputName, const std::string& bank);

	int GetTileCount() { return m_tileStore.size(); }

	const BITMAP& GetGeneralBitmapInfo() { return  m_generalBitmapInfo; }

private:
	void WriteFrames(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrameArray(const std::string& outputName, std::ofstream& sourceFile);
	void WriteAnimationStruct(const std::string& outputName, std::ofstream& sourceFile, const std::string& bank);

	void WriteHeaderFile(const std::string& outputFolder, const std::string& outputName, const std::string& bank);
	void WriteSourceFile(const std::string& outputFolder, const std::string& outputName, const std::string& bank);

private:
	LPVOID m_galeFileHandle;

	std::vector<GGTileAnimationFrame>	m_frames;
	std::vector<Tile>					m_tileStore;
	int									m_totalFrameTime = 0;
	const Options&						m_options;
	AnimationProperties&				m_animationProperties;
	BITMAP								m_generalBitmapInfo;
	int									m_tilesInFrame;
};

}

