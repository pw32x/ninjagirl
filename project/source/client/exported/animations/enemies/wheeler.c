#include "wheeler.h"


unsigned char const wheelerTileData[2176] = // 68tiles x 32 bytes
{
// tile: 0
    0x0f, 0x00, 0x0f, 0x00, 
    0x1e, 0x09, 0x16, 0x01, 
    0x3f, 0x16, 0x29, 0x06, 
    0x7f, 0x2f, 0x50, 0x0f, 
    0xff, 0x5f, 0xa0, 0x1f, 
    0xff, 0x40, 0xbf, 0x40, 
    0xf1, 0x0e, 0xf0, 0x0e, 
    0xef, 0x5e, 0xae, 0x5e, 
// tile: 1
    0xef, 0x1e, 0xee, 0x1e, 
    0xef, 0x5e, 0xae, 0x1e, 
    0x77, 0x2f, 0x57, 0x2f, 
    0x3f, 0x17, 0x2f, 0x17, 
    0x1f, 0x00, 0x1f, 0x00, 
    0x3f, 0x1f, 0x20, 0x00, 
    0x77, 0x3a, 0x44, 0x32, 
    0xfa, 0x7d, 0x81, 0x78, 
// tile: 2
    0xf0, 0x00, 0xf0, 0x00, 
    0x08, 0xf0, 0x08, 0xf0, 
    0x04, 0xf8, 0x04, 0xf8, 
    0xbf, 0x40, 0xbf, 0x40, 
    0xff, 0xbe, 0x7f, 0xbe, 
    0xff, 0x00, 0xff, 0x00, 
    0xce, 0x30, 0x02, 0x30, 
    0x7e, 0xa0, 0xa2, 0x24, 
// tile: 3
    0xfa, 0x04, 0x06, 0x80, 
    0x76, 0x88, 0x8a, 0x44, 
    0xac, 0x50, 0x54, 0x28, 
    0xf8, 0x80, 0x88, 0x80, 
    0xf0, 0x00, 0xf0, 0x00, 
    0x80, 0x80, 0x00, 0x00, 
    0xce, 0x00, 0x00, 0x00, 
    0x31, 0xce, 0xce, 0x42, 
// tile: 4
    0x1f, 0x01, 0x00, 0x01, 
    0x2f, 0x1e, 0x0e, 0x1e, 
    0x23, 0x1f, 0x03, 0x1f, 
    0x1c, 0x03, 0x00, 0x03, 
    0x1f, 0x00, 0x1c, 0x00, 
    0x1f, 0x0c, 0x13, 0x0c, 
    0x0f, 0x07, 0x08, 0x07, 
    0x3f, 0x39, 0x06, 0x01, 
// tile: 5
    0x7b, 0x7c, 0x3b, 0x00, 
    0xcd, 0xf3, 0x41, 0x30, 
    0x9e, 0xe5, 0x08, 0x65, 
    0x9e, 0xe5, 0x08, 0x65, 
    0xde, 0xe1, 0x4c, 0x61, 
    0xec, 0xf3, 0x60, 0x73, 
    0x70, 0x7f, 0x30, 0x3f, 
    0x3f, 0x3f, 0x00, 0x00, 
// tile: 6
    0xe4, 0xdb, 0x1b, 0xc3, 
    0xef, 0x10, 0x54, 0x00, 
    0xcf, 0xb0, 0xb6, 0x80, 
    0xcf, 0xb0, 0xb6, 0x80, 
    0xef, 0x10, 0x54, 0x00, 
    0xe4, 0x1b, 0xdb, 0x03, 
    0xf1, 0x8e, 0x6e, 0x82, 
    0xfe, 0xc0, 0x20, 0xc0, 
// tile: 7
    0xe0, 0x20, 0xc0, 0x00, 
    0xf0, 0xf0, 0xe0, 0x00, 
    0x70, 0xf0, 0x20, 0xa0, 
    0x70, 0xf0, 0x20, 0xa0, 
    0x50, 0xf0, 0x00, 0xa0, 
    0x50, 0xf0, 0x00, 0xa0, 
    0xa0, 0xe0, 0x00, 0x40, 
    0xc0, 0xc0, 0x00, 0x00, 
// tile: 8
    0xa4, 0x58, 0x58, 0x18, 
    0x5c, 0x80, 0x80, 0x00, 
    0x40, 0x80, 0x80, 0x00, 
    0x40, 0x80, 0x80, 0x00, 
    0x5c, 0x80, 0x80, 0x00, 
    0xa4, 0x58, 0x58, 0x18, 
    0x88, 0x70, 0x70, 0x10, 
    0x70, 0x00, 0x00, 0x00, 
// tile: 9
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 10
    0x1f, 0x01, 0x00, 0x01, 
    0x2f, 0x1e, 0x0e, 0x1e, 
    0x23, 0x1f, 0x03, 0x1f, 
    0x1c, 0x03, 0x00, 0x03, 
    0x1f, 0x00, 0x1c, 0x00, 
    0x1f, 0x0c, 0x13, 0x0c, 
    0x3f, 0x37, 0x08, 0x07, 
    0x7f, 0x79, 0x36, 0x01, 
// tile: 11
    0xcb, 0xf4, 0x43, 0x30, 
    0x9e, 0xe5, 0x08, 0x65, 
    0xde, 0xe5, 0x48, 0x65, 
    0xde, 0xe1, 0x4c, 0x61, 
    0xcc, 0xf3, 0x40, 0x73, 
    0x60, 0x7f, 0x20, 0x3f, 
    0x3f, 0x3f, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 12
    0xf1, 0xce, 0x0e, 0xc2, 
    0xe4, 0x1b, 0x5b, 0x03, 
    0xef, 0x90, 0x94, 0x80, 
    0xe4, 0x9b, 0x9b, 0x83, 
    0xf1, 0x0e, 0x6e, 0x02, 
    0xfe, 0x00, 0xe0, 0x00, 
    0xf0, 0xc0, 0x30, 0xc0, 
    0xe0, 0xc0, 0x20, 0xc0, 
// tile: 13
    0xf0, 0x30, 0xe0, 0x00, 
    0x50, 0xf0, 0x00, 0xa0, 
    0x70, 0xf0, 0x20, 0xa0, 
    0x70, 0xf0, 0x20, 0xa0, 
    0x50, 0xf0, 0x00, 0xa0, 
    0xa0, 0xe0, 0x00, 0x40, 
    0xc0, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 14
    0x8c, 0x70, 0x70, 0x10, 
    0xa4, 0x58, 0x58, 0x18, 
    0x5c, 0x80, 0x80, 0x00, 
    0xa0, 0x58, 0x58, 0x18, 
    0x88, 0x70, 0x70, 0x10, 
    0x70, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 15
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 16
    0x0f, 0x00, 0x0f, 0x00, 
    0x10, 0x0f, 0x10, 0x0f, 
    0x20, 0x1f, 0x20, 0x1f, 
    0xfd, 0x02, 0xfd, 0x02, 
    0xff, 0x7d, 0xfe, 0x7d, 
    0xff, 0x00, 0xff, 0x00, 
    0x73, 0x0c, 0x40, 0x0c, 
    0x7e, 0x05, 0x45, 0x24, 
// tile: 17
    0x5f, 0x20, 0x60, 0x01, 
    0x6e, 0x11, 0x51, 0x22, 
    0x35, 0x0a, 0x2a, 0x14, 
    0x1f, 0x01, 0x11, 0x01, 
    0x0f, 0x00, 0x0f, 0x00, 
    0x01, 0x01, 0x00, 0x00, 
    0x73, 0x00, 0x00, 0x00, 
    0x8c, 0x73, 0x73, 0x42, 
// tile: 18
    0xf0, 0x00, 0xf0, 0x00, 
    0x78, 0x90, 0x68, 0x80, 
    0xfc, 0x68, 0x94, 0x60, 
    0xfe, 0xf4, 0x0a, 0xf0, 
    0xff, 0xfa, 0x05, 0xf8, 
    0xff, 0x02, 0xfd, 0x02, 
    0x8f, 0x70, 0x0f, 0x70, 
    0xf7, 0x7a, 0x75, 0x7a, 
// tile: 19
    0xf7, 0x78, 0x77, 0x78, 
    0xf7, 0x7a, 0x75, 0x78, 
    0xee, 0xf4, 0xea, 0xf4, 
    0xfc, 0xe8, 0xf4, 0xe8, 
    0xf8, 0x00, 0xf8, 0x00, 
    0xfc, 0xf8, 0x04, 0x00, 
    0xee, 0x5c, 0x22, 0x4c, 
    0x5f, 0xbe, 0x81, 0x1e, 
// tile: 20
    0x94, 0x6b, 0x6b, 0x63, 
    0xeb, 0x04, 0x04, 0x00, 
    0x0b, 0x04, 0x05, 0x00, 
    0x0b, 0x04, 0x05, 0x00, 
    0xeb, 0x04, 0x04, 0x00, 
    0x94, 0x6b, 0x6b, 0x63, 
    0x46, 0x39, 0x39, 0x21, 
    0x39, 0x00, 0x00, 0x00, 
// tile: 21
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 22
    0x9f, 0x6e, 0x60, 0x0e, 
    0xdf, 0x21, 0xa9, 0x01, 
    0xcf, 0x37, 0xb7, 0x07, 
    0xcc, 0x37, 0xb4, 0x07, 
    0xdf, 0x20, 0xa8, 0x00, 
    0x9f, 0x60, 0x6f, 0x00, 
    0x3f, 0xc7, 0xd8, 0x07, 
    0xff, 0x0e, 0x11, 0x0e, 
// tile: 23
    0x1f, 0x10, 0x0f, 0x00, 
    0x3e, 0x3f, 0x16, 0x00, 
    0x39, 0x3e, 0x10, 0x16, 
    0x39, 0x3e, 0x10, 0x16, 
    0x29, 0x3e, 0x00, 0x16, 
    0x28, 0x3f, 0x00, 0x17, 
    0x14, 0x1f, 0x00, 0x0b, 
    0x0f, 0x0f, 0x00, 0x00, 
// tile: 24
    0xe0, 0x00, 0x00, 0x00, 
    0xd0, 0xe0, 0xc0, 0xe0, 
    0x10, 0xe0, 0x00, 0xe0, 
    0xe0, 0x00, 0x00, 0x00, 
    0xe0, 0x00, 0xe0, 0x00, 
    0xe0, 0xc0, 0x20, 0xc0, 
    0xc0, 0x80, 0x40, 0x80, 
    0xf0, 0x70, 0x80, 0x00, 
// tile: 25
    0x78, 0xf8, 0x70, 0x00, 
    0xcc, 0x3c, 0x08, 0x30, 
    0xe4, 0x9c, 0x40, 0x98, 
    0xe4, 0x9c, 0x40, 0x98, 
    0xec, 0x1c, 0xc8, 0x18, 
    0xdc, 0x3c, 0x18, 0x38, 
    0x38, 0xf8, 0x30, 0xf0, 
    0xf0, 0xf0, 0x00, 0x00, 
// tile: 26
    0xc6, 0x39, 0x39, 0x21, 
    0x94, 0x6b, 0x6b, 0x63, 
    0xeb, 0x04, 0x04, 0x00, 
    0x14, 0x6b, 0x6b, 0x63, 
    0x46, 0x39, 0x39, 0x21, 
    0x39, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 27
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 28
    0x3f, 0xce, 0xc0, 0x0e, 
    0x9f, 0x61, 0x69, 0x01, 
    0xdf, 0x27, 0xa7, 0x07, 
    0x9c, 0x67, 0x64, 0x07, 
    0x3f, 0xc0, 0xd8, 0x00, 
    0xff, 0x00, 0x1f, 0x00, 
    0x3f, 0x07, 0x38, 0x07, 
    0x1f, 0x0e, 0x11, 0x0e, 
// tile: 29
    0x3f, 0x30, 0x1f, 0x00, 
    0x29, 0x3e, 0x00, 0x16, 
    0x39, 0x3e, 0x10, 0x16, 
    0x39, 0x3e, 0x10, 0x16, 
    0x28, 0x3f, 0x00, 0x17, 
    0x14, 0x1f, 0x00, 0x0b, 
    0x0f, 0x0f, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 30
    0xe0, 0x00, 0x00, 0x00, 
    0xd0, 0xe0, 0xc0, 0xe0, 
    0x10, 0xe0, 0x00, 0xe0, 
    0xe0, 0x00, 0x00, 0x00, 
    0xe0, 0x00, 0xe0, 0x00, 
    0xe0, 0xc0, 0x20, 0xc0, 
    0xf0, 0xb0, 0x40, 0x80, 
    0xf8, 0x78, 0xb0, 0x00, 
// tile: 31
    0x4c, 0xbc, 0x08, 0x30, 
    0xe4, 0x9c, 0x40, 0x98, 
    0xec, 0x9c, 0x48, 0x98, 
    0xec, 0x1c, 0xc8, 0x18, 
    0xcc, 0x3c, 0x08, 0x38, 
    0x18, 0xf8, 0x10, 0xf0, 
    0xf0, 0xf0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 32
    0x00, 0x00, 0x00, 0x00, 
    0x03, 0x01, 0x02, 0x00, 
    0x03, 0x00, 0x03, 0x00, 
    0x07, 0x03, 0x04, 0x03, 
    0x07, 0x00, 0x07, 0x00, 
    0x07, 0x01, 0x07, 0x01, 
    0x07, 0x01, 0x07, 0x01, 
    0x07, 0x03, 0x07, 0x03, 
// tile: 33
    0x57, 0x2b, 0x2f, 0x2b, 
    0x97, 0x6b, 0x6f, 0x6b, 
    0xbf, 0x43, 0x57, 0x03, 
    0x93, 0x6d, 0x6f, 0x01, 
    0x45, 0x38, 0x39, 0x00, 
    0x2c, 0x18, 0x08, 0x18, 
    0x2f, 0x18, 0x08, 0x18, 
    0x17, 0x0f, 0x07, 0x0f, 
// tile: 34
    0xff, 0x00, 0xff, 0x00, 
    0xff, 0x00, 0xff, 0x00, 
    0xff, 0x7e, 0xff, 0x7e, 
    0xff, 0x00, 0xff, 0x00, 
    0xff, 0xc3, 0xc3, 0xc3, 
    0xd7, 0xa9, 0xa9, 0x95, 
    0xbb, 0x44, 0x44, 0x22, 
    0xfd, 0x02, 0x02, 0x40, 
// tile: 35
    0xbf, 0x58, 0x58, 0x1a, 
    0xfd, 0x02, 0x02, 0x40, 
    0xbb, 0x44, 0x44, 0x22, 
    0xd7, 0xa9, 0xa9, 0x95, 
    0xff, 0xc3, 0xc3, 0xc3, 
    0xff, 0x00, 0xff, 0x00, 
    0xff, 0xff, 0x00, 0x00, 
    0xff, 0x7e, 0x00, 0x7e, 
// tile: 36
    0x00, 0x00, 0x00, 0x00, 
    0xc0, 0x80, 0x40, 0x00, 
    0xc0, 0x00, 0xc0, 0x00, 
    0xe0, 0xc0, 0x20, 0xc0, 
    0xe0, 0x00, 0xe0, 0x00, 
    0xe0, 0x80, 0xe0, 0x80, 
    0xe0, 0x80, 0xe0, 0x80, 
    0xe0, 0xc0, 0xe0, 0xc0, 
// tile: 37
    0xea, 0xd4, 0xf4, 0xd4, 
    0xe9, 0xd6, 0xf6, 0xd6, 
    0xfd, 0xc2, 0xea, 0xc0, 
    0xc9, 0xb6, 0xf6, 0x80, 
    0xa2, 0x1c, 0x9c, 0x00, 
    0x34, 0x18, 0x10, 0x18, 
    0xf4, 0x18, 0x10, 0x18, 
    0xe8, 0xf0, 0xe0, 0xf0, 
// tile: 38
    0xc7, 0x3b, 0x00, 0x3b, 
    0x1f, 0x07, 0x00, 0x07, 
    0x1f, 0x0f, 0x10, 0x0f, 
    0x1f, 0x0f, 0x10, 0x0f, 
    0x1f, 0x0f, 0x10, 0x0f, 
    0x1f, 0x0f, 0x10, 0x0f, 
    0x1f, 0x0f, 0x10, 0x0f, 
    0x0f, 0x07, 0x08, 0x07, 
// tile: 39
    0x07, 0x00, 0x07, 0x00, 
    0x01, 0x01, 0x00, 0x00, 
    0x02, 0x03, 0x00, 0x01, 
    0x02, 0x03, 0x00, 0x01, 
    0x02, 0x03, 0x00, 0x01, 
    0x02, 0x03, 0x00, 0x01, 
    0x02, 0x03, 0x00, 0x01, 
    0x01, 0x01, 0x00, 0x00, 
// tile: 40
    0xf8, 0xf7, 0x00, 0xf7, 
    0xfe, 0xf8, 0x00, 0xf8, 
    0xfe, 0xfc, 0x02, 0xfc, 
    0xfe, 0xfc, 0x02, 0xfc, 
    0xfe, 0xfc, 0x02, 0xfc, 
    0xfe, 0xfc, 0x02, 0xfc, 
    0xfe, 0xfc, 0x02, 0xfc, 
    0xfc, 0xf8, 0x04, 0xf8, 
// tile: 41
    0xf8, 0x00, 0xf8, 0x00, 
    0x20, 0xe0, 0x00, 0xc0, 
    0x10, 0xf0, 0x00, 0xe0, 
    0x10, 0xf0, 0x00, 0xe0, 
    0x10, 0xf0, 0x00, 0xe0, 
    0x10, 0xf0, 0x00, 0xe0, 
    0x10, 0xf0, 0x00, 0xe0, 
    0xe0, 0xe0, 0x00, 0x00, 
// tile: 42
    0xc0, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 43
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 44
    0x0f, 0x00, 0x0f, 0x00, 
    0x1e, 0x09, 0x16, 0x01, 
    0x3f, 0x16, 0x29, 0x06, 
    0x7f, 0x2f, 0x50, 0x0f, 
    0xff, 0x5f, 0xa0, 0x1f, 
    0xff, 0x40, 0xbf, 0x40, 
    0xf1, 0x0e, 0xf0, 0x0e, 
    0xef, 0x5e, 0xae, 0x5e, 
// tile: 45
    0xef, 0x1e, 0xee, 0x1e, 
    0xef, 0x5e, 0xae, 0x1e, 
    0x77, 0x2f, 0x57, 0x2f, 
    0x3f, 0x17, 0x2f, 0x17, 
    0x1f, 0x00, 0x1f, 0x00, 
    0x0f, 0x0f, 0x00, 0x00, 
    0x1f, 0x0f, 0x10, 0x0f, 
    0x3f, 0x1f, 0x20, 0x1f, 
// tile: 46
    0xf0, 0x00, 0xf0, 0x00, 
    0x08, 0xf0, 0x08, 0xf0, 
    0x04, 0xf8, 0x04, 0xf8, 
    0xbf, 0x40, 0xbf, 0x40, 
    0xff, 0xbe, 0x7f, 0xbe, 
    0xff, 0x00, 0xff, 0x00, 
    0xce, 0x30, 0x02, 0x30, 
    0x7e, 0xa0, 0xa2, 0x24, 
// tile: 47
    0xfa, 0x04, 0x06, 0x80, 
    0x76, 0x88, 0x8a, 0x44, 
    0xac, 0x50, 0x54, 0x28, 
    0xf8, 0x80, 0x88, 0x80, 
    0xf0, 0x00, 0xf0, 0x00, 
    0xf0, 0xf0, 0x00, 0x00, 
    0xf8, 0xf0, 0x08, 0xf0, 
    0xfc, 0xf8, 0x04, 0xf8, 
// tile: 48
    0x7f, 0x1f, 0x00, 0x1f, 
    0xbf, 0x6f, 0x20, 0x6f, 
    0xbf, 0x68, 0x24, 0x68, 
    0x3c, 0x63, 0x23, 0x60, 
    0x59, 0x3e, 0x1e, 0x38, 
    0x63, 0x1c, 0x05, 0x18, 
    0x39, 0x06, 0x26, 0x00, 
    0x1c, 0x03, 0x1b, 0x00, 
// tile: 49
    0x1f, 0x18, 0x04, 0x08, 
    0x33, 0x3c, 0x10, 0x0c, 
    0x27, 0x39, 0x02, 0x19, 
    0x27, 0x39, 0x02, 0x19, 
    0x37, 0x38, 0x13, 0x18, 
    0x3b, 0x3c, 0x18, 0x1c, 
    0x1c, 0x1f, 0x0c, 0x0f, 
    0x0f, 0x0f, 0x00, 0x00, 
// tile: 50
    0xfc, 0xf8, 0x04, 0xf8, 
    0xfc, 0xf8, 0x04, 0xf8, 
    0xfc, 0x40, 0x20, 0x40, 
    0x62, 0x9c, 0x9c, 0x84, 
    0x29, 0xd6, 0xd6, 0xc6, 
    0xdf, 0x20, 0x28, 0x00, 
    0x29, 0xd6, 0xd6, 0xc6, 
    0x62, 0x9c, 0x9c, 0x84, 
// tile: 51
    0xfc, 0x00, 0x60, 0x00, 
    0x1c, 0xfc, 0x08, 0x60, 
    0x9c, 0x7c, 0x08, 0x68, 
    0x9c, 0x7c, 0x08, 0x68, 
    0x94, 0x7c, 0x00, 0x68, 
    0x14, 0xfc, 0x00, 0xe8, 
    0x28, 0xf8, 0x00, 0xd0, 
    0xf0, 0xf0, 0x00, 0x00, 
// tile: 52
    0x0f, 0x00, 0x0f, 0x00, 
    0x1e, 0x09, 0x16, 0x01, 
    0x3f, 0x16, 0x29, 0x06, 
    0x7f, 0x2f, 0x50, 0x0f, 
    0xff, 0x5f, 0xa0, 0x1f, 
    0xff, 0x40, 0xbf, 0x40, 
    0xfc, 0x03, 0xf0, 0x03, 
    0xf7, 0x49, 0xa9, 0x41, 
// tile: 53
    0xff, 0x00, 0xe0, 0x08, 
    0xf7, 0x48, 0xa8, 0x04, 
    0x7a, 0x25, 0x55, 0x22, 
    0x3f, 0x10, 0x28, 0x10, 
    0x1f, 0x00, 0x1f, 0x00, 
    0x0f, 0x0f, 0x00, 0x00, 
    0x1f, 0x0f, 0x10, 0x0f, 
    0x3f, 0x1f, 0x20, 0x1f, 
// tile: 54
    0xf0, 0x00, 0xf0, 0x00, 
    0x08, 0xf0, 0x08, 0xf0, 
    0x04, 0xf8, 0x04, 0xf8, 
    0xbf, 0x40, 0xbf, 0x40, 
    0xff, 0xbe, 0x7f, 0xbe, 
    0xff, 0x00, 0xff, 0x00, 
    0xc2, 0x3c, 0x02, 0x3c, 
    0xfe, 0x1c, 0x1e, 0x5c, 
// tile: 55
    0xbe, 0x5c, 0x5e, 0x1c, 
    0x7e, 0x9c, 0x9e, 0x5c, 
    0xfc, 0x38, 0x3c, 0xb8, 
    0xf8, 0x70, 0x78, 0x70, 
    0xf0, 0x00, 0xf0, 0x00, 
    0xf0, 0xf0, 0x00, 0x00, 
    0xf8, 0xf0, 0x08, 0xf0, 
    0xfc, 0xf8, 0x04, 0xf8, 
// tile: 56
    0x1f, 0x00, 0x1f, 0x00, 
    0x3f, 0x17, 0x2f, 0x17, 
    0x77, 0x2f, 0x57, 0x2f, 
    0xef, 0x5e, 0xae, 0x1e, 
    0xef, 0x1e, 0xee, 0x1e, 
    0xef, 0x5e, 0xae, 0x5e, 
    0xf1, 0x0e, 0xf0, 0x0e, 
    0xff, 0x40, 0xbf, 0x40, 
// tile: 57
    0xff, 0x5f, 0xa0, 0x1f, 
    0x7f, 0x2f, 0x50, 0x0f, 
    0x3f, 0x16, 0x29, 0x06, 
    0x1e, 0x09, 0x16, 0x01, 
    0x0f, 0x00, 0x0f, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 58
    0xf0, 0x00, 0xf0, 0x00, 
    0xf8, 0x80, 0x88, 0x80, 
    0xac, 0x50, 0x54, 0x28, 
    0x76, 0x88, 0x8a, 0x44, 
    0xfa, 0x04, 0x06, 0x80, 
    0x7e, 0xa0, 0xa2, 0x24, 
    0xce, 0x30, 0x02, 0x30, 
    0xff, 0x00, 0xff, 0x00, 
// tile: 59
    0xff, 0xbe, 0x7f, 0xbe, 
    0xbf, 0x40, 0xbf, 0x40, 
    0x04, 0xf8, 0x04, 0xf8, 
    0x08, 0xf0, 0x08, 0xf0, 
    0xf0, 0x00, 0xf0, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 60
    0x0c, 0x00, 0x00, 0x00, 
    0x23, 0x1c, 0x1c, 0x04, 
    0x49, 0x36, 0x36, 0x06, 
    0x56, 0x20, 0x20, 0x00, 
    0x90, 0x60, 0x60, 0x00, 
    0x90, 0x60, 0x60, 0x00, 
    0x56, 0x20, 0x20, 0x00, 
    0x49, 0x36, 0x36, 0x06, 
// tile: 61
    0x23, 0x1c, 0x1c, 0x04, 
    0x3c, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 62
    0x30, 0x00, 0x00, 0x00, 
    0xc4, 0x38, 0x38, 0x20, 
    0x92, 0x6c, 0x6c, 0x60, 
    0x6a, 0x04, 0x04, 0x00, 
    0x09, 0x06, 0x06, 0x00, 
    0x09, 0x06, 0x06, 0x00, 
    0x6a, 0x04, 0x04, 0x00, 
    0x92, 0x6c, 0x6c, 0x60, 
// tile: 63
    0xc4, 0x38, 0x38, 0x20, 
    0x3c, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 64
    0x3f, 0x3f, 0x00, 0x00, 
    0x40, 0x7f, 0x00, 0x3f, 
    0x8c, 0xf3, 0x00, 0x73, 
    0x9e, 0xe5, 0x08, 0x65, 
    0x9e, 0xe5, 0x08, 0x65, 
    0xde, 0xe1, 0x4c, 0x61, 
    0xec, 0xf3, 0x60, 0x73, 
    0x70, 0x7f, 0x30, 0x3f, 
// tile: 65
    0x3f, 0x3f, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 66
    0xc0, 0xc0, 0x00, 0x00, 
    0xa0, 0xe0, 0x00, 0x40, 
    0x50, 0xf0, 0x00, 0xa0, 
    0x70, 0xf0, 0x20, 0xa0, 
    0x70, 0xf0, 0x20, 0xa0, 
    0x50, 0xf0, 0x00, 0xa0, 
    0x50, 0xf0, 0x00, 0xa0, 
    0xa0, 0xe0, 0x00, 0x40, 
// tile: 67
    0xc0, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
};

