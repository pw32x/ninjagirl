#pragma once

#include "galefile151119\galefile.h"
#include <vector>
#include "Options.h"
#include "SMSCommon.h"

namespace sms
{

bool TilesAreIdentical(const Tile& firstTile, const Tile& secondTile);
bool TilesAreMirroredOnX(const Tile& firstTile, const Tile& secondTile);
bool TilesAreMirroredOnY(const Tile& firstTile, const Tile& secondTile);
bool TilesAreMirroredOnXY(const Tile& firstTile, const Tile& secondTile);

bool TilesAreIdenticalOrMirrored(const Tile& firstTile, const Tile& secondTile);

bool StoreContainsIdenticalOrMirroredTile(std::vector<Tile>& tileStore, const Tile& tileToFind);

int AddOrGetTileInStore(std::vector<Tile>& tileStore,  const Tile& tileToFind, bool removeDuplicates = true);

}