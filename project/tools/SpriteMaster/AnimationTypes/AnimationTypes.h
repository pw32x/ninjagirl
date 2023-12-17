#pragma once

#include <string>

namespace SpriteMaster
{

enum class AnimationType
{
    Standard,
    Streamed,
    AnimatedTileset,
    PlaneAnimation
};

class IAnimation
{
public:
    virtual void Write(const std::string& outputFolder, 
                       const std::string& outputName, 
                       const std::string& bank) = 0;
};

const int NEXT_FRAME_NOT_SET = -1;
const int NO_LOOP = -2;

}