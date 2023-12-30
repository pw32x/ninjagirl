#ifndef TILESET_FUNCTIONS_INCLUDE_H
#define TILESET_FUNCTIONS_INCLUDE_H

#include "engine/base_types.h"
#include "engine/map_types.h"
#include "engine/gameobject_template_types.h"

void breakable_rock_tileset_TilesetFunction(const Tileset* tileset, 
											const GameObjectTemplate* gameObjectTemplate, 
											u16 blockx, 
											u16 blocky);

#endif