#ifndef TILE_TYPES_INCLUDE_H
#define TILE_TYPES_INCLUDE_H

// exported format of tileindex
// tile_type     | blockmap_index | block_index
// 11111           11              111111111
// 0 - 31          0 - 3           0 - 511

#define TILE_TYPE_MASK	0xF800

#define GET_TILE_TYPE(map, x, y, width) (map[(x) + ((y) * (width))] & TILE_TYPE_MASK)

// we start at (1 << 11) so easily perform a bitwise and to find the value
#define TILE_EMPTY				    0
#define TILE_SOLID				 2048
#define TILE_TOPSOLID			 4096
#define TILE_CLIMB				 6144
#define TILE_HURT				 8192
#define TILE_SLOPE45RIGHT		10240
#define TILE_SLOPE45LEFT		12288
#define TILE_SLOPE30RIGHT1		14336
#define TILE_SLOPE30RIGHT2		16384
#define TILE_SLOPE30LEFT1		18432
#define TILE_SLOPE30LEFT2		20480
#define TILE_SLOPE45RIGHTFLAT	22528
#define TILE_SLOPE45LEFTFLAT	24576
#define TILE_SLOPE30RIGHTFLAT	26624
#define TILE_SLOPE30LEFTFLAT	28672
#define TILE_SLOPEHALFHEIGHT	30720
#define TILE_SLOPE15RIGHT1		32768
#define TILE_SLOPE15RIGHT2		34816
#define TILE_SLOPE15RIGHT3		36864
#define TILE_SLOPE15RIGHT4		38912
#define TILE_SLOPE15LEFT1		40960
#define TILE_SLOPE15LEFT2		43008
#define TILE_SLOPE15LEFT3		45056
#define TILE_SLOPE15LEFT4		47104
#define TILE_WATER				49152

#endif