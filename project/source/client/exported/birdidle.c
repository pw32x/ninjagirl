#include "birdidle.h"


unsigned char const birdidleTileData[1600] = // 50tiles x 32 bytes
{
// tile: 0
    0x00, 0x3f, 0x00, 0x00, 
    0x09, 0x82, 0x09, 0x7d, 
    0x1c, 0x41, 0x1c, 0x3e, 
    0x3f, 0x80, 0x3f, 0x7f, 
    0x1f, 0x40, 0x1f, 0x3f, 
    0x02, 0x5d, 0x02, 0x22, 
    0x1f, 0x40, 0x1f, 0x3f, 
    0x1b, 0x44, 0x1b, 0x3b, 
// tile: 1
    0x1b, 0x44, 0x1b, 0x3b, 
    0x1f, 0x40, 0x1f, 0x3f, 
    0x1e, 0x41, 0x1f, 0x3f, 
    0x1f, 0x40, 0x1e, 0x3f, 
    0x1f, 0x40, 0x1e, 0x3f, 
    0x0f, 0x40, 0x0f, 0x3f, 
    0x1f, 0x40, 0x1f, 0x3f, 
    0x1e, 0x40, 0x1e, 0x3f, 
// tile: 2
    0x00, 0x80, 0x00, 0x00, 
    0x80, 0xc0, 0x80, 0x80, 
    0x80, 0x40, 0x80, 0x80, 
    0xc0, 0x60, 0xc0, 0xc0, 
    0xc0, 0x20, 0xc0, 0xc0, 
    0x00, 0xe0, 0x00, 0x00, 
    0xc0, 0x20, 0xc0, 0xc0, 
    0x40, 0xa0, 0x40, 0x40, 
// tile: 3
    0x40, 0xa0, 0x40, 0x40, 
    0xc0, 0x20, 0xc0, 0xc0, 
    0xc0, 0x20, 0x00, 0xc0, 
    0xe0, 0x10, 0x00, 0xe0, 
    0xc0, 0x20, 0x00, 0xc0, 
    0xc0, 0x20, 0xc0, 0xc0, 
    0x40, 0x60, 0x40, 0xc0, 
    0x40, 0x60, 0x40, 0xc0, 
// tile: 4
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x01, 0x00, 0x00, 
    0x00, 0x02, 0x00, 0x01, 
// tile: 5
    0x01, 0x04, 0x01, 0x03, 
    0x03, 0x08, 0x03, 0x07, 
    0x07, 0x08, 0x07, 0x07, 
    0x07, 0x10, 0x07, 0x0f, 
    0x0f, 0x20, 0x0f, 0x1f, 
    0x07, 0x20, 0x07, 0x1f, 
    0x0b, 0x40, 0x0b, 0x3f, 
    0x17, 0x80, 0x17, 0x7f, 
// tile: 6
    0x07, 0x10, 0x07, 0x0f, 
    0x03, 0x10, 0x03, 0x0f, 
    0x0f, 0x20, 0x0f, 0x1f, 
    0x07, 0x20, 0x07, 0x1f, 
    0x1f, 0x40, 0x1f, 0x3f, 
    0x7b, 0x80, 0x7b, 0x7f, 
    0x7f, 0x00, 0x7f, 0xff, 
    0xfd, 0x02, 0xfd, 0xfd, 
// tile: 7
    0xfd, 0x02, 0xfd, 0xfd, 
    0xfc, 0x03, 0xfc, 0xfc, 
    0xf8, 0x04, 0xf8, 0xfb, 
    0xf9, 0x04, 0xf9, 0xfb, 
    0xf3, 0x08, 0xf3, 0xf7, 
    0xf7, 0x08, 0xf7, 0xf7, 
    0xe7, 0x10, 0xe7, 0xef, 
    0xcf, 0x20, 0xcf, 0xdf, 
// tile: 8
    0xfc, 0x02, 0xfc, 0xfc, 
    0xfc, 0x06, 0xfc, 0xfc, 
    0xfe, 0x01, 0xfe, 0xfe, 
    0xfe, 0x01, 0xfe, 0xfe, 
    0xff, 0x01, 0xff, 0xff, 
    0xff, 0x01, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
// tile: 9
    0xff, 0x00, 0xff, 0xff, 
    0x7e, 0x81, 0x7e, 0x7e, 
    0x00, 0x7e, 0x00, 0x81, 
    0x00, 0x00, 0x00, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
// tile: 10
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x80, 0x00, 0x00, 
    0x00, 0x80, 0x00, 0x00, 
    0x80, 0x00, 0x80, 0x80, 
    0x80, 0xc0, 0x80, 0x80, 
// tile: 11
    0x80, 0x60, 0x80, 0x80, 
    0x00, 0xa0, 0x00, 0x40, 
    0x40, 0x20, 0x40, 0xc0, 
    0xc0, 0x60, 0xc0, 0xc0, 
    0xc0, 0x20, 0xc0, 0xc0, 
    0xc0, 0x20, 0xc0, 0xc0, 
    0xc0, 0x60, 0xc0, 0xc0, 
    0xc0, 0x20, 0xc0, 0xc0, 
// tile: 12
    0x15, 0x80, 0x15, 0x7f, 
    0x0b, 0x80, 0x0b, 0x7f, 
    0x04, 0x41, 0x04, 0x3e, 
    0x00, 0x3e, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 13
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 14
    0xcf, 0x20, 0xcf, 0xdf, 
    0x9f, 0x40, 0x9f, 0xbf, 
    0x3f, 0x80, 0x3f, 0x7f, 
    0x3f, 0x00, 0x3f, 0xff, 
    0x3f, 0x80, 0x3f, 0x7f, 
    0x1f, 0x40, 0x1f, 0x3f, 
    0x00, 0x20, 0x00, 0x1f, 
    0x00, 0x1f, 0x00, 0x00, 
// tile: 15
    0x00, 0x07, 0x07, 0x00, 
    0x03, 0x04, 0x04, 0x03, 
    0x01, 0x06, 0x06, 0x03, 
    0x03, 0x04, 0x04, 0x03, 
    0x01, 0x0e, 0x0e, 0x07, 
    0x02, 0x0c, 0x0c, 0x06, 
    0x06, 0x08, 0x08, 0x06, 
    0x04, 0x18, 0x18, 0x0c, 
// tile: 16
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
    0x00, 0xff, 0x00, 0x00, 
// tile: 17
    0x00, 0x1c, 0x1c, 0x00, 
    0x0c, 0x10, 0x10, 0x0c, 
    0x04, 0x18, 0x18, 0x0c, 
    0x0c, 0x10, 0x10, 0x0c, 
    0x04, 0x18, 0x18, 0x0c, 
    0x02, 0x0c, 0x0c, 0x06, 
    0x06, 0x08, 0x08, 0x06, 
    0x04, 0x18, 0x18, 0x0c, 
// tile: 18
    0xe0, 0x10, 0xe0, 0xe0, 
    0xc0, 0x50, 0xc0, 0xe0, 
    0xc0, 0x20, 0xc0, 0xc0, 
    0x80, 0x20, 0x80, 0xc0, 
    0x80, 0xc0, 0x80, 0x80, 
    0x00, 0x40, 0x00, 0x80, 
    0x00, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 19
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 20
    0x18, 0x60, 0x60, 0x18, 
    0x3c, 0xc0, 0xc0, 0x7c, 
    0x2a, 0xd4, 0xd4, 0x3e, 
    0x16, 0x28, 0x28, 0x16, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
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
    0x18, 0x60, 0x60, 0x38, 
    0x47, 0xb8, 0xb8, 0x7f, 
    0x2a, 0xd5, 0xd5, 0x3f, 
    0x35, 0x0a, 0x0a, 0x35, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 23
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 24
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x80, 
    0x80, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 25
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 26
    0x00, 0x3f, 0x00, 0x00, 
    0x09, 0x82, 0x09, 0x7d, 
    0x1c, 0x41, 0x1c, 0x3e, 
    0x3f, 0x80, 0x3f, 0x7f, 
    0x1f, 0x40, 0x1f, 0x3f, 
    0x02, 0x5d, 0x02, 0x22, 
    0x1f, 0x40, 0x1f, 0x3f, 
    0x1b, 0x44, 0x1b, 0x3b, 
// tile: 27
    0x1b, 0x44, 0x1b, 0x3b, 
    0x1f, 0x40, 0x1f, 0x3f, 
    0x1e, 0x41, 0x1f, 0x3f, 
    0x1f, 0x40, 0x1e, 0x3f, 
    0x1f, 0x40, 0x1e, 0x3f, 
    0x0f, 0x40, 0x0f, 0x3f, 
    0x1f, 0x40, 0x1f, 0x3f, 
    0x1e, 0x40, 0x1e, 0x3f, 
// tile: 28
    0x00, 0x80, 0x00, 0x00, 
    0x80, 0xc0, 0x80, 0x80, 
    0x80, 0x40, 0x80, 0x80, 
    0xc0, 0x60, 0xc0, 0xc0, 
    0xc0, 0x20, 0xc0, 0xc0, 
    0x00, 0xe0, 0x00, 0x00, 
    0xc0, 0x20, 0xc0, 0xc0, 
    0x40, 0xa0, 0x40, 0x40, 
// tile: 29
    0x40, 0xa0, 0x40, 0x40, 
    0xc0, 0x20, 0xc0, 0xc0, 
    0xc0, 0x20, 0x00, 0xc0, 
    0xe0, 0x10, 0x00, 0xe0, 
    0xc0, 0x20, 0x00, 0xc0, 
    0xc0, 0x20, 0xc0, 0xc0, 
    0x40, 0x60, 0x40, 0xc0, 
    0x40, 0x60, 0x40, 0xc0, 
// tile: 30
    0x00, 0x01, 0x00, 0x00, 
    0x00, 0x01, 0x00, 0x00, 
    0x00, 0x02, 0x00, 0x01, 
    0x00, 0x02, 0x00, 0x01, 
    0x01, 0x04, 0x01, 0x03, 
    0x03, 0x08, 0x03, 0x07, 
    0x03, 0x08, 0x03, 0x07, 
    0x03, 0x08, 0x03, 0x07, 
// tile: 31
    0x07, 0x10, 0x07, 0x0f, 
    0x07, 0x10, 0x07, 0x0f, 
    0x07, 0x10, 0x07, 0x0f, 
    0x07, 0x10, 0x07, 0x0f, 
    0x0f, 0x20, 0x0f, 0x1f, 
    0x07, 0x20, 0x07, 0x1f, 
    0x0b, 0x40, 0x0b, 0x3f, 
    0x17, 0x80, 0x17, 0x7f, 
// tile: 32
    0x7f, 0x00, 0x7f, 0xff, 
    0x3f, 0x00, 0x3f, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0x7f, 0x00, 0x7f, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xbf, 0x00, 0xbf, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xdf, 0x20, 0xdf, 0xdf, 
// tile: 33
    0xef, 0x10, 0xef, 0xef, 
    0xe7, 0x18, 0xe7, 0xe7, 
    0xe0, 0x17, 0xe0, 0xe8, 
    0xe0, 0x10, 0xe0, 0xef, 
    0xcf, 0x20, 0xcf, 0xdf, 
    0xdf, 0x20, 0xdf, 0xdf, 
    0xdf, 0x20, 0xdf, 0xdf, 
    0x9f, 0x40, 0x9f, 0xbf, 
// tile: 34
    0xc0, 0x20, 0xc0, 0xc0, 
    0xc0, 0x60, 0xc0, 0xc0, 
    0xe0, 0x10, 0xe0, 0xe0, 
    0xe0, 0x10, 0xe0, 0xe0, 
    0xf0, 0x18, 0xf0, 0xf0, 
    0xf0, 0x1c, 0xf0, 0xf0, 
    0xf8, 0x02, 0xf8, 0xfc, 
    0xf8, 0x0d, 0xf8, 0xfa, 
// tile: 35
    0xf8, 0x06, 0xf8, 0xf9, 
    0xe0, 0x1a, 0xe0, 0xe5, 
    0x04, 0xe2, 0x04, 0x1d, 
    0x0c, 0x07, 0x0c, 0xfc, 
    0xfc, 0x03, 0xfc, 0xfc, 
    0xfc, 0x03, 0xfc, 0xfc, 
    0xfc, 0x06, 0xfc, 0xfc, 
    0xfc, 0x02, 0xfc, 0xfc, 
// tile: 36
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 37
    0x00, 0x80, 0x00, 0x00, 
    0x00, 0x80, 0x00, 0x00, 
    0x00, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 38
    0x15, 0x80, 0x15, 0x7f, 
    0x0a, 0x80, 0x0a, 0x7f, 
    0x04, 0x41, 0x04, 0x3e, 
    0x00, 0x3e, 0x00, 0x01, 
    0x03, 0x08, 0x03, 0x07, 
    0x01, 0x04, 0x01, 0x03, 
    0x00, 0x02, 0x00, 0x01, 
    0x00, 0x01, 0x00, 0x00, 
// tile: 39
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 40
    0x9f, 0x40, 0x9f, 0xbf, 
    0x3f, 0x80, 0x3f, 0x7f, 
    0x7f, 0x00, 0x7f, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0xff, 0x00, 0xff, 0xff, 
    0x00, 0x00, 0x00, 0xff, 
    0x00, 0xff, 0x00, 0x00, 
// tile: 41
    0x00, 0x71, 0x71, 0x00, 
    0x30, 0x41, 0x41, 0x30, 
    0x10, 0x61, 0x61, 0x30, 
    0x30, 0x40, 0x40, 0x30, 
    0x00, 0x70, 0x70, 0x30, 
    0x10, 0x60, 0x60, 0x30, 
    0x30, 0x40, 0x40, 0x30, 
    0x30, 0x40, 0x40, 0x30, 
// tile: 42
    0xfe, 0x01, 0xfe, 0xfe, 
    0xfc, 0x05, 0xfc, 0xfe, 
    0xfc, 0x02, 0xfc, 0xfc, 
    0xf8, 0x02, 0xf8, 0xfc, 
    0xf8, 0x0c, 0xf8, 0xf8, 
    0xf0, 0x04, 0xf0, 0xf8, 
    0x00, 0x08, 0x00, 0xf0, 
    0x00, 0xf0, 0x00, 0x00, 
// tile: 43
    0x00, 0xc0, 0xc0, 0x00, 
    0xc0, 0x00, 0x00, 0xc0, 
    0x40, 0x80, 0x80, 0xc0, 
    0x60, 0x80, 0x80, 0x60, 
    0x20, 0xc0, 0xc0, 0x60, 
    0x20, 0xc0, 0xc0, 0x60, 
    0x60, 0x80, 0x80, 0x60, 
    0x20, 0xc0, 0xc0, 0x60, 
// tile: 44
    0x1c, 0x60, 0x60, 0x1c, 
    0x2a, 0xd4, 0xd4, 0x7e, 
    0x06, 0xf8, 0xf8, 0x06, 
    0x00, 0xf8, 0xf8, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 45
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 46
    0x37, 0x48, 0x48, 0x3f, 
    0x0a, 0x75, 0x75, 0x3f, 
    0x45, 0xba, 0xba, 0x75, 
    0x00, 0xf8, 0xf8, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 47
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 48
    0x00, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x80, 
    0x80, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
// tile: 49
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
};

