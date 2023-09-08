#include "evil_eye.h"


unsigned char const evil_eyeTileData[3072] = // 96tiles x 32 bytes
{
// tile: 0
    0x02, 0x01, 0x00, 0x01, 
    0x06, 0x02, 0x01, 0x01, 
    0x0c, 0x04, 0x07, 0x03, 
    0x19, 0x09, 0x07, 0x07, 
    0x32, 0x12, 0x1f, 0x0f, 
    0x64, 0x35, 0x0e, 0x1f, 
    0xc1, 0x73, 0x41, 0x3e, 
    0x83, 0x43, 0x23, 0x7c, 
// tile: 1
    0x86, 0x46, 0x27, 0x78, 
    0xc6, 0x57, 0x61, 0x38, 
    0xa5, 0x34, 0x62, 0x19, 
    0xa5, 0x14, 0x42, 0x39, 
    0xa6, 0x17, 0x41, 0x38, 
    0xa6, 0x17, 0x41, 0x38, 
    0xa6, 0x17, 0x41, 0x38, 
    0xa6, 0x17, 0x41, 0x38, 
// tile: 2
    0x1f, 0x00, 0xe0, 0xff, 
    0x1f, 0x10, 0xf0, 0xef, 
    0x80, 0xff, 0x80, 0xff, 
    0x00, 0x40, 0x80, 0xff, 
    0x7f, 0xff, 0x40, 0x80, 
    0xfe, 0xfe, 0xc1, 0x00, 
    0x81, 0xbe, 0xfe, 0x01, 
    0x01, 0x7e, 0xfe, 0x01, 
// tile: 3
    0x00, 0xe1, 0xff, 0x1e, 
    0x0c, 0xed, 0xff, 0x1e, 
    0xad, 0x2d, 0x7f, 0x9e, 
    0xa1, 0x33, 0x6d, 0x9e, 
    0x7f, 0xff, 0x9e, 0x00, 
    0x7f, 0xff, 0x80, 0x00, 
    0x7f, 0xff, 0x80, 0x00, 
    0x3f, 0xbf, 0xc0, 0x00, 
// tile: 4
    0xfd, 0x00, 0x02, 0xfc, 
    0xfd, 0x00, 0x02, 0xfc, 
    0x02, 0xfe, 0x03, 0xfc, 
    0x01, 0x03, 0x01, 0xfe, 
    0x80, 0x81, 0x80, 0x7f, 
    0xc1, 0xc0, 0xc1, 0x3f, 
    0x6e, 0x60, 0xee, 0x1f, 
    0xae, 0x30, 0x6e, 0x9f, 
// tile: 5
    0x18, 0xd8, 0xf8, 0x07, 
    0x18, 0xf8, 0xe0, 0x07, 
    0x18, 0x78, 0xe0, 0x07, 
    0x98, 0xf8, 0x60, 0x07, 
    0x68, 0x08, 0x90, 0x67, 
    0x68, 0x08, 0x90, 0x67, 
    0x98, 0xf8, 0x60, 0x07, 
    0x18, 0x79, 0xe0, 0x07, 
// tile: 6
    0x00, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 
    0x40, 0x00, 0x80, 0x00, 
    0xa0, 0x80, 0xc0, 0x00, 
    0x50, 0xc0, 0x60, 0x80, 
    0x58, 0xc0, 0x60, 0x80, 
    0x24, 0x60, 0x38, 0xc0, 
    0x14, 0x60, 0x08, 0xf0, 
// tile: 7
    0x74, 0xc0, 0x48, 0xb0, 
    0x74, 0xc0, 0x48, 0xb0, 
    0x14, 0x60, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0xa0, 0x08, 0xf0, 
// tile: 8
    0xa6, 0x17, 0x41, 0x38, 
    0xa6, 0x16, 0x47, 0x38, 
    0xa3, 0x13, 0x43, 0x3c, 
    0xa1, 0x11, 0x41, 0x3e, 
    0xa0, 0x10, 0x40, 0x3f, 
    0xa1, 0x10, 0x41, 0x3f, 
    0xa6, 0x10, 0x46, 0x3f, 
    0x96, 0x18, 0x76, 0x0f, 
// tile: 9
    0x62, 0x0c, 0x12, 0x0f, 
    0x28, 0x0e, 0x18, 0x07, 
    0x16, 0x07, 0x0e, 0x01, 
    0x09, 0x01, 0x07, 0x00, 
    0x06, 0x00, 0x01, 0x00, 
    0x02, 0x00, 0x01, 0x00, 
    0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 10
    0x1e, 0xde, 0xe1, 0x00, 
    0x04, 0xe5, 0xfb, 0x00, 
    0x18, 0x67, 0xe7, 0x18, 
    0x98, 0xa7, 0xe7, 0x18, 
    0x67, 0xe7, 0x58, 0x80, 
    0x7f, 0x7f, 0x40, 0x80, 
    0x00, 0x00, 0x00, 0xff, 
    0x00, 0x60, 0x00, 0xff, 
// tile: 11
    0x60, 0xf0, 0x60, 0x9f, 
    0x60, 0x90, 0x00, 0xff, 
    0x60, 0x90, 0x00, 0xff, 
    0x60, 0x9f, 0x00, 0xff, 
    0xff, 0x00, 0x00, 0xff, 
    0x00, 0x00, 0xff, 0x00, 
    0xff, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 12
    0x19, 0xfb, 0xe1, 0x06, 
    0x19, 0xdb, 0xf9, 0x06, 
    0x30, 0xb1, 0xf0, 0x0f, 
    0x60, 0x60, 0xe0, 0x1f, 
    0xd8, 0xc0, 0xd8, 0x3f, 
    0x98, 0x80, 0x98, 0x7f, 
    0x06, 0x00, 0x06, 0xff, 
    0x06, 0x00, 0x06, 0xff, 
// tile: 13
    0x01, 0x00, 0x01, 0xff, 
    0x00, 0x61, 0x00, 0xff, 
    0x63, 0xf7, 0x63, 0x9c, 
    0x66, 0x9e, 0x07, 0xf8, 
    0x81, 0x7c, 0x7e, 0x80, 
    0x01, 0x00, 0xfe, 0x00, 
    0xfe, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 14
    0x94, 0xe0, 0x88, 0x70, 
    0x94, 0xe0, 0x88, 0x70, 
    0x74, 0xc0, 0x48, 0xb0, 
    0x74, 0xc0, 0x48, 0xb0, 
    0x04, 0x70, 0x18, 0xe0, 
    0x04, 0x30, 0x18, 0xe0, 
    0x24, 0x70, 0x38, 0xc0, 
    0x64, 0x60, 0x78, 0x80, 
// tile: 15
    0x58, 0xc0, 0x60, 0x80, 
    0x10, 0x80, 0x60, 0x80, 
    0x60, 0x00, 0x80, 0x00, 
    0x40, 0x00, 0x80, 0x00, 
    0x80, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 16
    0x02, 0x01, 0x00, 0x01, 
    0x06, 0x02, 0x01, 0x01, 
    0x0c, 0x04, 0x07, 0x03, 
    0x19, 0x09, 0x07, 0x07, 
    0x33, 0x12, 0x1f, 0x0f, 
    0x71, 0x30, 0x1f, 0x0f, 
    0xfc, 0x61, 0x62, 0x1f, 
    0x9e, 0x43, 0x22, 0x7d, 
// tile: 17
    0x80, 0x5e, 0x20, 0x7f, 
    0xc0, 0x50, 0x60, 0x3f, 
    0xa0, 0x30, 0x60, 0x1f, 
    0xa0, 0x10, 0x40, 0x3f, 
    0xa0, 0x10, 0x40, 0x3f, 
    0xa0, 0x10, 0x40, 0x3f, 
    0xa0, 0x10, 0x40, 0x3f, 
    0xa0, 0x18, 0x40, 0x3f, 
// tile: 18
    0x07, 0x00, 0xf8, 0xff, 
    0x07, 0x04, 0xfc, 0xfb, 
    0x80, 0xcf, 0x80, 0xff, 
    0xc0, 0x00, 0xc0, 0xff, 
    0xe7, 0x07, 0xe4, 0xf8, 
    0xef, 0x0f, 0xec, 0xf0, 
    0x18, 0x1b, 0x1f, 0xe0, 
    0x30, 0x37, 0x3f, 0xc0, 
// tile: 19
    0x66, 0x68, 0x79, 0x87, 
    0x65, 0x79, 0x1b, 0x87, 
    0x5b, 0x43, 0x27, 0x9f, 
    0x58, 0x40, 0x27, 0x9f, 
    0x67, 0x7f, 0x1f, 0x80, 
    0x67, 0x7f, 0x18, 0x80, 
    0x67, 0x7f, 0x18, 0x80, 
    0x63, 0x7b, 0x1c, 0x80, 
// tile: 20
    0xfd, 0x00, 0x02, 0xfc, 
    0xfd, 0x00, 0x02, 0xfc, 
    0x02, 0xfe, 0x03, 0xfc, 
    0x01, 0x03, 0x01, 0xfe, 
    0xf8, 0xf9, 0x08, 0x07, 
    0xed, 0xec, 0x1d, 0x03, 
    0x16, 0xe6, 0xee, 0x11, 
    0x1b, 0xe3, 0xe7, 0x18, 
// tile: 21
    0x41, 0x5d, 0xff, 0x80, 
    0x61, 0x6f, 0xde, 0x80, 
    0x71, 0x77, 0xce, 0x80, 
    0x79, 0xff, 0x46, 0x80, 
    0xf6, 0xf0, 0x89, 0x06, 
    0xf6, 0xf0, 0x09, 0x06, 
    0xf9, 0xff, 0x06, 0x00, 
    0xf1, 0xf7, 0x0e, 0x00, 
// tile: 22
    0x00, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 
    0x40, 0x00, 0x80, 0x00, 
    0xa0, 0x80, 0xc0, 0x00, 
    0x50, 0xc0, 0x60, 0x80, 
    0x58, 0xc0, 0x60, 0x80, 
    0x24, 0x60, 0x38, 0xc0, 
    0x14, 0x20, 0x08, 0xf0, 
// tile: 23
    0x94, 0xa0, 0x88, 0x70, 
    0x94, 0xa0, 0x08, 0x70, 
    0x94, 0xa0, 0x08, 0x70, 
    0x94, 0xa0, 0x08, 0x70, 
    0x94, 0xa0, 0x08, 0x70, 
    0x94, 0xa0, 0x08, 0x70, 
    0x94, 0xa0, 0x08, 0x70, 
    0x94, 0xa0, 0x08, 0x70, 
// tile: 24
    0xb8, 0x0c, 0x48, 0x37, 
    0xb8, 0x0c, 0x48, 0x37, 
    0xa0, 0x18, 0x40, 0x3f, 
    0xa0, 0x10, 0x40, 0x3f, 
    0xa0, 0x10, 0x40, 0x3f, 
    0xa0, 0x10, 0x40, 0x3f, 
    0xa1, 0x10, 0x41, 0x3f, 
    0x91, 0x18, 0x71, 0x0f, 
// tile: 25
    0x6a, 0x0c, 0x1a, 0x07, 
    0x28, 0x0e, 0x18, 0x07, 
    0x16, 0x07, 0x0e, 0x01, 
    0x09, 0x01, 0x07, 0x00, 
    0x06, 0x00, 0x01, 0x00, 
    0x02, 0x00, 0x01, 0x00, 
    0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 26
    0x61, 0x7d, 0x1e, 0x80, 
    0x60, 0x6e, 0x7f, 0x80, 
    0x31, 0x36, 0x3e, 0xc1, 
    0x19, 0x1a, 0x1e, 0xe1, 
    0x6e, 0x0e, 0x6d, 0xf0, 
    0x67, 0x07, 0x64, 0xf8, 
    0x80, 0x00, 0x80, 0xff, 
    0x80, 0x06, 0x80, 0xff, 
// tile: 27
    0x06, 0x0f, 0x06, 0xf9, 
    0x06, 0x09, 0x00, 0xff, 
    0x06, 0x09, 0x00, 0xff, 
    0x06, 0xf9, 0x00, 0xff, 
    0xff, 0x00, 0x00, 0xff, 
    0x00, 0x00, 0xff, 0x00, 
    0xff, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 28
    0xe1, 0xef, 0x1e, 0x00, 
    0x41, 0x5d, 0xbf, 0x00, 
    0x83, 0x7b, 0x7f, 0x80, 
    0x86, 0x76, 0x7e, 0x81, 
    0x7d, 0x7c, 0x8d, 0x03, 
    0xf9, 0xf8, 0x09, 0x07, 
    0x01, 0x00, 0x01, 0xff, 
    0x01, 0x00, 0x01, 0xff, 
// tile: 29
    0x01, 0x00, 0x01, 0xff, 
    0x00, 0x07, 0x00, 0xff, 
    0x06, 0x0d, 0x05, 0xfa, 
    0x06, 0xf9, 0x01, 0xfe, 
    0x81, 0x7e, 0x7e, 0x80, 
    0x01, 0x00, 0xfe, 0x00, 
    0xfe, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 30
    0x94, 0xa0, 0x08, 0x70, 
    0x94, 0xa0, 0x88, 0x70, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x84, 0x30, 0x98, 0xe0, 
    0x84, 0x30, 0x98, 0xe0, 
    0x84, 0x30, 0x98, 0xe0, 
    0xa4, 0x60, 0xb8, 0xc0, 
// tile: 31
    0x58, 0xc0, 0x60, 0x80, 
    0x10, 0x80, 0x60, 0x80, 
    0x60, 0x00, 0x80, 0x00, 
    0x40, 0x00, 0x80, 0x00, 
    0x80, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 32
    0x01, 0x00, 0x00, 0x00, 
    0x03, 0x01, 0x01, 0x00, 
    0x06, 0x02, 0x01, 0x01, 
    0x0c, 0x04, 0x07, 0x03, 
    0x19, 0x09, 0x07, 0x07, 
    0x33, 0x12, 0x1f, 0x0f, 
    0x66, 0x34, 0x0e, 0x1f, 
    0xc6, 0x78, 0x46, 0x3f, 
// tile: 33
    0x86, 0x40, 0x26, 0x7f, 
    0x81, 0x41, 0x21, 0x7e, 
    0xc3, 0x53, 0x63, 0x3c, 
    0xa6, 0x36, 0x67, 0x18, 
    0xa6, 0x17, 0x41, 0x38, 
    0xa5, 0x14, 0x42, 0x39, 
    0xa5, 0x14, 0x42, 0x39, 
    0xa6, 0x17, 0x41, 0x38, 
// tile: 34
    0xff, 0x00, 0x00, 0x00, 
    0x08, 0xf8, 0x0f, 0xf0, 
    0x07, 0x04, 0xfc, 0xfb, 
    0x20, 0x1f, 0xc0, 0xff, 
    0x20, 0x30, 0xe0, 0xdf, 
    0x00, 0xe0, 0x00, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
    0x7f, 0x7f, 0x40, 0x80, 
// tile: 35
    0xf8, 0xf8, 0xc7, 0x00, 
    0x87, 0xb8, 0xf8, 0x07, 
    0x07, 0x78, 0xf8, 0x07, 
    0x09, 0xe8, 0xfe, 0x07, 
    0x19, 0xdc, 0xea, 0x07, 
    0xbf, 0x3f, 0x47, 0x80, 
    0xbf, 0x3f, 0x40, 0x80, 
    0x7f, 0xff, 0x80, 0x00, 
// tile: 36
    0xfe, 0x00, 0x00, 0x00, 
    0x01, 0x00, 0xfe, 0x00, 
    0xfd, 0x00, 0x02, 0xfc, 
    0x02, 0xfe, 0x03, 0xfc, 
    0x00, 0x03, 0x00, 0xff, 
    0x06, 0x01, 0x06, 0xff, 
    0x07, 0x00, 0x07, 0xff, 
    0x98, 0x80, 0x98, 0x7f, 
// tile: 37
    0xd8, 0xc0, 0xd8, 0x3f, 
    0x60, 0x60, 0xe0, 0x1f, 
    0xb0, 0x30, 0x70, 0x8f, 
    0x98, 0x58, 0x78, 0x87, 
    0x98, 0x78, 0x60, 0x87, 
    0x18, 0x78, 0xe0, 0x07, 
    0x98, 0xf8, 0x60, 0x07, 
    0x98, 0xf8, 0x60, 0x07, 
// tile: 38
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 
    0x40, 0x00, 0x80, 0x00, 
    0xa0, 0x80, 0xc0, 0x00, 
    0x50, 0xc0, 0x60, 0x80, 
    0x58, 0xc0, 0x60, 0x80, 
    0x24, 0x60, 0x38, 0xc0, 
// tile: 39
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x60, 0x08, 0xf0, 
    0x74, 0xc0, 0x48, 0xb0, 
    0x74, 0xc0, 0x48, 0xb0, 
    0x14, 0x60, 0x08, 0xf0, 
// tile: 40
    0xa6, 0x17, 0x41, 0x38, 
    0xa6, 0x17, 0x41, 0x38, 
    0xa6, 0x17, 0x41, 0x38, 
    0xa6, 0x17, 0x41, 0x38, 
    0xa6, 0x16, 0x47, 0x38, 
    0xa3, 0x13, 0x43, 0x3c, 
    0xa1, 0x11, 0x41, 0x3e, 
    0xa6, 0x10, 0x46, 0x3f, 
// tile: 41
    0x96, 0x18, 0x76, 0x0f, 
    0x62, 0x0c, 0x12, 0x0f, 
    0x28, 0x0e, 0x18, 0x07, 
    0x16, 0x07, 0x0e, 0x01, 
    0x09, 0x01, 0x07, 0x00, 
    0x06, 0x00, 0x01, 0x00, 
    0x02, 0x00, 0x01, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 42
    0x7f, 0xff, 0x80, 0x00, 
    0x7f, 0xff, 0x80, 0x00, 
    0x3f, 0xbf, 0xc0, 0x00, 
    0x1e, 0xde, 0xe1, 0x00, 
    0x04, 0xe5, 0xfb, 0x00, 
    0x18, 0x67, 0xe7, 0x18, 
    0x98, 0xa7, 0xe7, 0x18, 
    0xe7, 0xe7, 0xd8, 0x00, 
// tile: 43
    0x7f, 0x7f, 0x40, 0x80, 
    0x00, 0x00, 0x00, 0xff, 
    0x00, 0x60, 0x00, 0xff, 
    0x60, 0xf0, 0x60, 0x9f, 
    0x60, 0x9f, 0x00, 0xff, 
    0xff, 0x00, 0x00, 0xff, 
    0xff, 0x00, 0x00, 0xff, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 44
    0x98, 0xf8, 0x60, 0x07, 
    0x68, 0x08, 0x90, 0x67, 
    0x68, 0x08, 0x90, 0x67, 
    0x18, 0xf8, 0xe0, 0x07, 
    0x18, 0xd9, 0xf8, 0x07, 
    0x31, 0xb3, 0xf1, 0x0e, 
    0x61, 0x63, 0xe1, 0x1e, 
    0xd8, 0xc1, 0xd8, 0x3f, 
// tile: 45
    0x98, 0x80, 0x98, 0x7f, 
    0x07, 0x00, 0x07, 0xff, 
    0x00, 0x07, 0x00, 0xff, 
    0x03, 0x07, 0x03, 0xfc, 
    0x06, 0xfe, 0x07, 0xf8, 
    0x81, 0x7c, 0x7e, 0x80, 
    0x81, 0x7c, 0x7e, 0x80, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 46
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0xe0, 0x08, 0xf0, 
    0xe4, 0x10, 0x18, 0xe0, 
    0xe4, 0x10, 0x18, 0xe0, 
    0x64, 0xf0, 0x78, 0x80, 
// tile: 47
    0x64, 0x60, 0x78, 0x80, 
    0x58, 0xc0, 0x60, 0x80, 
    0x10, 0x80, 0x60, 0x80, 
    0x60, 0x00, 0x80, 0x00, 
    0x40, 0x00, 0x80, 0x00, 
    0x80, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 48
    0x01, 0x00, 0x00, 0x00, 
    0x03, 0x01, 0x01, 0x00, 
    0x06, 0x02, 0x01, 0x01, 
    0x0c, 0x04, 0x07, 0x03, 
    0x19, 0x09, 0x07, 0x07, 
    0x33, 0x12, 0x1f, 0x0f, 
    0x67, 0x34, 0x0f, 0x1f, 
    0xc3, 0x70, 0x43, 0x3f, 
// tile: 49
    0x81, 0x58, 0x21, 0x7f, 
    0x98, 0x4c, 0x28, 0x77, 
    0x98, 0x4c, 0x28, 0x77, 
    0x81, 0x59, 0x21, 0x7e, 
    0xc1, 0x51, 0x60, 0x3e, 
    0xa1, 0x31, 0x60, 0x1e, 
    0xa1, 0x11, 0x40, 0x3e, 
    0xa1, 0x11, 0x40, 0x3e, 
// tile: 50
    0xff, 0x00, 0x00, 0x00, 
    0x08, 0xf8, 0x0f, 0xf0, 
    0x07, 0x00, 0xf8, 0xff, 
    0x98, 0xe7, 0x80, 0xff, 
    0x98, 0x3c, 0x98, 0xe7, 
    0x00, 0x18, 0x00, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
    0x9f, 0x1f, 0x90, 0xe0, 
// tile: 51
    0xbf, 0x3f, 0xb0, 0xc0, 
    0x60, 0x6f, 0x7f, 0x80, 
    0xc0, 0xdf, 0xff, 0x00, 
    0x99, 0xa1, 0xe7, 0x1e, 
    0x95, 0xe5, 0x6f, 0x1e, 
    0x6d, 0x0d, 0x9f, 0x7e, 
    0x61, 0x03, 0x9d, 0x7e, 
    0x9f, 0xff, 0x7e, 0x00, 
// tile: 52
    0xfe, 0x00, 0x00, 0x00, 
    0x01, 0x00, 0xfe, 0x00, 
    0xfd, 0x00, 0x02, 0xfc, 
    0x02, 0xfe, 0x03, 0xfc, 
    0x01, 0x03, 0x01, 0xfe, 
    0x00, 0x01, 0x00, 0xff, 
    0x01, 0x00, 0x01, 0xff, 
    0xe6, 0xe0, 0x26, 0x1f, 
// tile: 53
    0xb6, 0xb0, 0x76, 0x0f, 
    0x58, 0x98, 0xb8, 0x47, 
    0x6c, 0x8c, 0x9c, 0x63, 
    0x06, 0x76, 0xfe, 0x01, 
    0x86, 0xbe, 0x78, 0x01, 
    0xc6, 0xde, 0x38, 0x01, 
    0xe6, 0xfe, 0x18, 0x01, 
    0xda, 0xc2, 0x24, 0x19, 
// tile: 54
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 
    0x40, 0x00, 0x80, 0x00, 
    0xa0, 0x80, 0xc0, 0x00, 
    0x50, 0xc0, 0x60, 0x80, 
    0x58, 0xc0, 0x60, 0x80, 
    0x24, 0x60, 0x38, 0xc0, 
// tile: 55
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
// tile: 56
    0xa1, 0x11, 0x40, 0x3e, 
    0xa1, 0x11, 0x40, 0x3e, 
    0xa1, 0x11, 0x41, 0x3e, 
    0xa0, 0x10, 0x40, 0x3f, 
    0xa0, 0x10, 0x40, 0x3f, 
    0xa1, 0x10, 0x41, 0x3f, 
    0x91, 0x18, 0x71, 0x0f, 
    0x6a, 0x0c, 0x1a, 0x07, 
// tile: 57
    0x28, 0x0e, 0x18, 0x07, 
    0x16, 0x07, 0x0e, 0x01, 
    0x09, 0x01, 0x07, 0x00, 
    0x06, 0x00, 0x01, 0x00, 
    0x02, 0x00, 0x01, 0x00, 
    0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 58
    0x8f, 0xef, 0x70, 0x00, 
    0x87, 0xf7, 0x78, 0x00, 
    0x81, 0xb9, 0xfe, 0x00, 
    0xc6, 0xd9, 0xf9, 0x06, 
    0x66, 0x69, 0x79, 0x86, 
    0xb9, 0x39, 0xb6, 0xc0, 
    0x9f, 0x1f, 0x90, 0xe0, 
    0x00, 0x00, 0x00, 0xff, 
// tile: 59
    0x00, 0x18, 0x00, 0xff, 
    0x18, 0x3c, 0x18, 0xe7, 
    0x18, 0xe7, 0x00, 0xff, 
    0xff, 0x00, 0x00, 0xff, 
    0x00, 0x00, 0xff, 0x00, 
    0xff, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 60
    0xda, 0xc2, 0x24, 0x19, 
    0x86, 0xbe, 0x78, 0x01, 
    0x06, 0x76, 0xfe, 0x01, 
    0x0c, 0xec, 0xfc, 0x03, 
    0x18, 0xd8, 0xf8, 0x07, 
    0xf6, 0xf0, 0x36, 0x0f, 
    0xe6, 0xe0, 0x26, 0x1f, 
    0x01, 0x00, 0x01, 0xff, 
// tile: 61
    0x00, 0x01, 0x00, 0xff, 
    0x03, 0x07, 0x03, 0xfc, 
    0x06, 0xfe, 0x07, 0xf8, 
    0x81, 0x7c, 0x7e, 0x80, 
    0x01, 0x00, 0xfe, 0x00, 
    0xfe, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 62
    0x14, 0x20, 0x08, 0xf0, 
    0x04, 0x30, 0x18, 0xe0, 
    0x04, 0x70, 0x18, 0xe0, 
    0x64, 0xd0, 0x58, 0xa0, 
    0x64, 0xd0, 0x58, 0xa0, 
    0x64, 0x70, 0x78, 0x80, 
    0x64, 0x60, 0x78, 0x80, 
    0x58, 0xc0, 0x60, 0x80, 
// tile: 63
    0x10, 0x80, 0x60, 0x80, 
    0x60, 0x00, 0x80, 0x00, 
    0x40, 0x00, 0x80, 0x00, 
    0x80, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 64
    0x01, 0x00, 0x00, 0x00, 
    0x03, 0x01, 0x01, 0x00, 
    0x06, 0x02, 0x01, 0x01, 
    0x0c, 0x04, 0x07, 0x03, 
    0x19, 0x09, 0x07, 0x07, 
    0x33, 0x12, 0x1f, 0x0f, 
    0x67, 0x34, 0x0f, 0x1f, 
    0xc0, 0x70, 0x40, 0x3f, 
// tile: 65
    0x80, 0x46, 0x20, 0x7f, 
    0x86, 0x4f, 0x26, 0x79, 
    0x86, 0x5f, 0x26, 0x79, 
    0x98, 0x4e, 0x28, 0x77, 
    0x98, 0x4c, 0x28, 0x77, 
    0x80, 0x58, 0x20, 0x7f, 
    0xc0, 0x50, 0x60, 0x3f, 
    0xa0, 0x30, 0x60, 0x1f, 
// tile: 66
    0xff, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0x00, 0xff, 
    0x00, 0x00, 0xff, 0xff, 
    0x81, 0xc2, 0x80, 0xff, 
    0x81, 0x03, 0x81, 0xfe, 
    0x80, 0x01, 0x80, 0xff, 
    0x80, 0x00, 0x80, 0xff, 
    0x67, 0x07, 0x64, 0xf8, 
// tile: 67
    0x6f, 0x0f, 0x6c, 0xf0, 
    0x18, 0x1b, 0x1f, 0xe0, 
    0x30, 0x37, 0x3f, 0xc0, 
    0x61, 0x6e, 0x7e, 0x81, 
    0x61, 0x7e, 0x1e, 0x81, 
    0x58, 0x46, 0x27, 0x99, 
    0x58, 0x46, 0x27, 0x99, 
    0x61, 0x7f, 0x1f, 0x80, 
// tile: 68
    0xff, 0x00, 0x00, 0x00, 
    0x80, 0x80, 0xff, 0x00, 
    0x7f, 0x00, 0x80, 0xff, 
    0x80, 0x7f, 0x00, 0xff, 
    0x80, 0xc0, 0x80, 0x7f, 
    0x00, 0x80, 0x00, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
    0xfe, 0xfe, 0x02, 0x01, 
// tile: 69
    0xfa, 0xfb, 0x06, 0x01, 
    0x05, 0xf9, 0xfb, 0x04, 
    0x06, 0xf8, 0xf9, 0x06, 
    0x90, 0x17, 0x7f, 0xe0, 
    0x18, 0x3b, 0xd7, 0xe0, 
    0x3c, 0x7d, 0xa3, 0xc0, 
    0x7e, 0xff, 0x41, 0x80, 
    0xfd, 0xfc, 0x82, 0x01, 
// tile: 70
    0x80, 0x00, 0x00, 0x00, 
    0x40, 0x00, 0x80, 0x00, 
    0x60, 0x00, 0x80, 0x00, 
    0x90, 0x80, 0xe0, 0x00, 
    0x68, 0xe0, 0x70, 0x80, 
    0x14, 0x70, 0x18, 0xe0, 
    0x56, 0x30, 0x58, 0xe0, 
    0x88, 0x18, 0x8e, 0xf0, 
// tile: 71
    0x06, 0x08, 0x00, 0xfe, 
    0x86, 0x88, 0x80, 0x7e, 
    0xc6, 0xc8, 0xc0, 0x3e, 
    0x66, 0x68, 0xe0, 0x1e, 
    0x66, 0xe8, 0x80, 0x1e, 
    0x66, 0xe8, 0x80, 0x1e, 
    0x66, 0xe8, 0x80, 0x1e, 
    0xa6, 0x28, 0x40, 0x9e, 
// tile: 72
    0xa0, 0x18, 0x40, 0x3f, 
    0xb8, 0x0c, 0x48, 0x37, 
    0xb8, 0x0c, 0x48, 0x37, 
    0xa0, 0x18, 0x40, 0x3f, 
    0xa0, 0x10, 0x40, 0x3f, 
    0xa0, 0x10, 0x40, 0x3f, 
    0x90, 0x18, 0x70, 0x0f, 
    0x6b, 0x0c, 0x1b, 0x07, 
// tile: 73
    0x29, 0x0e, 0x19, 0x07, 
    0x14, 0x07, 0x0c, 0x03, 
    0x09, 0x01, 0x07, 0x00, 
    0x06, 0x00, 0x01, 0x00, 
    0x02, 0x00, 0x01, 0x00, 
    0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 74
    0x60, 0x7e, 0x1f, 0x80, 
    0x60, 0x7f, 0x1f, 0x80, 
    0x60, 0x6f, 0x7f, 0x80, 
    0x30, 0x37, 0x3f, 0xc0, 
    0x18, 0x1b, 0x1f, 0xe0, 
    0x6f, 0x0f, 0x6c, 0xf0, 
    0x67, 0x07, 0x64, 0xf8, 
    0x80, 0x00, 0x80, 0xff, 
// tile: 75
    0x80, 0x01, 0x80, 0xff, 
    0x01, 0x03, 0x01, 0xfe, 
    0x01, 0xfe, 0x00, 0xff, 
    0xff, 0x00, 0x00, 0xff, 
    0x00, 0x00, 0xff, 0x00, 
    0xff, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 76
    0xfd, 0xfc, 0x02, 0x01, 
    0x78, 0x7b, 0x87, 0x00, 
    0x10, 0x97, 0xef, 0x00, 
    0x60, 0x9e, 0x9f, 0x60, 
    0x61, 0x9d, 0x9f, 0x60, 
    0x9e, 0x9f, 0x62, 0x01, 
    0xfe, 0xfe, 0x02, 0x01, 
    0x00, 0x00, 0x00, 0xff, 
// tile: 77
    0x00, 0x80, 0x00, 0xff, 
    0x80, 0xc1, 0x80, 0x7f, 
    0x81, 0x7f, 0x01, 0xfe, 
    0xe0, 0x1f, 0x1f, 0xe0, 
    0x00, 0x00, 0xff, 0x00, 
    0xff, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 78
    0xa6, 0x28, 0x40, 0x9e, 
    0x60, 0xee, 0x86, 0x18, 
    0x60, 0x6e, 0xe6, 0x18, 
    0xc0, 0xce, 0xc6, 0x38, 
    0x80, 0x8e, 0x86, 0x78, 
    0x08, 0x1e, 0x0e, 0xf0, 
    0x98, 0x18, 0x9e, 0xe0, 
    0x56, 0x30, 0x58, 0xe0, 
// tile: 79
    0x04, 0x60, 0x18, 0xe0, 
    0xd8, 0xc0, 0xe0, 0x00, 
    0x90, 0x80, 0xe0, 0x00, 
    0x60, 0x00, 0x80, 0x00, 
    0x40, 0x00, 0x80, 0x00, 
    0x80, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 80
    0x01, 0x00, 0x00, 0x00, 
    0x03, 0x01, 0x01, 0x00, 
    0x06, 0x02, 0x01, 0x01, 
    0x0c, 0x04, 0x07, 0x03, 
    0x19, 0x09, 0x07, 0x07, 
    0x33, 0x12, 0x1f, 0x0f, 
    0x66, 0x34, 0x0e, 0x1f, 
    0xc6, 0x78, 0x46, 0x3f, 
// tile: 81
    0x86, 0x40, 0x26, 0x7f, 
    0x81, 0x40, 0x21, 0x7f, 
    0x81, 0x58, 0x21, 0x7f, 
    0x98, 0x4c, 0x28, 0x77, 
    0x98, 0x4c, 0x28, 0x77, 
    0x81, 0x59, 0x21, 0x7e, 
    0x81, 0x41, 0x20, 0x7e, 
    0x81, 0x41, 0x20, 0x7e, 
// tile: 82
    0xff, 0x00, 0x00, 0x00, 
    0x08, 0xf8, 0x0f, 0xf0, 
    0x07, 0x00, 0xf8, 0xff, 
    0x98, 0xe7, 0x80, 0xff, 
    0x98, 0x3e, 0x98, 0xe7, 
    0x06, 0x1f, 0x06, 0xf9, 
    0x06, 0x0f, 0x06, 0xf9, 
    0x00, 0x06, 0x00, 0xff, 
// tile: 83
    0x00, 0x00, 0x00, 0xff, 
    0x9f, 0x1f, 0x90, 0xe0, 
    0xb1, 0x31, 0xbe, 0xc0, 
    0x6e, 0x61, 0x71, 0x8e, 
    0xde, 0xc1, 0xe1, 0x1e, 
    0x99, 0xa1, 0xe7, 0x1e, 
    0x99, 0xe3, 0x65, 0x1e, 
    0x8f, 0xef, 0x7e, 0x00, 
// tile: 84
    0xfe, 0x00, 0x00, 0x00, 
    0x01, 0x00, 0xfe, 0x00, 
    0xfd, 0x00, 0x02, 0xfc, 
    0x1a, 0xe6, 0x03, 0xfc, 
    0x19, 0x3f, 0x19, 0xe6, 
    0x00, 0x19, 0x00, 0xff, 
    0x01, 0x00, 0x01, 0xff, 
    0x06, 0x00, 0x06, 0xff, 
// tile: 85
    0x06, 0x00, 0x06, 0xff, 
    0xe8, 0xe0, 0x28, 0x1f, 
    0xa0, 0xb0, 0x60, 0x1f, 
    0x58, 0x98, 0xb8, 0x47, 
    0x6c, 0x8c, 0x9c, 0x63, 
    0x06, 0x76, 0xfe, 0x01, 
    0x86, 0xbe, 0x78, 0x01, 
    0xc6, 0xde, 0x38, 0x01, 
// tile: 86
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 
    0x40, 0x00, 0x80, 0x00, 
    0xa0, 0x80, 0xc0, 0x00, 
    0x50, 0xc0, 0x60, 0x80, 
    0x58, 0xc0, 0x60, 0x80, 
    0x24, 0x60, 0x38, 0xc0, 
// tile: 87
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
// tile: 88
    0xc1, 0x51, 0x60, 0x3e, 
    0xa1, 0x31, 0x60, 0x1e, 
    0xa1, 0x11, 0x40, 0x3e, 
    0xa1, 0x11, 0x40, 0x3e, 
    0xa1, 0x11, 0x40, 0x3e, 
    0xa1, 0x11, 0x40, 0x3e, 
    0xa1, 0x11, 0x41, 0x3e, 
    0xa0, 0x10, 0x40, 0x3f, 
// tile: 89
    0x90, 0x18, 0x70, 0x0f, 
    0x6b, 0x0c, 0x1b, 0x07, 
    0x29, 0x0e, 0x19, 0x07, 
    0x14, 0x07, 0x0c, 0x03, 
    0x09, 0x01, 0x07, 0x00, 
    0x06, 0x00, 0x01, 0x00, 
    0x02, 0x00, 0x01, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 90
    0x9f, 0xff, 0x60, 0x00, 
    0x6f, 0x0f, 0x90, 0x60, 
    0x6f, 0x0f, 0x90, 0x60, 
    0x9f, 0xff, 0x60, 0x00, 
    0x8f, 0xef, 0x70, 0x00, 
    0x87, 0xf7, 0x78, 0x00, 
    0x81, 0xb9, 0xfe, 0x00, 
    0xc6, 0xd9, 0xf9, 0x06, 
// tile: 91
    0x66, 0x69, 0x79, 0x86, 
    0xb9, 0x39, 0xb6, 0xc0, 
    0x9f, 0x1f, 0x90, 0xe0, 
    0x00, 0x00, 0x00, 0xff, 
    0x00, 0xff, 0x00, 0xff, 
    0xfe, 0x01, 0x01, 0xfe, 
    0xfe, 0x01, 0x01, 0xfe, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 92
    0xe6, 0xfe, 0x18, 0x01, 
    0xe6, 0xfe, 0x18, 0x01, 
    0xe6, 0xfe, 0x18, 0x01, 
    0xda, 0xc2, 0x24, 0x19, 
    0xda, 0xc2, 0x24, 0x19, 
    0x86, 0xbe, 0x78, 0x01, 
    0x06, 0x76, 0xfe, 0x01, 
    0x0c, 0xec, 0xfc, 0x03, 
// tile: 93
    0x18, 0xd8, 0xf8, 0x07, 
    0xf4, 0xf3, 0x34, 0x0f, 
    0xe1, 0xe7, 0x21, 0x1e, 
    0x02, 0x07, 0x03, 0xfc, 
    0x06, 0xfe, 0x07, 0xf8, 
    0x01, 0xfc, 0xfe, 0x00, 
    0x01, 0xfc, 0xfe, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 94
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x14, 0x20, 0x08, 0xf0, 
    0x04, 0x30, 0x18, 0xe0, 
    0x04, 0x30, 0x18, 0xe0, 
    0x04, 0x30, 0x18, 0xe0, 
    0x04, 0x70, 0x18, 0xe0, 
    0x64, 0xd0, 0x58, 0xa0, 
// tile: 95
    0x64, 0x90, 0x18, 0xe0, 
    0x98, 0xe0, 0xe0, 0x00, 
    0x90, 0x80, 0xe0, 0x00, 
    0x60, 0x00, 0x80, 0x00, 
    0x40, 0x00, 0x80, 0x00, 
    0x80, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
};

