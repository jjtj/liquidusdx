#include "pch.h"
#include "World.h"
#include "../Terrain/QuadTreeBuild.h"

using namespace Platform;
using namespace Windows::Data::Json;

#define JSON_NAMED_OBJECT(JObject, Name)  \
  JObject->GetNamedObject(ref new Platform::String(Name))

#define JSON_NAMED_NUMBER(JObject, Name) \
  JObject->GetNamedNumber(ref new Platform::String(Name))

#define PSTR(Str) \
  ref new Platform::String(Str)



/**
 *  Create world
 *
 *  @param json {Platform::String} Json string
 *
 */
World* world_create(Platform::String^ json)
{
  auto world = new World();

  auto root = JsonObject::Parse(json);
  auto dim = JSON_NAMED_OBJECT(root, L"dim");
  world->width = (int)JSON_NAMED_NUMBER(dim, L"w");
  world->height = (int)JSON_NAMED_NUMBER(dim, L"h");

  auto terrainJson = root->GetNamedString(PSTR(L"wolrdTerrain"));
  auto terrainArray = JsonArray::Parse(terrainJson);

  auto rootQuad = quad_tree_build(terrainArray);

  auto newTerrain = new Terrain();
  newTerrain->ReplaceRoot(rootQuad);

  world->worldTerrain = terrain_entity_create(newTerrain, 0, 0);

  return world;
}

/**
 *  Generate terrain bitmap for world
 */
World* world_gen_terrain_bitmap(World* w,
                                ID2D1DeviceContext* ctx,
                                const SIZE& screensize)
{
  _ASSERTE(w);
  _ASSERTE(ctx);

  terrain_entity_generate_bitmap(w->worldTerrain,
                                 ctx,
                                 screensize.cx,
                                 screensize.cy);
}