#ifndef OBJECT_TYPES_INCLUDE_H
#define OBJECT_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "engine/animation_types.h"

typedef struct game_object
{
	void (*Update)(struct game_object* gameObject);
	void (*Draw)(struct game_object* gameObject);
	const Animation* animation;
	const AnimationFrame* currentAnimationFrame;
	s16 x;
	s16 y;
	s16 speedx;
	s16 speedy;
	u8 animationVdpTileIndex;
	u8 currentAnimationFrameIndex;
	u8 animationTime;
	u8 alive;
	u8 objectId;
	u8 data1;
	u8 data2;
	u8 data3;
} GameObject;

typedef void (*ObjectFunctionType)(GameObject* gameObject);

#endif