const AnimationSpriteBatched evil_eyeFrame0SpriteBatched[] = 
{
    { 4, { -15, -16, 0 } },
    { 4, { -15, 0, 8 } },
    {0},
};

const AnimationSpriteBatched evil_eyeFrame1SpriteBatched[] = 
{
    { 4, { -15, -16, 16 } },
    { 4, { -15, 0, 24 } },
    {0},
};

const AnimationSpriteBatched evil_eyeFrame2SpriteBatched[] = 
{
    { 4, { -15, -15, 32 } },
    { 4, { -15, 1, 40 } },
    {0},
};

const AnimationSpriteBatched evil_eyeFrame3SpriteBatched[] = 
{
    { 4, { -15, -15, 48 } },
    { 4, { -15, 1, 56 } },
    {0},
};

const AnimationSpriteBatched evil_eyeFrame4SpriteBatched[] = 
{
    { 4, { -15, -15, 64 } },
    { 4, { -15, 1, 72 } },
    {0},
};

const AnimationSpriteBatched evil_eyeFrame5SpriteBatched[] = 
{
    { 4, { -15, -15, 80 } },
    { 4, { -15, 1, 88 } },
    {0},
};


const AnimationFrameBatched evil_eyeFrame0 = 
{
    evil_eyeFrame0SpriteBatched,
    8, // frame time
};

