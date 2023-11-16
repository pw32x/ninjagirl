#include "resource_infos.h"

#include "client\exported\animations\explosion.h"
#include "client\exported\animations\impact.h"
#include "client\exported\animations\kunai.h"
#include "client\exported\animations\ninja_girl.h"
#include "client\exported\animations\rock_particle.h"
#include "client\exported\animations\waterfall.h"
#include "client\exported\maps\background3.h"
#include "client\generated\background3_tileset.h"
#include "client\generated\breakable_rock_tileset.h"
#include "client\generated\waterfall_tileset.h"

const ResourceInfo explosionResourceInfo = 
{
    2,
    (const Resource*)&explosion
};

const ResourceInfo impactResourceInfo = 
{
    2,
    (const Resource*)&impact
};

const ResourceInfo kunaiResourceInfo = 
{
    2,
    (const Resource*)&kunai
};

const ResourceInfo ninja_girlResourceInfo = 
{
    2,
    (const Resource*)&ninja_girl
};

const ResourceInfo rock_particleResourceInfo = 
{
    2,
    (const Resource*)&rock_particle
};

const ResourceInfo waterfallResourceInfo = 
{
    2,
    (const Resource*)&waterfall
};

const ResourceInfo background3_mapResourceInfo = 
{
    4,
    (const Resource*)&background3_map
};

const ResourceInfo background3_tilesetResourceInfo = 
{
    3,
    (const Resource*)&background3_tileset
};

const ResourceInfo breakable_rock_tilesetResourceInfo = 
{
    0,
    (const Resource*)&breakable_rock_tileset
};

const ResourceInfo waterfall_tilesetResourceInfo = 
{
    3,
    (const Resource*)&waterfall_tileset
};

