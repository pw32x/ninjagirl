#pragma once

#include <string>
#include <map>

/*
enum LoopAction
{
	LoopAction_NoLoop,
	LoopAction_Loop,
	LoopAction_Jump
};

class AnimationSpan
{
	std::string name;
	int start;
	int end;
	LoopAction loopAction;
};
*/

class AnimationProperties
{
public:
	AnimationProperties();

public:
	int mOffsetX;
	int mOffsetY;

	std::multimap<int, std::string> animationFrameNames;
};