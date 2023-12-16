#include "stdafx.h"

#include "AnimationTypes\Animation.h"
#include "AnimationTypes\AnimationProperties.h"
#include "AnimationTypes\PlaneAnimation.h"
#include "AnimationTypes\TileAnimation.h"
#include "GraphicsGale\GraphicsGaleObject.h"
#include "Options.h"
#include "Utils\errors.h"
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
        AnimationProperties	animationProperties;
        Options	options;

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

        options.ProcessOptions(filename);

        if (options.mBackgroundPlaneAnimation)
        {
            GGPlaneAnimation animation(ggo, options);
            animation.Write(programArguments.m_destinationFolder, outputName, programArguments.m_bank);
        }
        else if (options.mTileAnimation)
        {
            GGTileAnimation animation(ggo, options, animationProperties);
            animation.Write(programArguments.m_destinationFolder, outputName, programArguments.m_bank);
        }
        else
        {
            GGAnimation animation(ggo, options, animationProperties);
            animation.Write(programArguments.m_destinationFolder, outputName, programArguments.m_bank);
        }
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