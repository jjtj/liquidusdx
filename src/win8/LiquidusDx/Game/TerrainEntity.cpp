#include "pch.h"
#include "TerrainEntity.h"
#include "../Common/DxUtils.h"
#include "../DirectXHelper.h"
#include "../Terrain/Terrain.h"
#include "../Terrain/Quad.h"

TerrainEntity* gen_bitmap(TerrainEntity* te,
                          ID2D1DeviceContext* ctx,
                          int w,
                          int h);


TerrainEntity* terrain_entity_create(GameContext* ctx,
                                     Terrain* terrain,
                                     int w,
                                     int h)
{
  auto obj = new TerrainEntity();
  obj->_ge._initfunc = terrain_entity_init;
  obj->_ge._updatefunc = terrain_entity_update;
  obj->_ge._drawfunc = terrain_entity_draw;

  obj->terrain = terrain;
  obj->bmp = nullptr;
  
  return obj;
}

IMPL_GAME_ENTITY_FUNC(terrain_entity_init, )
TerrainEntity* terrain_entity_init(GameContext* ) {

}


/**
 *  Generate terrain bitmap
 */
TerrainEntity* gen_bitmap(TerrainEntity* te,
                          ID2D1DeviceContext* ctx,
                          int w,
                          int h)
{
  _ASSERTE(te);
  _ASSERTE(ctx);
  _ASSERTE(w > 0);
  _ASSERTE(h > 0);

  DX::ThrowIfFailed(
    dxutils_create_bitmap(ctx, w, h, &te->bmp)
    );

  ComPtr<ID2D1Image>  old;
  ComPtr<ID2D1SolidColorBrush> brush;

  DX::ThrowIfFailed(
    ctx->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &brush)
    );

  ctx->GetTarget(&old);
  ctx->SetTarget(te->bmp.Get());
  ctx->Clear(D2D1::ColorF(0,0.0f));


  auto rc = D2D1::RectF();
  te->terrain->Query(0,0,w,h,
    [&](Quad* q) {
      _ASSERTE(q);
      _ASSERTE(q->IsValidLeaf());

      rc.left   = (float)q->X();
      rc.top    = (float)q->Y();
      rc.right  = (float)q->Right();
      rc.bottom = (float)q->Bottom();

      ctx->DrawRectangle(&rc,
                         brush.Get());                                     
  });

  ctx->SetTarget(old.Get());
  return te;
}