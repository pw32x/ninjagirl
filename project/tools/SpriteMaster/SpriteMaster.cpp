// gale2c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "AnimationTypes\Animation.h"
#include "AnimationTypes\AnimationProperties.h"
#include "AnimationTypes\PlaneAnimation.h"
#include "AnimationTypes\TileAnimation.h"

#include "Options.h"

#include "Utils\errors.h"
#include "Utils\FileUtils.h"
#include "Utils\GraphicsGaleObject.h"
#include <system_error>

namespace SpriteMaster
{

std::string						gOutputFolder;
std::string                     gBank;

std::vector<std::string>        gFilenames;

bool gUpdateOnly = false;


void parseOptionalParameter(const std::string& parameter)
{
    if (parameter == "-updateonly")
    {
        gUpdateOnly = true;
    }
    else
    {
        std::string bankFlag = "-bank";
        int found = parameter.find(bankFlag);
        if (found != std::string::npos)
        {
            gBank = "BANK" + parameter.substr(found + bankFlag.length());
        }
        else
        {
            gOutputFolder = parameter;
            gOutputFolder += "\\";
        }
    }
}

void ValidateArguments(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("No Graphics Gale file or folder specified\n");
        printf("\ngale2c.exe [.gal file or folder] [optional_destination_folder] [-updateonly]\n");
        exit(-1);
    }

    std::string fileOrPath = argv[1];

    // if ends with gal, then it's indivdual file.
    int findIndex = fileOrPath.rfind(".gal");
    if (findIndex != -1)
    {
        gFilenames.push_back(fileOrPath);
    }
    else // else assume it's a folder
    {
        std::string extension = ".gal";

        WIN32_FIND_DATAA findFileData;

        HANDLE hFind;

        std::string searchPattern = fileOrPath + "\\*.gal";
        hFind = FindFirstFileA(searchPattern.c_str(), &findFileData);

        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                std::string fileName = findFileData.cFileName;
                gFilenames.push_back(fileOrPath + "\\" + fileName);

            } while (FindNextFileA(hFind, &findFileData) != 0);

            FindClose(hFind);
        }
        else
        {
            printf("No animations found in %s.\n", fileOrPath.c_str());
            exit(-1);
        }
    }

    for (int loop = 2; loop < argc; loop++)
    {
        parseOptionalParameter(argv[loop]);
    }
}



int Main(int argc, char* argv[])
{
    ValidateArguments(argc, argv);

    for (auto& filename : gFilenames)
    {
        AnimationProperties	animationProperties;
        Options	options;

        GraphicsGaleObject ggo(filename);

        std::string outputFilename;

        // figure out the output name
        std::size_t index;
        index = filename.rfind("\\"); // remove path
        if (index != std::string::npos)
        {
            outputFilename = filename.substr(index + 1);
        }
        else
        {
            outputFilename = filename;
        }

        index = outputFilename.find(".");
        outputFilename = outputFilename.substr(0, index);

        if (gUpdateOnly && !FileUtils::needsUpdate(filename, gOutputFolder, outputFilename))
        {
            printf("%s is already up to date.\n", filename.c_str());
            continue;
        }
        else
        {
            printf("Exporting %s \n", filename.c_str());
        }

        if (!FileUtils::folderExists(gOutputFolder.c_str()))
            FileUtils::createFolder(gOutputFolder.c_str());

        options.ProcessOptions(filename);

        if (options.mBackgroundPlaneAnimation)
        {
            GGPlaneAnimation animation(ggo, options);
            animation.Write(gOutputFolder, outputFilename, gBank);
        }
        else if (options.mTileAnimation)
        {
            GGTileAnimation animation(ggo, options, animationProperties);
            animation.Write(gOutputFolder, outputFilename, gBank);
        }
        else
        {
            GGAnimation animation(ggo, options, animationProperties);
            animation.Write(gOutputFolder, outputFilename, gBank);
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