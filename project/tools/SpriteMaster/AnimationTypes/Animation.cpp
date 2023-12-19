#include "..\stdafx.h"
#include "Animation.h"

#include "..\Base\TileStore.h"
#include "..\GraphicsGale\GraphicsGaleObject.h"
#include "..\Utils\StringUtils.h"
#include "..\Utils\WriteUtils.h"

#include <algorithm>
#include <fstream>
#include <sstream>

namespace SpriteMaster
{

GGAnimation::GGAnimation(const GraphicsGaleObject& ggo, 
                         AnimationType animationType)
: m_ggo(ggo),
  m_isStreamed(false),
  m_removeDuplicates(false)
{
    if (animationType != AnimationType::Streamed &&
        animationType != AnimationType::Standard)
    {
        THROW_ERROR(Error::UnsupportedAnimationType, "Animation only supports standard and streamed type animations.");
    }

    m_isStreamed = animationType == AnimationType::Streamed;
    m_removeDuplicates = m_isStreamed;

    HBITMAP bitmap = m_ggo.getBitmap(0, 0);

    if (bitmap == NULL)
    {
		printf("Error retrieving bitmap data");
		exit(-1);
    }

    if (GetObject(bitmap, sizeof(BITMAP), &m_generalBitmapInfo) == 0)
    {
        printf("BitmapInfo is NULL\n");
		exit(-1);
    }

    unsigned int numberOfFrames = m_ggo.getFrameCount();
	m_frames.resize(numberOfFrames);

    m_maxTilesInFrame = 0;

    for (DWORD loop = 0; loop < numberOfFrames; loop++)
    {
		GGAnimationFrame& frame = m_frames[loop];

		frame.Init(loop, 
                   m_ggo, 
                   m_spriteStripStore,
                   m_animationProperties);

        m_maxTilesInFrame = max(m_maxTilesInFrame, frame.GetMaxTilesInAFrame());

		m_totalFrameTime += frame.GetFrameDelayTime();

        if (loop > 0)
        {
            int previousIndex = loop - 1;

            GGAnimationFrame& previousFrame = m_frames[previousIndex];

            if (previousFrame.getNextFrameIndex() == AnimationFrameBase::NEXT_FRAME_NOT_SET)
            {
                if (frame.startsAnimation())
                {
                    int animationStartIndex;

                    auto it = m_animationProperties.animationFrameNames.lower_bound(loop);

                    if (it != m_animationProperties.animationFrameNames.begin()) 
                    {
                        --it; // Move the iterator one step back to get the closest key
                        animationStartIndex = it->first;
                    } 
                    else 
                    {
                        animationStartIndex = 0;
                    }

                    previousFrame.setNextFrameIndex(animationStartIndex);
                }
                else
                {
                    previousFrame.setNextFrameIndex(loop);
                }
            }
        }
    }

    int lastFrameIndex = m_frames.size() - 1;

    if (m_frames[lastFrameIndex].getNextFrameIndex() == AnimationFrameBase::NEXT_FRAME_NOT_SET)
    {
        if (!m_frames[lastFrameIndex].startsAnimation())
        {
            auto it = m_animationProperties.animationFrameNames.lower_bound(lastFrameIndex);

            if (it != m_animationProperties.animationFrameNames.begin()) 
            {
                --it; // Move the iterator one step back to get the closest key
                m_frames[lastFrameIndex].setNextFrameIndex(it->first);
            } 
            else 
            {
                m_frames[lastFrameIndex].setNextFrameIndex(0);
            }
        }
        else
        {
            m_frames[lastFrameIndex].setNextFrameIndex(lastFrameIndex);
        }
    }
}

void GGAnimation::Write(const std::string& outputFolder, const std::string& outputName, const std::string& bank)
{
	WriteGGAnimationHeaderFile(outputFolder, outputName, bank);
	WriteGGAnimationSourceFile(outputFolder, outputName, bank);
}


void GGAnimation::WriteGGAnimationHeaderFile(const std::string& outputFolder, 
                                             const std::string& outputName,
                                             const std::string& bank)
{
	std::string headerFilename = outputName + ".h";
	std::ofstream headerfile(outputFolder + headerFilename, std::ios::trunc);

    // header guard
    std::string headerGuard = outputName + "_ANIMATION_INCLUDE_H";
    std::transform(headerGuard.begin(), headerGuard.end(), headerGuard.begin(), ::toupper);
    headerfile << "// File generated by SpriteMaster. https://github.com/pw32x/ninjagirl\n";
    headerfile << "#ifndef " << headerGuard << "\n";
    headerfile << "#define " << headerGuard << "\n";
    headerfile << "\n";

	// includes
    headerfile << "#include \"animation_types.h\"\n";
    headerfile << "#include \"resource_types.h\"\n";
    headerfile << "\n";

	// exported types

    std::string streamed = m_isStreamed ? "Streamed" : "";
    headerfile << "RESOURCE(" << bank << ") extern const " << streamed << "BatchedAnimation " << outputName << ";\n"; 

    headerfile << "\n";

    if (m_animationProperties.animationFrameNames.size() > 0)
    {
        headerfile << "// frame numbers for specific animations.\n";
        for (const auto& pair : m_animationProperties.animationFrameNames) 
	    {
		    std::transform(headerGuard.begin(), headerGuard.end(), headerGuard.begin(), ::toupper);
		    headerfile << "#define " << StringUtils::str_toupper(outputName) << "_" << StringUtils::str_toupper(pair.second) << "_FRAME_INDEX" << " " << pair.first << "\n";
        }
        headerfile << "\n";
    }

    // end header guard
    headerfile << "#endif\n\n";
    headerfile.close();
}

void GGAnimation::WriteSpritesBatched(const std::string& outputName, std::ofstream& sourceFile)
{
	for (size_t frameLoop = 0; frameLoop < m_frames.size(); frameLoop++)
	{
		const GGAnimationFrame& frame = m_frames[frameLoop];

        std::string spriteName = WriteUtils::BuildFrameName(outputName, frameLoop) + "BatchedSprite";

        sourceFile << "const BatchedAnimationSprite " << spriteName << "[] = \n";
        sourceFile << "{\n";

        int tileStoreModifier = 0;

        if (m_isStreamed)
        {
            tileStoreModifier = frame.getSprites().begin()->m_spriteStrip.tileStartIndex;
        }

        for (const auto& sprite : frame.getSprites())
        {
            sourceFile << "    { ";
            sourceFile << sprite.m_spriteStrip.count << ", ";
            sourceFile << "{ ";
            sourceFile << sprite.m_xPositionOffset - m_animationProperties.mOffsetX << ", ";
            sourceFile << sprite.m_yPositionOffset - m_animationProperties.mOffsetY << ", ";
            //sourceFile << sprite.m_spriteStrip.tileStartIndex - tileStoreModifier;
            sourceFile << sprite.m_spriteStrip.tileStartIndex;
            sourceFile << " }";
            sourceFile << " },\n";
        }
        sourceFile << "    {0},\n";
        sourceFile << "};\n\n";
    }
}

void GGAnimation::WriteFramesBatched(const std::string& outputName, std::ofstream& sourceFile)
{
	for (size_t frameLoop = 0; frameLoop < m_frames.size(); frameLoop++)
	{
		const GGAnimationFrame& frame = m_frames[frameLoop];
        std::string frameName = WriteUtils::BuildFrameName(outputName, frameLoop);

        if (m_isStreamed)
            sourceFile << "extern const StreamedBatchedAnimationFrame " << frameName << ";\n";
        else
            sourceFile << "extern const BatchedAnimationFrame " << frameName << ";\n";
	}

    sourceFile << "\n";

	for (size_t frameLoop = 0; frameLoop < m_frames.size(); frameLoop++)
	{
		const GGAnimationFrame& frame = m_frames[frameLoop];

        std::string frameName = WriteUtils::BuildFrameName(outputName, frameLoop);
        std::string nextFrameName;
        

        if (frame.getNextFrameIndex() == AnimationFrameBase::NO_LOOP)
            nextFrameName = "NULL";
        else
            nextFrameName = "&" + WriteUtils::BuildFrameName(outputName, frame.getNextFrameIndex());

		sourceFile << "\n";

        if (m_isStreamed)
            sourceFile << "const StreamedBatchedAnimationFrame " << frameName << " = \n";
        else
		    sourceFile << "const BatchedAnimationFrame " << frameName << " = \n";

		sourceFile << "{\n";
        sourceFile << "    " << frameName << "BatchedSprite,\n";

        if (m_isStreamed)
        {
            int tileIndex = frame.getSprites().begin()->m_spriteStrip.tileStartIndex;
            sourceFile << "    " << tileIndex << ", // tile index\n"; 
        }

		sourceFile << "    " << frame.GetFrameDelayTime() << ", // frame time\n"; 
        sourceFile << "    " << nextFrameName << ", // next frame\n";
		sourceFile << "};\n";
	}
}


void GGAnimation::WriteFrames(const std::string& outputName, std::ofstream& sourceFile)
{
	for (size_t frameLoop = 0; frameLoop < m_frames.size(); frameLoop++)
	{
		const GGAnimationFrame& frame = m_frames[frameLoop];
        std::string frameName = WriteUtils::BuildFrameName(outputName, frameLoop);

        if (m_isStreamed)
            sourceFile << "extern const StreamedAnimationFrame " << frameName << ";\n";
        else
            sourceFile << "extern const AnimationFrame " << frameName << ";\n";
	}

	for (size_t frameLoop = 0; frameLoop < m_frames.size(); frameLoop++)
	{
		const GGAnimationFrame& frame = m_frames[frameLoop];

        std::string frameName = WriteUtils::BuildFrameName(outputName, frameLoop);
        std::string nextFrameName;
        

        if (frame.getNextFrameIndex() == AnimationFrameBase::NO_LOOP)
            nextFrameName = "NULL";
        else
            nextFrameName = "&" + WriteUtils::BuildFrameName(outputName, frame.getNextFrameIndex());

		sourceFile << "\n";


        if (m_isStreamed)
            sourceFile << "const StreamedAnimationFrame " << frameName << " = \n";
        else
		    sourceFile << "const AnimationFrame " << frameName << " = \n";


		sourceFile << "{\n";
        sourceFile << "    " << frameName << "Sprites,\n";
		sourceFile << "    " << frame.getSprites().size() << ", // number of sprites\n";

        if (m_isStreamed)
        {
            int tileIndex = frame.getSprites().begin()->m_spriteStrip.tileStartIndex;
            sourceFile << "    " << tileIndex << ", // tile index\n"; 
        }

		sourceFile << "    " << frame.GetFrameDelayTime() << ", // frame time\n"; 
        sourceFile << "    " << nextFrameName << ", // next frame\n";
		sourceFile << "};\n";
	}
}

void GGAnimation::WriteFrameArrayBatched(const std::string& outputName, std::ofstream& sourceFile)
{
    if (m_isStreamed)
        sourceFile << "const StreamedBatchedAnimationFrame* const " << outputName << "Frames[" << m_frames.size() << "] = \n";
    else
        sourceFile << "const BatchedAnimationFrame* const " << outputName << "Frames[" << m_frames.size() << "] = \n";
    sourceFile << "{\n";

    for (size_t loop = 0; loop < m_frames.size(); loop++)
    {
        sourceFile << "    &" << WriteUtils::BuildFrameName(outputName, loop) << ",\n";
    }

    sourceFile << "};\n\n";
}


void GGAnimation::WriteFrameArray(const std::string& outputName, std::ofstream& sourceFile)
{
    if (m_isStreamed)
        sourceFile << "const StreamedAnimationFrame* const " << outputName << "Frames[" << m_frames.size() << "] = \n";
    else
        sourceFile << "const AnimationFrame* const " << outputName << "Frames[" << m_frames.size() << "] = \n";
    sourceFile << "{\n";

    for (size_t loop = 0; loop < m_frames.size(); loop++)
    {
        sourceFile << "    &" << WriteUtils::BuildFrameName(outputName, loop) << ",\n";
    }

    sourceFile << "};\n\n";
}


void GGAnimation:: WriteAnimationStructBatched(const std::string& outputName, 
                                               std::ofstream& sourceFile,
                                               const std::string& bank)
{
    sourceFile << "u8 " << outputName << "VdpLocation;\n\n";

    if (m_isStreamed)
    {
        // final struct
        sourceFile << "const StreamedBatchedAnimation " << outputName << " = \n";
        sourceFile << "{\n";
        sourceFile << "    STREAMED_BATCHED_ANIMATION_RESOURCE_TYPE, \n";
        sourceFile << "    (const StreamedBatchedAnimationFrame** const)" << outputName << "Frames,\n";
    }
    else
    {
        // final struct
        sourceFile << "const BatchedAnimation " << outputName << " = \n";
        sourceFile << "{\n";
        sourceFile << "    BATCHED_ANIMATION_RESOURCE_TYPE, \n";
        sourceFile << "    (const BatchedAnimationFrame** const)" << outputName << "Frames,\n";
    }


    sourceFile << "    (unsigned char* const)" << outputName << "TileData, // start of the sprite data\n";
    sourceFile << "    " << m_frames.size() << ", // number of frames\n";
    sourceFile << "    " << m_generalBitmapInfo.bmWidth << ", // width in pixels\n";
    sourceFile << "    " << m_generalBitmapInfo.bmHeight << ", // height in pixels\n";
    sourceFile << "    " << m_spriteStripStore.GetTileCount() << ", // the total amount of tiles in animation\n";

    if (m_isStreamed)
        sourceFile << "    " << m_maxTilesInFrame << ", // the max amount of sprite tiles in a frame\n";    

    sourceFile << "    &" << outputName << "VdpLocation,\n";
    sourceFile << "};\n";
}


void GGAnimation:: WriteAnimationStruct(const std::string& outputName, 
                                        std::ofstream& sourceFile,
                                        const std::string& bank)
{
    sourceFile << "u8 " << outputName << "VdpLocation;\n\n";

    if (m_isStreamed)
    {
        // final struct
        sourceFile << "RESOURCE(" << bank << ") const StreamedAnimation " << outputName << " = \n";
        sourceFile << "{\n";
        sourceFile << "    STREAMED_REGULAR_ANIMATION_RESOURCE_TYPE, \n";
        sourceFile << "    (const StreamedAnimationFrame** const)" << outputName << "Frames,\n";
    }
    else
    {
        // final struct
        sourceFile << "RESOURCE(" << bank << ") const Animation " << outputName << " = \n";
        sourceFile << "{\n";
        sourceFile << "    REGULAR_ANIMATION_RESOURCE_TYPE, \n";
        sourceFile << "    (const AnimationFrame** const)" << outputName << "Frames,\n";
    }
    sourceFile << "    (unsigned char* const)" << outputName << "TileData, // start of the sprite data\n";
    sourceFile << "    " << m_frames.size() << ", // number of frames\n";
    sourceFile << "    " << m_generalBitmapInfo.bmWidth << ", // width in pixels\n";
    sourceFile << "    " << m_generalBitmapInfo.bmHeight << ", // height in pixels\n";
    sourceFile << "    " << m_spriteStripStore.GetTileCount() << ", // the total amount of tiles in animation\n";

    if (m_isStreamed)
        sourceFile << "    " << m_maxTilesInFrame << ", // the max amount of sprite tiles in a frame\n";    

    sourceFile << "    &" << outputName << "VdpLocation,\n";
    sourceFile << "};\n";
}


void GGAnimation::WriteGGAnimationSourceFile(const std::string& outputFolder, 
                                             const std::string& outputName,
                                             const std::string& bank)
{
	std::ofstream sourceFile(outputFolder + outputName + ".c");

    // includes
    sourceFile << "#include \"" << outputName << ".h\"\n";
	
    sourceFile << "\n";
    sourceFile << "\n";

	// tile data
    m_spriteStripStore.WriteTileStore(outputName, sourceFile);

    WriteSpritesBatched(outputName, sourceFile);
    WriteFramesBatched(outputName, sourceFile);
	WriteFrameArrayBatched(outputName, sourceFile);
    WriteAnimationStructBatched(outputName, sourceFile, bank);


    sourceFile.close();
}

/*
#include "player.h"


unsigned short const playerTileData[32] = 
{
// tile: 0
    0x0000, 0x22,
    0x0000, 0x2ee,
    0x0000, 0x2eee,
    0x0000, 0x29e9,
    0x0002, 0x9ee6,
    0x0002, 0xee66,
    0x002e, 0xfe6e,
    0x002e, 0xfe9c,

	[...]

};

const Sprite playerFrame0Sprites[] =
{
	x, y, n,
	x, y, n,
	[...]
};

const Sprite playerFrame0XFlippedSprites[] =
{
	x, y, n,
	x, y, n,
	[...]
};

(align to 4)
const AnimationFrame playerFrame0 =
{
	playerFrame0Sprites
	0, // frame time
	X, // num sprites
}

(align to 4)
const AnimationFrame playerFrame0XFlipped =
{
	playerFrame0XFlippedSprites
	0, // frame time
	X, // num sprites

}

const AnimationFrames* playerFrames[] = // need pointers???
{
	playerFrame0,
	playerFrame0XFlipped
};

(align to 4)
const Animation player_animation =
{
    playerFrames,										(unsigned int)
    (u32*)playerTileData, // start of the sprite data	(unsigned int)
    2, // number of frames								(unsigned char)
    24, // width in pixels								(unsigned char)
    32, // height in pixels								(unsigned char)
    12, // max tiles per frame							(unsigned char)
    20, // the total number of tiles in the animation	(unsigned char)
    118, // the total time of the animation				(unsigned short)
};



*/

}