const s8 wheelerFrame0MetaSprites[] = 
{
    -5, -16, 0,
    3, -16, 2,
    -10, 0, 4,
    -2, 0, 6,
    6, 0, 8,
    (s8)0x80 // end marker
};

const s8 wheelerFrame1MetaSprites[] = 
{
    -5, -15, 0,
    3, -15, 2,
    -10, 1, 10,
    -2, 1, 12,
    6, 1, 14,
    (s8)0x80 // end marker
};

const s8 wheelerFrame2MetaSprites[] = 
{
    -11, -16, 16,
    -3, -16, 18,
    -12, 0, 20,
    -4, 0, 22,
    4, 0, 24,
    (s8)0x80 // end marker
};

const s8 wheelerFrame3MetaSprites[] = 
{
    -11, -15, 16,
    -3, -15, 18,
    -12, 1, 26,
    -4, 1, 28,
    4, 1, 30,
    (s8)0x80 // end marker
};

const s8 wheelerFrame4MetaSprites[] = 
{
    -12, -16, 32,
    -4, -16, 34,
    4, -16, 36,
    -9, 0, 38,
    -1, 0, 40,
    7, 0, 42,
    (s8)0x80 // end marker
};

const s8 wheelerFrame5MetaSprites[] = 
{
    -8, -16, 44,
    0, -16, 46,
    -8, 0, 48,
    0, 0, 50,
    (s8)0x80 // end marker
};

