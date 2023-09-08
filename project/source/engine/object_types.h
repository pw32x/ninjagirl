#ifndef OBJECT_TYPES_INCLUDE_H
#define OBJECT_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "engine/animation_types.h"

typedef struct game_object
{
	void (*Update)(struct game_object* gameObject);
	void (*Draw)(struct game_object* gameObject);
	BOOL (*UpdateAnimation)(struct game_object* gameObject);
	union
	{
		const AnimationBatched* animationBatched;
		const PlaneAnimation* planeAnimation;
	};

	union
	{
		const AnimationFrameBatched* currentAnimationBatchedFrame;
		const PlaneAnimationFrame* currentPlaneAnimationFrame;
	};

	s16 x;
	s16 y;

	s16 speedx;
	s16 speedy;

	u8 animationVdpTileIndex;
	u8 currentAnimationFrameIndex;
	u8 animationTime;
	u8 alive;

	s8 rectLeft;
	s8 rectTop;
	s8 rectRight;
	s8 rectBottom;

	u8 objectId;
	u8 pixelWidth;
	u8 pixelHeight;
	u8 objectType;
} GameObject;

typedef void (*ObjectFunctionType)(GameObject* gameObject);

#endif