#ifndef GAMEOBJECT_TEMPLATE_TYPES_INCLUDE_H
#define GAMEOBJECT_TEMPLATE_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "engine/resource_types.h"

typedef struct gameobject_template
{
	s8 startHealth;
	s8 damage;

	s8 rectLeft;
	s8 rectTop;
	s8 rectRight;
	s8 rectBottom;

	u8 objectType;
	const ResourceInfo* resourceInfo;
} GameObjectTemplate;

#endif