const s8 wheelerFrame6MetaSprites[] = 
{
    -8, -16, 52,
    0, -16, 54,
    -8, 0, 48,
    0, 0, 50,
    (s8)0x80 // end marker
};

const s8 wheelerFrame7MetaSprites[] = 
{
    -8, -7, 56,
    0, -7, 58,
    (s8)0x80 // end marker
};

const s8 wheelerFrame8MetaSprites[] = 
{
    -4, -5, 60,
    (s8)0x80 // end marker
};

const s8 wheelerFrame9MetaSprites[] = 
{
    -4, -5, 62,
    (s8)0x80 // end marker
};

const s8 wheelerFrame10MetaSprites[] = 
{
    -6, -4, 64,
    2, -4, 66,
    (s8)0x80 // end marker
};

extern const MetaSpriteAnimationFrame wheelerFrame0;
extern const MetaSpriteAnimationFrame wheelerFrame1;
extern const MetaSpriteAnimationFrame wheelerFrame2;
extern const MetaSpriteAnimationFrame wheelerFrame3;
extern const MetaSpriteAnimationFrame wheelerFrame4;
extern const MetaSpriteAnimationFrame wheelerFrame5;
extern const MetaSpriteAnimationFrame wheelerFrame6;
extern const MetaSpriteAnimationFrame wheelerFrame7;
extern const MetaSpriteAnimationFrame wheelerFrame8;
extern const MetaSpriteAnimationFrame wheelerFrame9;
extern const MetaSpriteAnimationFrame wheelerFrame10;


