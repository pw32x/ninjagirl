#include "..\stdafx.h"
#include "AnimationTypes.h"

#include "../GraphicsGale/GraphicsGaleObject.h"
#include "../Utils/SpriteUtils.h"
#include "AnimationProperties.h"
#include <queue>
#include <sstream>

namespace SpriteMaster
{

AnimationFrameBase::AnimationFrameBase()
	: mFrameDelayTime(-1)
	, mFrameNumber(-1)
	, m_startsAnimation(false)
	, mNextFrame(NEXT_FRAME_NOT_SET)
{

}

void AnimationFrameBase::GetGGInfo(const GraphicsGaleObject& ggo, 
								   AnimationProperties& animationProperties)
{
	LONG ggFrameDelayTime = ggo.getFrameInfo(mFrameNumber, 2); // the 2 means frame time?
	mFrameDelayTime = (LONG)(myround((float)ggFrameDelayTime / 17.0f)); // 17 ms per frame

	const int length =  1024;
	char frameName[length];
	ggo.getFrameName(mFrameNumber, frameName, length);


	std::istringstream iss(frameName);
	std::queue<std::string> tokens;
	std::string token;

	while (iss >> token) 
	{
		tokens.push(token);
	}

	while (!tokens.empty())
	{
		std::string token = tokens.front();
		tokens.pop();

		if (strstr(token.c_str(), "%") || 
			strstr(token.c_str(), "Copy_") ||
			strstr(token.c_str(), "Frame"))
			continue;

		if (strstr(token.c_str(), "OFFSET"))
		{
			token = tokens.front();
			animationProperties.mOffsetX = stoi(token);
			tokens.pop();

			token = tokens.front();
			animationProperties.mOffsetY = stoi(token);
			tokens.pop();
		}
		else if (token == "NOLOOP")
		{
			mNextFrame = NO_LOOP;
		}
		else if (token == "LOOP")
		{
			int lastFrameWithAnimationFrameName = 0;

			if (!animationProperties.animationFrameNames.empty())
				lastFrameWithAnimationFrameName = animationProperties.animationFrameNames.rbegin()->first;

			mNextFrame = lastFrameWithAnimationFrameName;
		}
		else if (token == "JUMPTO")
		{
			token = tokens.front();
			mNextFrame = stoi(token);
			tokens.pop();
		}
		else if (token == "SLICE_START_LEFT")
		{
			token = tokens.front();
			m_sliceStartLeft = stoi(token);
			tokens.pop();
		}
		else if (token == "SLICE_START_TOP")
		{
			token = tokens.front();
			m_sliceStartTop = stoi(token);
			tokens.pop();
		}
		else
		{
			animationProperties.animationFrameNames.insert({mFrameNumber, token});
			m_startsAnimation = true;
		}
	}
}
}