#include "stdafx.h"

#include "AnimationTypes\Animation.h"
#include "AnimationTypes\AnimationProperties.h"
#include "AnimationTypes\PlaneAnimation.h"
#include "AnimationTypes\TileAnimation.h"
#include "AnimationTypes\Palette.h"
#include "GraphicsGale\GraphicsGaleObject.h"
#include "Base\errors.h"
#include "Utils\FileUtils.h"
#include "Utils\ParseArguments.h"

#include <string>
#include <system_error>



namespace SpriteMaster
{

void getOutputName(std::string& filename, std::string& outputName)
{
    // figure out the output name
    std::size_t index;
    index = filename.rfind("\\"); // remove path
    if (index != std::string::npos)
    {
        outputName = filename.substr(index + 1);
    }
    else
    {
        outputName = filename;
    }

    index = outputName.find(".");
    outputName = outputName.substr(0, index);
}

int Main(int argc, char* argv[])
{
    ProgramArguments programArguments = ParseArguments(argc, argv);

    std::vector<std::string> outFilenames;
    FileUtils::getFilenames(programArguments.m_filepath, outFilenames);

    for (auto& filename : outFilenames)
    {
        GraphicsGaleObject ggo(filename);

        std::string outputName;

        getOutputName(filename, outputName);

        if (programArguments.m_updateOnly && !FileUtils::needsUpdate(filename, programArguments.m_destinationFolder, outputName))
        {
            printf("%s is already up to date.\n", filename.c_str());
            continue;
        }
        else
        {
            printf("Exporting %s \n", filename.c_str());
        }

        if (!FileUtils::folderExists(programArguments.m_destinationFolder.c_str()))
            FileUtils::createFolder(programArguments.m_destinationFolder.c_str());

        AnimationBase* animation;

        switch (programArguments.m_animationType)
        {
        case AnimationType::PlaneAnimation: 
        {
            animation = new GGPlaneAnimation(ggo);
            break;
        }
        case AnimationType::AnimatedTileset:
        {
            animation = new GGTileAnimation(ggo);
            break;
        }
        case AnimationType::Palette:
        {
            animation = new GGPalette(ggo);
            break;
        }
        default:
        {
            animation = new GGAnimation(ggo, programArguments.m_isStreamed, programArguments.m_isMetaSprite);
            break;
        }
        }

        animation->Write(programArguments.m_destinationFolder, outputName, programArguments.m_bank);
        delete animation;
    }

    printf("done\n");

    return 0;
}

}

int main(int argc, char* argv[])
{
    printf("SpriteMaster.exe Graphics Gale to C exporter by pw_32x. https://github.com/pw32x/ninjagirl\n");

    try
    {
        SpriteMaster::Main(argc, argv);
    }
    catch (const std::system_error& e)
    {
        printf(e.what());
        return e.code().value();
    }

    return 0;
}