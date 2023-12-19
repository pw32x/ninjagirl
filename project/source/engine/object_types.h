#ifndef OBJECT_TYPES_INCLUDE_H
#define OBJECT_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "engine/animation_types.h"
#include "engine/math_utils.h"
#include "engine/resource_types.h"

typedef struct game_object
{
	void (*Update)(struct game_object* gameObject);
	BOOL (*Draw)(struct game_object* gameObject);
	BOOL (*UpdateAnimation)(struct game_object* gameObject);
	void (*HandleCollision)(struct game_object* gameObject, struct game_object* other);
	union
	{
		const BatchedAnimation* batchedAnimation;
		const PlaneAnimation* planeAnimation;
		const TileAnimation* tileAnimation;
	};

	union
	{
		const BatchedAnimationFrame* currentBatchedAnimationFrame;
		const PlaneAnimationFrame* currentPlaneAnimationFrame;
		const TileAnimationFrame* currentTileAnimationFrame;
	};

	s16 x;
	s16 y;

	s16 speedx;
	s16 speedy;

	u8 currentAnimationFrameIndex;
	u8 animationTime;
	u8 alive;
	u8 flipped;

	u8 data1;


	u8 data2;
	u8 data3;
	s8 health;
	s8 damage;

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


typedef struct create_info
{
	s16 startX;
	s16 startY;
	const ResourceInfo* resourceInfo;
} CreateInfo;

#endif