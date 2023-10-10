#include "engine/resource_types.h"
#include "engine/terrain_manager.h"
#include "engine/map_types.h"

#include "exported/rock_particle.h"
#include "exported/explosion.h"

#include "objects/particle_effect.h"

const Resource* breakable_rock_tileset_Resource = (const Resource*)&rock_particle;

void breakable_rock_tileset_TilesetFunction(const Tileset* tileset, unsigned short blockx, unsigned short blocky)
{
	CreateInfo createInfo = 
	{ 
		B2P(blockx & TERRAIN_WIDTH_MINUS_ONE) + 4, 
		B2P(blocky) + 4, 
		*tileset->tilesetResource,
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

