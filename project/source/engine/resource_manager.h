#ifndef RESOURCE_MANAGER_INCLUDE_H
#define RESOURCE_MANAGER_INCLUDE_H

#include "engine/base_types.h"

struct game_object;

void ResourceManager_Init(void);
void* ResourceManager_LoadResource(const void* resource);
void* ResourceManager_SetupResource(struct game_object* gameObject, const void* resource);

#endif