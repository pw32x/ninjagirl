#include "engine/resource_types.h"
#include "engine/terrain_manager.h"

#include "exported/rock_particle.h"
#include "exported/explosion.h"

#include "objects/effect.h"

void breakable_rock_tileset_TilesetFunction(unsigned short blockx, unsigned short blocky, const Resource* resource)
{
	CreateInfo createInfo = 
	{ 
		B2P(blockx & TERRAIN_WIDTH_MINUS_ONE) + 8, 
		B2P(blocky) + 8, 
		(const void*)&explosion, 
	};

	GameObject* effect = Effect_Create(&createInfo);
}

const Resource* breakable_rock_tileset_Resource = (const Resource*)&rock_particle;