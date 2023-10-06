#ifndef RESOURCE_MANAGER_INCLUDE_H
#define RESOURCE_MANAGER_INCLUDE_H

#include "engine/base_types.h"

struct game_object;

typedef void* (*OnResourceLoadedCallback)(const void* resource);

void ResourceManager_Init(OnResourceLoadedCallback callback);

void* ResourceManager_LoadResource(const void* resource);
void* ResourceManager_SetupResource(struct game_object* gameObject, const void* resource);


void ResourceManager_SetOnResourceLoadedCallback(OnResourceLoadedCallback callback);

#endif