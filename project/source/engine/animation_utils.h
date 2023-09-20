#ifndef ANIMATION_UTILS_INCLUDE_H
#define ANIMATION_UTILS_INCLUDE_H

#include "SMSLib.h"
#include "engine/animation_types.h"

struct game_object;

#define ANIMATION_NO_CHANGE			0
#define ANIMATION_CHANGED_FRAME		1
#define ANIMATION_FINISHED			2

u8 AnimationUtils_updateAnimation(struct game_object* gameObject);
u8 AnimationUtils_updateAnimationBatched(struct game_object* gameObject);
u8 AnimationUtils_updateAnimationBatched_noLoop(struct game_object* gameObject);
u8 AnimationUtils_updatePlaneAnimation(struct game_object* gameObject);

void AnimationUtils_setAnimationFrameBatched(struct game_object* gameObject, u8 animationFrameIndex);

u16 Load_AnimationResource(const Animation* animation);
u16 Load_BatchedAnimationResource(const AnimationBatched* animationBatched);
u16 Load_PlaneAnimationResource(const PlaneAnimation* planeAnimation);

u16 Setup_AnimationResource(struct game_object* gameObject, const Animation* animation);
u16 Setup_BatchedAnimationResource(struct game_object* gameObject, const AnimationBatched* animationBatched);
u16 Setup_PlaneAnimationResource(struct game_object* gameObject, const PlaneAnimation* planeAnimation);

#endif