const MetaSpriteAnimationFrame wheelerFrame0 = 
{
    wheelerFrame0MetaSprites,
    6, // frame time
    &wheelerFrame1, // next frame
};

const MetaSpriteAnimationFrame wheelerFrame1 = 
{
    wheelerFrame1MetaSprites,
    6, // frame time
    &wheelerFrame0, // next frame
};

const MetaSpriteAnimationFrame wheelerFrame2 = 
{
    wheelerFrame2MetaSprites,
    6, // frame time
    &wheelerFrame3, // next frame
};

const MetaSpriteAnimationFrame wheelerFrame3 = 
{
    wheelerFrame3MetaSprites,
    6, // frame time
    &wheelerFrame2, // next frame
};

const MetaSpriteAnimationFrame wheelerFrame4 = 
{
    wheelerFrame4MetaSprites,
    29, // frame time
    &wheelerFrame4, // next frame
};

const MetaSpriteAnimationFrame wheelerFrame5 = 
{
    wheelerFrame5MetaSprites,
    59, // frame time
    &wheelerFrame6, // next frame
};

const MetaSpriteAnimationFrame wheelerFrame6 = 
{
    wheelerFrame6MetaSprites,
    59, // frame time
    &wheelerFrame5, // next frame
};

const MetaSpriteAnimationFrame wheelerFrame7 = 
{
    wheelerFrame7MetaSprites,
    6, // frame time
    &wheelerFrame7, // next frame
};

