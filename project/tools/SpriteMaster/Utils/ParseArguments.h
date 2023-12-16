#pragma once
#include <string>
#include "..\AnimationTypes\AnimationTypes.h"

#ifdef min 
#undef min 
#endif

#ifdef max 
#undef max
#endif

#include "..\thirdparty\argparse\argparse.hpp"
#include "errors.h"

namespace SpriteMaster
{

class ProgramArguments
{
public:
    std::string m_filepath;
    std::string m_destinationFolder;
    std::string m_bank;
    AnimationType m_animationType = AnimationType::Standard;
    bool m_updateOnly;
};

ProgramArguments ParseArguments(int argc, char* argv[]);

}