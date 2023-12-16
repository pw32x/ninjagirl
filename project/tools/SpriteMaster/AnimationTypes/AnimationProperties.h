#pragma once

#include <string>
#include <map>

namespace SpriteMaster
{

class AnimationProperties
{
public:
	AnimationProperties();

public:
	int mOffsetX;
	int mOffsetY;

	std::multimap<int, std::string> animationFrameNames;
};

}