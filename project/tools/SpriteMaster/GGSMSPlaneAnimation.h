#pragma once

#include <string>
#include "galefile151119\galefile.h"
#include "GGSMSPlaneAnimationFrame.h"
#include "Options.h"
#include <vector>
#include <memory>

namespace sms
{


class GGPlaneAnimation
{
public:
	GGPlaneAnimation(LPVOID galeFileHandle, const Options& options);
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
	LPVOID								m_galeFileHandle;
	int									m_uniqueTileCount = 0;
	int									m_maxUniqueTilesPerFrame = 0;
	const Options&						m_options;
	BITMAP								m_generalBitmapInfo;
	DWORD								m_numberOfFrames;
	std::vector<GGPlaneAnimationFrame>  m_frames;
	std::vector<GGPlaneAnimationFrame*> m_uniqueFrameData;
	std::vector<Tile>					m_tileStore;
};

}