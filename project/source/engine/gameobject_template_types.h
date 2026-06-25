#ifndef GAMEOBJECT_TEMPLATE_TYPES_INCLUDE_H
#define GAMEOBJECT_TEMPLATE_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "engine/resource_types.h"
#include "engine/object_types.h"

struct create_info;

typedef GameObject* (*InitObjectFunctionType)(GameObject* gameObject, const struct create_info* createInfo);

typedef struct gameobject_template
{
	// match the order of decleration in object_types.h
	s8 startHealth;
	s8 damage;

	s16 rectLeft;
	s16 rectTop;
	s16 rectRight;
	s16 rectBottom;

	u8 objectType;
	const ResourceInfo* resourceInfo;
	const ResourceInfo** extraResources;

	InitObjectFunctionType initFunction;
} GameObjectTemplate;

#endif