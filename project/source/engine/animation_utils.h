#ifndef ANIMATION_UTILS_INCLUDE_H
#define ANIMATION_UTILS_INCLUDE_H

#include "SMSLib.h"
#include "engine/animation_types.h"

struct game_object;

BOOL AnimationUtils_updateAnimationBatched(struct game_object* gameObject);
BOOL AnimationUtils_updatePlaneAnimation(struct game_object* gameObject);

u16 Load_AnimationResource(const Animation* animation);
u16 Load_BatchedAnimationResource(const AnimationBatched* animationBatched);
u16 Load_PlaneAnimationResource(const PlaneAnimation* planeAnimation);

u16 Setup_AnimationResource(struct game_object* gameObject, const Animation* animation, u16 vdpTileIndex);
u16 Setup_BatchedAnimationResource(struct game_object* gameObject, const AnimationBatched* animationBatched, u16 vdpTileIndex);
u16 Setup_PlaneAnimationResource(struct game_object* gameObject, const PlaneAnimation* planeAnimation, u16 vdpTileIndex);

#endif