const MetaSpriteAnimationFrame wheelerFrame8 = 
{
    wheelerFrame8MetaSprites,
    6, // frame time
    &wheelerFrame8, // next frame
};

const MetaSpriteAnimationFrame wheelerFrame9 = 
{
    wheelerFrame9MetaSprites,
    6, // frame time
    &wheelerFrame9, // next frame
};

const MetaSpriteAnimationFrame wheelerFrame10 = 
{
    wheelerFrame10MetaSprites,
    6, // frame time
    &wheelerFrame10, // next frame
};
const MetaSpriteAnimationFrame* const wheelerFrames[11] = 
{
    &wheelerFrame0,
    &wheelerFrame1,
    &wheelerFrame2,
    &wheelerFrame3,
    &wheelerFrame4,
    &wheelerFrame5,
    &wheelerFrame6,
    &wheelerFrame7,
    &wheelerFrame8,
    &wheelerFrame9,
    &wheelerFrame10,
};

u8 wheelerVdpLocation;

const MetaSpriteAnimation wheeler = 
{
    METASPRITE_ANIMATION_RESOURCE_TYPE, 
    (const MetaSpriteAnimationFrame** const)wheelerFrames,
    (unsigned char* const)wheelerTileData, // start of the sprite data
    11, // number of frames
    24, // width in pixels
    32, // height in pixels
    68, // the total amount of tiles in animation
    12, // the max amount of sprite tiles in a frame
    &wheelerVdpLocation,
};
