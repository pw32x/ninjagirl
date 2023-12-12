#pragma once

#include "GGAnimationFrame.h"
#include <string>
#include "AnimationProperties.h"

class GGAnimation
{
public:
	GGAnimation(LPVOID galeFileHandle, const Options& options, AnimationProperties& animationProperties);
	void Write(const std::string& outputFolder, const std::string& outputName);

	int GetTileCount() { return m_tileCount; }

	const BITMAP& GetGeneralBitmapInfo() { return  m_generalBitmapInfo; }

private:
	void WriteSpritesData(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrameSpriteArrayData(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrames(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrameArray(const std::string& outputName, std::ofstream& sourceFile);
	void WriteAnimationStruct(const std::string& outputName, std::ofstream& sourceFile);

	void WriteGGAnimationHeaderFile(const std::string& outputFolder, const std::string& outputName);
	void WriteGGAnimationSourceFile(const std::string& outputFolder, const std::string& outputName);

private:
	LPVOID m_galeFileHandle;

	std::vector<GGAnimationFrame>	m_frames;
	std::vector<RawSprite>			m_rawSprites;
	std::vector<SpriteProperties>	m_spriteProperties;
	std::vector<SpriteArray>		m_spriteArrays;
	bool							mHasFrameTriggerData;
	int								m_tileCount = 0;
	int								m_totalFrameTime = 0;
	int								m_maxTilesPerFrame = 0;
	const Options&					m_options;
	AnimationProperties&			m_animationProperties;
	BITMAP							m_generalBitmapInfo;
	DWORD							m_numberOfFrames;
};