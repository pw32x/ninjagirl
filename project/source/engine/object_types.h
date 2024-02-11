#ifndef OBJECT_TYPES_INCLUDE_H
#define OBJECT_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "engine/animation_types.h"
#include "engine/math_utils.h"
#include "engine/resource_types.h"

#define OBJECTTYPE_PROJECTILE		0
#define OBJECTTYPE_ENEMY			1
#define OBJECTTYPE_EFFECT			2
#define OBJECTTYPE_PLAYER			3
#define OBJECTTYPE_COMMANDRUNNER	4

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
	s16 screenx;
	s16 screeny;

	s16 speedx;
	s16 speedy;

	u8 currentAnimationFrameIndex;
	u8 animationTime;
	u8 alive;
	u8 flipped;

	s8 health;
	s8 damage;

	s8 rectLeft;
	s8 rectTop;
	s8 rectRight;
	s8 rectBottom;

	u8 objectId;
	u8 pixelWidth; // remove me
	u8 pixelHeight;// remove me
	u8 objectType;

	u16 extraData1;
	u16 extraData2;
	u16 extraData3;
	u16 extraData4;
} GameObject;

typedef void (*ObjectFunctionType)(GameObject* gameObject);

#endif