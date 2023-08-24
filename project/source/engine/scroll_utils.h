#ifndef SCROLL_UTILS_INCLUDE_H
#define SCROLL_UTILS_INCLUDE_H

#include "engine/base_types.h"
#include "engine/map_types.h"
#include "engine/object_types.h"

void ScrollUtils_buildColumn(void);
void ScrollUtils_InitTilemap(void);

extern u16 ScrollUtils_mapColumnToBuild;


#endif