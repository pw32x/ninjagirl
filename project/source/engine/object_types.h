#ifndef OBJECT_TYPES_INCLUDE_H
#define OBJECT_TYPES_INCLUDE_H

#include "engine/types.h"
#include "engine/animation_types.h"

typedef struct game_object
{
	s16 x;
	s16 y;
	const Animation* animation;
	u8 animationVdpTileIndex;
	const AnimationFrame* currentAnimationFrame;
	u8 currentAnimationFrameIndex;
	u8 animationTime;
	void (*Update)(struct game_object* gameObject);
	void (*Draw)(struct game_object* gameObject);
} GameObject;

typedef void (*ObjectFunctionType)(GameObject* gameObject);

#endif