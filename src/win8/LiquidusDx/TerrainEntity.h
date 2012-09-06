#pragma once

#include "GameEntity.h"
#include "../Terrain/Terrain.h"

using namespace Microsoft::WRL;

struct TerrainEntity 
{
  GameEntity  _ge;
  Terrain*  terrain;
  ComPtr<ID2D1Bitmap1>  bmp;
};

TerrainEntity* terrain_entity_create(GameContext* ctx,
                                     Terrain* terrain,
                                     int x,
                                     int y);

DECL_GAME_ENTITY_FUNC(terrain_entity_init);
DECL_GAME_ENTITY_FUNC(terrain_entity_update);
DECL_GAME_ENTITY_FUNC(terrain_entity_draw);
