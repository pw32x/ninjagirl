#include "..\stdafx.h"
#include "ParseArguments.h"
#include "FileUtils.h"

namespace SpriteMaster
{

ProgramArguments ParseArguments(int argc, char* argv[])
{
    argparse::ArgumentParser program("SpriteMaster");
    program.add_argument("path").required();
    program.add_argument("-d", "-destfolder").help("Destination folder").default_value("");
    program.add_argument("-u", "-updateonly").help("Only update if source is newer").flag();
    program.add_argument("-b", "-bank").help("The rom bank number to export to.").default_value(0);

    auto &group = program.add_mutually_exclusive_group();
    group.add_argument("-s", "-streamed").flag();
    group.add_argument("-a", "-animatedtileset").flag();
    group.add_argument("-p", "-planeanimation").flag();
    //group.add_argument("-pal", "-palette");


    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::exception&)
    {
        std::stringstream ss;
        ss << program;
        THROW_ERROR(Error::ParsingArgumentsFailed, ss.str().c_str());
    }

    ProgramArguments programArguments;

    programArguments.m_filepath = program.get<std::string>("path");
    programArguments.m_destinationFolder = FileUtils::ensureBackslash(program.get<std::string>("-destfolder"));

    programArguments.m_bank = program.get<std::string>("-bank");


    if (program["-s"] == true)
        programArguments.m_animationType = AnimationType::Streamed;
    if (program["-a"] == true)
        programArguments.m_animationType = AnimationType::AnimatedTileset;
    if (program["-p"] == true)
        programArguments.m_animationType = AnimationType::PlaneAnimation;

    return programArguments;
}

}