const AnimationFrameBatched evil_eyeFrame1 = 
{
    evil_eyeFrame1SpriteBatched,
    8, // frame time
};

const AnimationFrameBatched evil_eyeFrame2 = 
{
    evil_eyeFrame2SpriteBatched,
    8, // frame time
};

const AnimationFrameBatched evil_eyeFrame3 = 
{
    evil_eyeFrame3SpriteBatched,
    8, // frame time
};

const AnimationFrameBatched evil_eyeFrame4 = 
{
    evil_eyeFrame4SpriteBatched,
    8, // frame time
};

const AnimationFrameBatched evil_eyeFrame5 = 
{
    evil_eyeFrame5SpriteBatched,
    8, // frame time
};
const AnimationFrameBatched* const evil_eyeFrames[6] = 
{
    &evil_eyeFrame0,
    &evil_eyeFrame1,
    &evil_eyeFrame2,
    &evil_eyeFrame3,
    &evil_eyeFrame4,
    &evil_eyeFrame5,
};

const AnimationBatched evil_eye = 
{
    BATCHED_ANIMATION_RESOURCE_TYPE, 
    (const AnimationFrameBatched** const)evil_eyeFrames,
    (unsigned char* const)evil_eyeTileData, // start of the sprite data
    48, // the total time of the animation
    6, // number of frames
    32, // width in pixels
    32, // height in pixels
    96, // the total amount of tiles in animation
};
