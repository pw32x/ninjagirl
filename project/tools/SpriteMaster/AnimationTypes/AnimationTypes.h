#pragma once

#include <string>
#include <string>

namespace SpriteMaster
{

class AnimationProperties;
class GraphicsGaleObject;

enum class AnimationType
{
    Standard,
    AnimatedTileset,
    PlaneAnimation,
    Palette
};

class AnimationBase
{
public:
    virtual void Write(const std::string& outputFolder, 
                       const std::string& outputName, 
                       const std::string& bank) = 0;


};

class AnimationFrameBase
{
public:
    static const int NEXT_FRAME_NOT_SET = -1;
    static const int NO_LOOP = -2;

public:
    AnimationFrameBase();
    virtual ~AnimationFrameBase() {};

    int getFrameNumber() const { return mFrameNumber; }
    LONG GetFrameDelayTime() const { return mFrameDelayTime; }

    void setNextFrameIndex(int nextFrame) { mNextFrame = nextFrame; }
    int getNextFrameIndex() const { return mNextFrame; }

    bool startsAnimation() const { return m_startsAnimation; }

protected:
    void GetGGInfo(const GraphicsGaleObject& ggo, 
                   AnimationProperties& animationProperties);

protected:
    LONG			mFrameDelayTime;
    int				mFrameNumber;

    int				mNextFrame;

    bool m_startsAnimation = false;

    int m_sliceStartLeft = -1;
    int m_sliceStartTop = -1;
};



}