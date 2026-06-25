#include "resource_infos.h"

#include "breakable_rock_tileset.h"
#include "field_tileset.h"
#include "waterfall_tileset.h"
#include "client\exported\animations\streamed\gun_girl_anim.h"
#include "client\exported\animations\standard\colorTweakerCursor_anim.h"
#include "client\exported\animations\standard\colorTweaker_anim.h"
#include "client\exported\animations\standard\explosion_anim.h"
#include "client\exported\animations\standard\impact_anim.h"
#include "client\exported\animations\standard\kunai_anim.h"
#include "client\exported\animations\standard\rock_particle_anim.h"
#include "client\exported\animations\standard\test_block_anim.h"
#include "client\exported\animations\enemies\enemy_bullet_anim.h"
#include "client\exported\animations\enemies\robotrunner_anim.h"
#include "client\exported\animations\enemies\robotspring_anim.h"
#include "client\exported\animations\enemies\threeshotflyer_anim.h"
#include "client\exported\animations\enemies\walker_anim.h"
#include "client\exported\animations\enemies\walker_big_anim.h"
#include "client\exported\animations\enemies\walker_small_anim.h"
#include "client\exported\animations\enemies\wheeler_anim.h"
#include "client\exported\animations\weapons\bullet_anim.h"
#include "client\exported\animations\weapons\deliveryrobot_anim.h"
#include "client\exported\animations\weapons\shotgun_bullet_anim.h"
#include "client\exported\animations\weapons\shotgun_item_anim.h"
#include "client\exported\animations\animatedtilesets\waterfall_anim.h"
#include "client\exported\palettes\globalPalette.h"
#include "client\exported\maps\bank8\level_001.h"
#include "client\exported\maps\bank4\field.h"
#include "client\exported\maps\bank4\waterfall.h"

const ResourceInfo breakable_rock_tilesetResourceInfo = { /*bank*/ 3, (const Resource*)&breakable_rock_tileset };
const ResourceInfo field_tilesetResourceInfo = { /*bank*/ 3, (const Resource*)&field_tileset };
const ResourceInfo waterfall_tilesetResourceInfo = { /*bank*/ 3, (const Resource*)&waterfall_tileset };
const ResourceInfo gun_girl_animResourceInfo = { /*bank*/ 7, (const Resource*)&gun_girl_anim };
const ResourceInfo colorTweakerCursor_animResourceInfo = { /*bank*/ 2, (const Resource*)&colorTweakerCursor_anim };
const ResourceInfo colorTweaker_animResourceInfo = { /*bank*/ 2, (const Resource*)&colorTweaker_anim };
const ResourceInfo explosion_animResourceInfo = { /*bank*/ 2, (const Resource*)&explosion_anim };
const ResourceInfo impact_animResourceInfo = { /*bank*/ 2, (const Resource*)&impact_anim };
const ResourceInfo kunai_animResourceInfo = { /*bank*/ 2, (const Resource*)&kunai_anim };
const ResourceInfo rock_particle_animResourceInfo = { /*bank*/ 2, (const Resource*)&rock_particle_anim };
const ResourceInfo test_block_animResourceInfo = { /*bank*/ 2, (const Resource*)&test_block_anim };
const ResourceInfo enemy_bullet_animResourceInfo = { /*bank*/ 6, (const Resource*)&enemy_bullet_anim };
const ResourceInfo robotrunner_animResourceInfo = { /*bank*/ 6, (const Resource*)&robotrunner_anim };
const ResourceInfo robotspring_animResourceInfo = { /*bank*/ 6, (const Resource*)&robotspring_anim };
const ResourceInfo threeshotflyer_animResourceInfo = { /*bank*/ 6, (const Resource*)&threeshotflyer_anim };
const ResourceInfo walker_animResourceInfo = { /*bank*/ 6, (const Resource*)&walker_anim };
const ResourceInfo walker_big_animResourceInfo = { /*bank*/ 6, (const Resource*)&walker_big_anim };
const ResourceInfo walker_small_animResourceInfo = { /*bank*/ 6, (const Resource*)&walker_small_anim };
const ResourceInfo wheeler_animResourceInfo = { /*bank*/ 6, (const Resource*)&wheeler_anim };
const ResourceInfo bullet_animResourceInfo = { /*bank*/ 5, (const Resource*)&bullet_anim };
const ResourceInfo deliveryrobot_animResourceInfo = { /*bank*/ 5, (const Resource*)&deliveryrobot_anim };
const ResourceInfo shotgun_bullet_animResourceInfo = { /*bank*/ 5, (const Resource*)&shotgun_bullet_anim };
const ResourceInfo shotgun_item_animResourceInfo = { /*bank*/ 5, (const Resource*)&shotgun_item_anim };
const ResourceInfo waterfall_animResourceInfo = { /*bank*/ 2, (const Resource*)&waterfall_anim };
const ResourceInfo globalPaletteResourceInfo = { /*bank*/ 0, (const Resource*)&globalPalette };
const ResourceInfo level_001_mapResourceInfo = { /*bank*/ 8, (const Resource*)&level_001_map };
const ResourceInfo field_mapResourceInfo = { /*bank*/ 4, (const Resource*)&field_map };
const ResourceInfo waterfall_mapResourceInfo = { /*bank*/ 4, (const Resource*)&waterfall_map };
