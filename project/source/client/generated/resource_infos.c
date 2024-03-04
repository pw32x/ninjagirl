#include "resource_infos.h"

#include "background3_tileset.h"
#include "breakable_rock_tileset.h"
#include "field_tileset.h"
#include "waterfall_tileset.h"
#include "client\exported\animations\streamed\gun_girl.h"
#include "client\exported\animations\standard\colorTweaker.h"
#include "client\exported\animations\standard\colorTweakerCursor.h"
#include "client\exported\animations\standard\explosion.h"
#include "client\exported\animations\standard\impact.h"
#include "client\exported\animations\standard\kunai.h"
#include "client\exported\animations\standard\rock_particle.h"
#include "client\exported\animations\standard\test_block.h"
#include "client\exported\animations\enemies\robotrunner.h"
#include "client\exported\animations\enemies\robotspring.h"
#include "client\exported\animations\enemies\threeshotflyer.h"
#include "client\exported\animations\enemies\walker.h"
#include "client\exported\animations\enemies\walker_big.h"
#include "client\exported\animations\enemies\walker_small.h"
#include "client\exported\animations\enemies\wheeler.h"
#include "client\exported\animations\weapons\bullet.h"
#include "client\exported\animations\weapons\deliveryrobot.h"
#include "client\exported\animations\weapons\shotgun.h"
#include "client\exported\animations\weapons\shotgun_item.h"
#include "client\exported\animations\animatedtilesets\waterfall.h"
#include "client\exported\palettes\globalPalette.h"
#include "client\exported\maps\background3.h"
#include "client\exported\maps\background3_test.h"
#include "client\exported\maps\field.h"
#include "client\exported\maps\level_001.h"
#include "client\exported\maps\waterfall.h"

const ResourceInfo background3_tilesetResourceInfo = { /*bank*/ 3, (const Resource*)&background3_tileset };
const ResourceInfo breakable_rock_tilesetResourceInfo = { /*bank*/ 3, (const Resource*)&breakable_rock_tileset };
const ResourceInfo field_tilesetResourceInfo = { /*bank*/ 3, (const Resource*)&field_tileset };
const ResourceInfo waterfall_tilesetResourceInfo = { /*bank*/ 3, (const Resource*)&waterfall_tileset };
const ResourceInfo gun_girlResourceInfo = { /*bank*/ 7, (const Resource*)&gun_girl };
const ResourceInfo colorTweakerResourceInfo = { /*bank*/ 2, (const Resource*)&colorTweaker };
const ResourceInfo colorTweakerCursorResourceInfo = { /*bank*/ 2, (const Resource*)&colorTweakerCursor };
const ResourceInfo explosionResourceInfo = { /*bank*/ 2, (const Resource*)&explosion };
const ResourceInfo impactResourceInfo = { /*bank*/ 2, (const Resource*)&impact };
const ResourceInfo kunaiResourceInfo = { /*bank*/ 2, (const Resource*)&kunai };
const ResourceInfo rock_particleResourceInfo = { /*bank*/ 2, (const Resource*)&rock_particle };
const ResourceInfo test_blockResourceInfo = { /*bank*/ 2, (const Resource*)&test_block };
const ResourceInfo robotrunnerResourceInfo = { /*bank*/ 6, (const Resource*)&robotrunner };
const ResourceInfo robotspringResourceInfo = { /*bank*/ 6, (const Resource*)&robotspring };
const ResourceInfo threeshotflyerResourceInfo = { /*bank*/ 6, (const Resource*)&threeshotflyer };
const ResourceInfo walkerResourceInfo = { /*bank*/ 6, (const Resource*)&walker };
const ResourceInfo walker_bigResourceInfo = { /*bank*/ 6, (const Resource*)&walker_big };
const ResourceInfo walker_smallResourceInfo = { /*bank*/ 6, (const Resource*)&walker_small };
const ResourceInfo wheelerResourceInfo = { /*bank*/ 6, (const Resource*)&wheeler };
const ResourceInfo bulletResourceInfo = { /*bank*/ 5, (const Resource*)&bullet };
const ResourceInfo deliveryrobotResourceInfo = { /*bank*/ 5, (const Resource*)&deliveryrobot };
const ResourceInfo shotgunResourceInfo = { /*bank*/ 5, (const Resource*)&shotgun };
const ResourceInfo shotgun_itemResourceInfo = { /*bank*/ 5, (const Resource*)&shotgun_item };
const ResourceInfo waterfallResourceInfo = { /*bank*/ 2, (const Resource*)&waterfall };
const ResourceInfo globalPaletteResourceInfo = { /*bank*/ 0, (const Resource*)&globalPalette };
const ResourceInfo background3_mapResourceInfo = { /*bank*/ 4, (const Resource*)&background3_map };
const ResourceInfo background3_test_mapResourceInfo = { /*bank*/ 4, (const Resource*)&background3_test_map };
const ResourceInfo field_mapResourceInfo = { /*bank*/ 4, (const Resource*)&field_map };
const ResourceInfo level_001_mapResourceInfo = { /*bank*/ 4, (const Resource*)&level_001_map };
const ResourceInfo waterfall_mapResourceInfo = { /*bank*/ 4, (const Resource*)&waterfall_map };
