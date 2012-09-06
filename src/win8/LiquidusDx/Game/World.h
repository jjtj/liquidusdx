#pragma once

#include "Level.h"
#include "TerrainEntity.h"

struct World
{
  int	width;
  int height;
  std::vector<Level> levels;
  TerrainEntity* worldTerrain;
};

World* world_create(Platform::String^ json);
World* world_gen_terrain_bitmap(World* w, 
                                ID2D1DeviceContext* ctx, 
                                const SIZE& screensize);
