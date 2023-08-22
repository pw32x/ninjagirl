#ifndef ANIMATION_UTILS_INCLUDE_H
#define ANIMATION_UTILS_INCLUDE_H

#include "engine/animation_types.h"

struct game_object;

void AnimationUtils_setupAnimation(struct game_object* gameObject, const Animation* animation, u8 vdpTileIndex);
void AnimationUtils_updateAnimation(struct game_object* gameObject);

#endif