#ifndef OBJECT_TYPES_INCLUDE_H
#define OBJECT_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "engine/animation_types.h"
#include "engine/math_utils.h"
#include "engine/resource_types.h"

#define OBJECTTYPE_PROJECTILE			0
#define OBJECTTYPE_ENEMY				1
#define OBJECTTYPE_EFFECT				2
#define OBJECTTYPE_PLAYER				3
#define OBJECTTYPE_COMMANDRUNNER		4
#define OBJECTTYPE_ITEM					5
#define OBJECTTYPE_ENEMY_PROJECTILE		6

#define GAME_OBJECT_FIELDS \
	void (*Update)(struct game_object* gameObject);\
	void (*HandleCollision)(struct game_object* gameObject, struct game_object* other);\
	void (*Draw)(struct game_object* gameObject);\
	BOOL (*UpdateAnimation)(struct game_object* gameObject);\
	union\
	{\
		const BatchedAnimationFrame* currentBatchedAnimationFrame;\
		const MetaSpriteAnimationFrame* currentMetaSpriteAnimationFrame;\
		const PlaneAnimationFrame* currentPlaneAnimationFrame;\
		const TileAnimationFrame* currentTileAnimationFrame;\
	};\
	u8 currentAnimationFrameIndex;\
	u8 animationTime;\
	union\
	{\
		const BatchedAnimation* batchedAnimation;\
		const MetaSpriteAnimation* metaSpriteAnimation;\
		const PlaneAnimation* planeAnimation;\
		const TileAnimation* tileAnimation;\
	};\
	\
	s16 x;\
	s16 y;\
	s16 screenx;\
	s16 screeny;\
	s16 screenRectLeft;\
	s16 screenRectTop;\
	s16 screenRectRight;\
	s16 screenRectBottom;\
	\
	s16 speedx;\
	s16 speedy;\
	\
	u8 alive;\
	u8 flipped;\
	\
	s8 health;\
	s8 damage;\
	s8 rectLeft;\
	s8 rectTop;\
	s8 rectRight;\
	s8 rectBottom;\
	u8 objectType; \
	const ResourceInfo* resourceInfo;\
	const ResourceInfo** extraResources;\
	\
	u8 objectId;\
	u8 pixelWidth; \
	u8 pixelHeight





typedef struct game_object
{
	GAME_OBJECT_FIELDS;	

	// pre-allocate space for extra data other types
	// of objects might want to use.
	u16 extraData1;
	u16 extraData2;
	u16 extraData3;
	u16 extraData4;
} GameObject;

typedef void (*ObjectFunctionType)(GameObject* gameObject);

#endif