#include "resource_infos.h"

#include "background3_tileset.h"
#include "breakable_rock_tileset.h"
#include "waterfall_tileset.h"
#include "client\exported\animations\explosion.h"
#include "client\exported\animations\impact.h"
#include "client\exported\animations\kunai.h"
#include "client\exported\animations\ninja_girl.h"
#include "client\exported\animations\rock_particle.h"
#include "client\exported\animations\walker.h"
#include "client\exported\animations\walker_big.h"
#include "client\exported\animations\walker_small.h"
#include "client\exported\animations\waterfall.h"
#include "client\exported\maps\background3.h"
#include "client\exported\maps\waterfall.h"

const ResourceInfo background3_tilesetResourceInfo = { /*bank*/ 3, (const Resource*)&background3_tileset };
const ResourceInfo breakable_rock_tilesetResourceInfo = { /*bank*/ 3, (const Resource*)&breakable_rock_tileset };
const ResourceInfo waterfall_tilesetResourceInfo = { /*bank*/ 3, (const Resource*)&waterfall_tileset };
const ResourceInfo explosionResourceInfo = { /*bank*/ 2, (const Resource*)&explosion };
const ResourceInfo impactResourceInfo = { /*bank*/ 2, (const Resource*)&impact };
const ResourceInfo kunaiResourceInfo = { /*bank*/ 2, (const Resource*)&kunai };
const ResourceInfo ninja_girlResourceInfo = { /*bank*/ 2, (const Resource*)&ninja_girl };
const ResourceInfo rock_particleResourceInfo = { /*bank*/ 2, (const Resource*)&rock_particle };
const ResourceInfo walkerResourceInfo = { /*bank*/ 2, (const Resource*)&walker };
const ResourceInfo walker_bigResourceInfo = { /*bank*/ 2, (const Resource*)&walker_big };
const ResourceInfo walker_smallResourceInfo = { /*bank*/ 2, (const Resource*)&walker_small };
const ResourceInfo waterfallResourceInfo = { /*bank*/ 2, (const Resource*)&waterfall };
const ResourceInfo background3_mapResourceInfo = { /*bank*/ 4, (const Resource*)&background3_map };
const ResourceInfo waterfall_mapResourceInfo = { /*bank*/ 4, (const Resource*)&waterfall_map };
