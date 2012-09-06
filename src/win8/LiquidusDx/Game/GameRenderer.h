#pragma once

#include "GameRendererState.h"
#include "..\DirectXBase.h"
#include "World.h"

using namespace Microsoft::WRL;

ref class GameRenderer sealed : public DirectXBase
{
  typedef DirectXBase baseClass;
public:
  GameRenderer();
  
  virtual void CreateDeviceIndependentResources() override;
  virtual void CreateDeviceResources() override;
  virtual void CreateWindowSizeDependentResources() override;
  virtual void Render() override;

  void Update(float timeTotal, float timeDelta);

private:
  void StateTo(GameRendererState newstate);
  void OnBeforeStateChange(GameRendererState oldstate, GameRendererState newstate);
  void OnAfterStateChange(GameRendererState oldstate, GameRendererState newstate);
  void OnLoadGame();

private:
  GameRendererState _state;

  ComPtr<ID2D1SolidColorBrush>  _pinkBrush;
  World* _world;

};