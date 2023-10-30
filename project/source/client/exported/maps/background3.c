// this file was automatically generated by tmx2c. https://github.com/pw32x/tmx2c
#include "background3.h"
#include "resource_types.h"

// array of metatile indexes. use the metatile look up table to figure out which actual 8x8 tiles to use.
const unsigned short const background3_metatile_map[560] = 
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,5,6,0,0,
    4103,4104,4105,0,0,0,0,0,0,0,0,0,0,0,0,0,4103,4104,4104,4104,4104,4104,4104,4104,4104,4105,0,10,11,0,0,0,0,0,0,12,13,14,0,0,
    4111,4111,4112,0,0,0,0,0,0,0,0,0,0,17,18,0,4115,4116,4116,4116,4116,4116,4116,4116,4116,4117,0,22,23,8216,8217,8218,0,0,0,12,13,14,0,0,
    4123,4124,4112,0,0,0,0,0,0,4125,4125,4125,4125,30,31,0,32,33,33,33,33,33,33,33,33,34,0,22,23,35,36,37,0,0,0,38,39,40,0,0,
    4111,4111,4137,0,0,0,0,0,0,4103,4104,4104,4105,0,0,0,42,4139,4104,4140,45,46,0,47,48,49,0,22,23,35,36,37,0,50,51,52,53,0,0,0,
    4111,4111,4137,0,0,8246,8246,0,0,4151,4111,4111,4112,4152,4153,4154,42,4155,4116,4156,45,0,0,0,42,49,0,61,62,8255,8256,8256,8257,66,67,68,69,0,0,0,
    4111,4111,4137,0,0,0,0,0,0,4151,4111,4111,4166,8263,8263,0,42,72,73,73,74,75,0,76,77,49,0,78,79,80,81,81,82,83,84,85,69,0,0,0,
    4111,4111,4137,0,0,0,0,0,0,4151,4123,4124,4166,4182,4183,4184,89,90,90,90,90,90,90,90,90,91,0,92,93,94,81,81,95,96,97,98,99,0,0,0,
    4111,4111,4137,8246,8246,8246,8246,4103,4104,4196,4111,4111,4197,4104,4104,4104,4104,4104,4104,4104,4104,4104,4104,4104,4104,4104,4104,4104,4104,4104,4104,4104,4104,102,102,102,0,0,0,0,
    4111,4111,4137,0,0,0,0,4151,4111,4111,4111,4111,4111,4111,4111,4111,4199,4200,4201,4202,4203,4204,4111,4205,4111,4137,4151,4111,4111,4111,4111,4111,4137,110,111,112,0,0,0,0,
    4111,4111,4137,0,0,0,0,4151,4111,4111,4111,4111,4111,4111,4111,4111,4209,4210,4211,4212,4213,4214,4111,4215,4111,4137,4151,4111,4111,4111,4111,4111,4137,120,120,120,0,0,0,0,
    4217,4217,4218,0,0,0,0,4219,4217,4217,4217,4217,4217,4217,4217,4217,4217,4217,4217,4217,4217,4217,4217,4217,4217,4218,4219,4217,4217,4217,4217,4217,4218,120,120,120,0,0,0,0,
    4220,4220,4220,0,0,0,0,4221,4220,4220,4220,4220,4220,4220,4220,4220,4220,4220,4220,4220,4220,4220,4220,4220,4220,4220,4221,4220,4220,4220,4220,4220,4220,126,126,126,0,0,0,0,
    
};


extern Tileset background3_tileset;


const void* background3_tilesets[1] = 
{
    &background3_tileset, // Tileset
};

RESOURCE(BANK3) const Map const background3_map = 
{
    MAP_RESOURCE_TYPE,
    background3_metatile_map, // metatile index map data
    background3_tilesets, // tilesets used in the map
    1, // number of tilesets used by this map
    40, // metatile map width
    14, // metatile map height
};

