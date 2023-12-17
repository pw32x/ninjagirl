#pragma once

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

}