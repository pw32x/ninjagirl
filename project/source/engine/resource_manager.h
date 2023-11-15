#ifndef RESOURCE_MANAGER_INCLUDE_H
#define RESOURCE_MANAGER_INCLUDE_H

#include "engine/base_types.h"
#include "engine/resource_types.h"

struct game_object;

typedef void* (*OnResourceLoadedCallback)(const ResourceInfo* resourceInfo);

void ResourceManager_Init(OnResourceLoadedCallback callback);

void* ResourceManager_LoadResource(const ResourceInfo* resourceInfo);
void* ResourceManager_SetupResource(struct game_object* gameObject, const ResourceInfo* resourceInfo);


void ResourceManager_SetOnResourceLoadedCallback(OnResourceLoadedCallback callback);

#endif