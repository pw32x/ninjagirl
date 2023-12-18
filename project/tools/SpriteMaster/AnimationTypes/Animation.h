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

class GGAnimation : public AnimationBase
{
public:
	GGAnimation(const GraphicsGaleObject& ggo, 
				AnimationType animationType);

	void Write(const std::string& outputFolder, const std::string& outputName, const std::string& bank);

	int GetTileCount() { return m_tileStore.GetStoreTileCount(); }

	const BITMAP& GetGeneralBitmapInfo() { return  m_generalBitmapInfo; }

private:

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
	AnimationProperties				m_animationProperties;

	TileStore						m_tileStore;
	SpriteStripStore				m_spriteStripStore;

	std::vector<GGAnimationFrame>	m_frames;
	int								m_totalFrameTime = 0;
	bool							m_isStreamed;
	bool							m_removeDuplicates;
	BITMAP							m_generalBitmapInfo;
	int								m_maxTilesInFrame;
};

}

