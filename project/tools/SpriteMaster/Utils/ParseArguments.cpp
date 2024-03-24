#include "..\stdafx.h"
#include "ParseArguments.h"
#include "FileUtils.h"

namespace SpriteMaster
{

ProgramArguments ParseArguments(int argc, char* argv[])
{
    argparse::ArgumentParser program("SpriteMaster");
    program.add_argument("path").required();
    program.add_argument("destfolder").help("Destination folder").default_value("");
    program.add_argument("-u", "-updateonly").help("Only update if source is newer").flag();
    //program.add_argument("-b", "-bank").help("The rom bank number to export to.").default_value(0);

    auto &group = program.add_mutually_exclusive_group();
    group.add_argument("-s", "-streamed").flag();
    group.add_argument("-m", "-metasprite").flag();
    group.add_argument("-t", "-animatedtileset").flag();
    group.add_argument("-p", "-planeanimation").flag();
    group.add_argument("-pal", "-palette").flag();

    std::vector<std::string> unknownArgs;

    try
    {
        unknownArgs = program.parse_known_args(argc, argv);
    }
    catch (const std::exception&)
    {
        std::stringstream ss;
        ss << program;
        THROW_ERROR(Error::ParsingArgumentsFailed, ss.str().c_str());
    }

    ProgramArguments programArguments;

    programArguments.m_filepath = program.get<std::string>("path");
    programArguments.m_destinationFolder = FileUtils::ensureBackslash(program.get<std::string>("destfolder"));
    programArguments.m_updateOnly = program.get<bool>("u");

    if (program["-s"] == true)
        programArguments.m_isStreamed = true;
    if (program["-m"] == true)
        programArguments.m_isMetaSprite = true;
    else if (program["-t"] == true)
        programArguments.m_animationType = AnimationType::AnimatedTileset;
    else if (program["-p"] == true)
        programArguments.m_animationType = AnimationType::PlaneAnimation;
    else if (program["-pal"] == true)
        programArguments.m_animationType = AnimationType::Palette;

    // get the bank number. it has a different format than what argparse handles.
    // -bank<NUMBER> and not -bank <NUMBER>
    std::string bankFlag = "-bank";
    for (auto& unknownArg : unknownArgs)
    {
        if (unknownArg.starts_with(bankFlag))
        {
            int found = unknownArg.find(bankFlag);
            if (found != std::string::npos)
            {
                programArguments.m_bank = "BANK" + unknownArg.substr(found + bankFlag.length());
            }
        }
        else
        {
            THROW_ERROR(Error::UnknownCommandLineFlag, "Encountered unknown flag " + unknownArg);
        }
    }

    return programArguments;
}

}