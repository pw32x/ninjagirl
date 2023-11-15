#ifndef ANIMATION_UTILS_INCLUDE_H
#define ANIMATION_UTILS_INCLUDE_H

#include "SMSLib.h"
#include "engine/animation_types.h"
#include "engine/resource_types.h"

struct game_object;

#define ANIMATION_NO_CHANGE			0
#define ANIMATION_CHANGED_FRAME		1
#define ANIMATION_FINISHED			2


// update
u8 AnimationUtils_updateAnimation(struct game_object* gameObject);
u8 AnimationUtils_updateBatchedAnimation(struct game_object* gameObject);
u8 AnimationUtils_updateBatchedAnimation_noLoop(struct game_object* gameObject);

u8 AnimationUtils_updateStreamedAnimation(struct game_object* gameObject);
u8 AnimationUtils_updateStreamedBatchedAnimation(struct game_object* gameObject);

u8 AnimationUtils_updatePlaneAnimation(struct game_object* gameObject);
u8 AnimationUtils_updateTileAnimation(struct game_object* gameObject);

// load 
u16 Load_AnimationResource(const ResourceInfo* resourceInfo);
u16 Load_BatchedAnimationResource(const ResourceInfo* resourceInfo);

u16 Load_StreamedAnimationResource(const ResourceInfo* resourceInfo);
u16 Load_StreamedBatchedAnimationResource(const ResourceInfo* resourceInfo);

u16 Load_PlaneAnimationResource(const ResourceInfo* resourceInfo);
u16 Load_TileAnimationResource(const ResourceInfo* resourceInfo);


// setup
u16 Setup_AnimationResource(struct game_object* gameObject, const ResourceInfo* resourceInfo);
u16 Setup_BatchedAnimationResource(struct game_object* gameObject, const ResourceInfo* resourceInfo);

u16 Setup_StreamedAnimationResource(struct game_object* gameObject, const ResourceInfo* resourceInfo);
u16 Setup_StreamedBatchedAnimationResource(struct game_object* gameObject, const ResourceInfo* resourceInfo);

u16 Setup_PlaneAnimationResource(struct game_object* gameObject, const ResourceInfo* resourceInfo);

u16 Setup_TileAnimationResource(struct game_object* gameObject, const ResourceInfo* resourceInfo);

// streaming

void AnimationUtils_UpdateStreamedBatchedAnimationFrame(struct game_object* gameObject);

// misc

void AnimationUtils_setBatchedAnimationFrame(struct game_object* gameObject, u8 animationFrameIndex);
void AnimationUtils_setStreamedBatchedAnimationFrame(struct game_object* gameObject, u8 animationFrameIndex);

#endif