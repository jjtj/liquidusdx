#pragma once

#include "GameContext.h"

typedef void (*GAME_ENTITY_FUNC)(GameEntity* ge,
                                 GameContext* ctx,
                                 UINT32 userdata);

#define DECL_GAME_ENTITY_FUNC(X)  \
  void X(GameEntity* ge,   \
         GameContext* ctx, \
         UINT32 userdata)

#define IMPL_GAME_ENTITY_FUNC(X, Y)  \
  void X(Y* ge,   \
         GameContext* ctx, \
         UINT32 userdata)

struct GameEntity
{
  GAME_ENTITY_FUNC  _initfunc;
  GAME_ENTITY_FUNC  _updatefunc;
  GAME_ENTITY_FUNC  _drawfunc;
  GAME_ENTITY_FUNC  _destroyfunc;
};