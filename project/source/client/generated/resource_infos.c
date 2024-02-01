#include "resource_infos.h"

#include "background3_tileset.h"
#include "breakable_rock_tileset.h"
#include "waterfall_tileset.h"
#include "client\exported\animations\bullet.h"
#include "client\exported\animations\explosion.h"
#include "client\exported\animations\gun_girl.h"
#include "client\exported\animations\impact.h"
#include "client\exported\animations\kunai.h"
#include "client\exported\animations\robotrunner.h"
#include "client\exported\animations\robotspring.h"
#include "client\exported\animations\rock_particle.h"
#include "client\exported\animations\walker.h"
#include "client\exported\animations\walker_big.h"
#include "client\exported\animations\walker_small.h"
#include "client\exported\animations\waterfall.h"
#include "client\exported\palettes\globalPalette.h"
#include "client\exported\maps\background3.h"
#include "client\exported\maps\waterfall.h"

const ResourceInfo background3_tilesetResourceInfo = { /*bank*/ 3, (const Resource*)&background3_tileset };
const ResourceInfo breakable_rock_tilesetResourceInfo = { /*bank*/ 3, (const Resource*)&breakable_rock_tileset };
const ResourceInfo waterfall_tilesetResourceInfo = { /*bank*/ 3, (const Resource*)&waterfall_tileset };
const ResourceInfo bulletResourceInfo = { /*bank*/ 2, (const Resource*)&bullet };
const ResourceInfo explosionResourceInfo = { /*bank*/ 2, (const Resource*)&explosion };
const ResourceInfo gun_girlResourceInfo = { /*bank*/ 2, (const Resource*)&gun_girl };
const ResourceInfo impactResourceInfo = { /*bank*/ 2, (const Resource*)&impact };
const ResourceInfo kunaiResourceInfo = { /*bank*/ 2, (const Resource*)&kunai };
const ResourceInfo robotrunnerResourceInfo = { /*bank*/ 2, (const Resource*)&robotrunner };
const ResourceInfo robotspringResourceInfo = { /*bank*/ 2, (const Resource*)&robotspring };
const ResourceInfo rock_particleResourceInfo = { /*bank*/ 2, (const Resource*)&rock_particle };
const ResourceInfo walkerResourceInfo = { /*bank*/ 2, (const Resource*)&walker };
const ResourceInfo walker_bigResourceInfo = { /*bank*/ 2, (const Resource*)&walker_big };
const ResourceInfo walker_smallResourceInfo = { /*bank*/ 2, (const Resource*)&walker_small };
const ResourceInfo waterfallResourceInfo = { /*bank*/ 2, (const Resource*)&waterfall };
const ResourceInfo globalPaletteResourceInfo = { /*bank*/ 0, (const Resource*)&globalPalette };
const ResourceInfo background3_mapResourceInfo = { /*bank*/ 4, (const Resource*)&background3_map };
const ResourceInfo waterfall_mapResourceInfo = { /*bank*/ 4, (const Resource*)&waterfall_map };
