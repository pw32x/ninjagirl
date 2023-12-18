#pragma once

#include "..\Base\TileStore.h"
#include "AnimationTypes.h"
#include "PlaneAnimationFrame.h"
#include <memory>
#include <string>
#include <vector>

namespace SpriteMaster
{

class GraphicsGaleObject;

class GGPlaneAnimation : public AnimationBase
{
public:
	GGPlaneAnimation(const GraphicsGaleObject& ggo);
	void Write(const std::string& outputFolder, const std::string& outputName, const std::string& bank);

	int GetTileCount() { return m_uniqueTileCount; }
	const BITMAP& GetGeneralBitmapInfo() { return  m_generalBitmapInfo; }

private:
	GGPlaneAnimationFrame* findSameFrame(const GGPlaneAnimationFrame& frame);
	int findSameFrameIndex(const GGPlaneAnimationFrame& frame);

	void WriteGGPlaneAnimationHeaderFile(const std::string& outputFolder, const std::string& outputName, const std::string& bank);
	void WriteGGPlaneAnimationSourceFile(const std::string& outputFolder, const std::string& outputName, const std::string& bank);
	void WriteFrameData(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrameNames(const std::string& outputName, std::ofstream& sourceFile);
	void WritePalettes(const std::string& outputName, std::ofstream& sourceFile);
	void WriteTileMaps(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrames(const std::string& outputName, std::ofstream& sourceFile);
	void WriteFrameArray(const std::string& outputName, std::ofstream& sourceFile);
	void WriteAnimationStruct(const std::string& outputName, std::ofstream& sourceFile, const std::string& bank);



private:
	const GraphicsGaleObject&			m_ggo;
	int									m_uniqueTileCount = 0;
	int									m_maxUniqueTilesPerFrame = 0;
	BITMAP								m_generalBitmapInfo;
	DWORD								m_numberOfFrames;
	std::vector<GGPlaneAnimationFrame>  m_frames;
	std::vector<GGPlaneAnimationFrame*> m_uniqueFrameData;
	TileStore							m_tileStore;
};

}