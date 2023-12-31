#ifndef CREATEINFO_TYPES_INCLUDE_H
#define CREATEINFO_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "engine/gameobject_template_types.h"

typedef struct create_info
{
	const GameObjectTemplate* gameObjectTemplate;
	s16 startX;
	s16 startY;	
} CreateInfo;

#endif