const AnimationSpriteBatched birdidleFrame0SpriteBatched[] = 
{
    { 2, { 13, 4, 0 } },
    { 4, { 2, 20, 4 } },
    { 4, { 1, 36, 12 } },
    { 3, { 10, 52, 20 } },
    {0},
};

const AnimationSpriteBatched birdidleFrame1SpriteBatched[] = 
{
    { 2, { 11, 4, 26 } },
    { 4, { 4, 20, 30 } },
    { 3, { 3, 36, 38 } },
    { 3, { 10, 52, 44 } },
    {0},
};


const AnimationFrameBatched birdidleFrame0 = 
{
    birdidleFrame0SpriteBatched,
    29, // frame time
};

const AnimationFrameBatched birdidleFrame1 = 
{
    birdidleFrame1SpriteBatched,
    29, // frame time
};
const AnimationFrameBatched* const birdidleFrames[2] = 
{
    &birdidleFrame0,
    &birdidleFrame1,
};

const AnimationBatched birdidle = 
{
    (const AnimationFrameBatched** const)birdidleFrames,
    (unsigned char* const)birdidleTileData, // start of the sprite data
    58, // the total time of the animation
    2, // number of frames
    32, // width in pixels
    56, // height in pixels
    50, // the total amount of tiles in animation
};
