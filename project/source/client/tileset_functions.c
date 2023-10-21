#include "tileset_functions.h"

#include "engine/resource_types.h"
#include "engine/terrain_manager.h"
#include "engine/map_types.h"

#include "exported/rock_particle.h"
#include "exported/explosion.h"

#include "objects/particle_effect.h"

void breakable_rock_tileset_TilesetFunction(const Tileset* tileset, const Resource* resource, u16 blockx, u16 blocky)
{
	UNUSED(tileset);

	CreateInfo createInfo = 
	{ 
		B2P(blockx) + 4, 
		B2P(blocky) + 4, 
		resource,
	};

	GameObject* effect = ParticleEffect_Create(&createInfo);
	effect->speedx = -15;
	effect->speedy = -60;


	createInfo.startX += 8;
	effect = ParticleEffect_Create(&createInfo);
	effect->speedx = 15;
	effect->speedy = -60;

	createInfo.startY += 8;
	effect = ParticleEffect_Create(&createInfo);
	effect->speedx = 10;
	effect->speedy = -50;

	createInfo.startX -= 8;
	effect = ParticleEffect_Create(&createInfo);
	effect->speedx = -10;
	effect->speedy = -50;
}

