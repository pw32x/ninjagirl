#pragma once

#include "windows.h"
#include <vector>
#include <string>

namespace SpriteMaster
{

#define SMS_TILE_WIDTH 8
#define SMS_TILE_HEIGHT 8

typedef std::vector<BYTE> Tile;

const int NEXT_FRAME_NOT_SET = -1;
const int NO_LOOP = -2;

std::string str_toupper(std::string s);

}