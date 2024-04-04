#include "tileset_functions.h"

#include "engine/resource_types.h"
#include "engine/terrain_manager.h"
#include "engine/map_types.h"
#include "engine/object_manager_create.h"

#include "exported/animations/standard/rock_particle.h"
#include "exported/animations/standard/explosion.h"

#include "objects/particle_effect.h"

void breakable_rock_tileset_TilesetFunction(const Tileset* tileset, 
											const GameObjectTemplate* gameObjectTemplate, 
											u16 blockx, 
											u16 blocky)
{
	UNUSED(tileset);

	CreateInfo createInfo = 
	{ 
		gameObjectTemplate,
		B2P(blockx) + 4, 
		B2P(blocky) + 4		
	};

	/*
	GameObject* effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
	effect->speedx = -15;
	effect->speedy = -60;


	createInfo.startX += 8;
	effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
	effect->speedx = 15;
	effect->speedy = -60;

	createInfo.startY += 8;
	effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
	effect->speedx = 10;
	effect->speedy = -50;

	createInfo.startX -= 8;
	effect = ObjectManager_CreateObjectByCreateInfo(&createInfo);
	effect->speedx = -10;
	effect->speedy = -50;
	*/
}

