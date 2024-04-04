#ifndef CREATEINFO_TYPES_INCLUDE_H
#define CREATEINFO_TYPES_INCLUDE_H

#include "engine/base_types.h"
#include "engine/gameobject_template_types.h"
#include "engine/command_types.h"

#define STANDARD_CREATE_INFO \
const GameObjectTemplate* gameObjectTemplate;\
s16 startX;\
s16 startY;\
s16 speedX;\
s16 speedY;

typedef struct create_info
{
	STANDARD_CREATE_INFO
	u16 extra;
} CreateInfo;

typedef struct commandrunner_create_info
{
	STANDARD_CREATE_INFO
	const Command* commands;
} CommandRunnerCreateInfo;

typedef struct 
{
	STANDARD_CREATE_INFO
	u8 startFrameNumber;
} EffectCreateInfo;

#endif