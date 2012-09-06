#include "pch.h"
#include "GameRenderer.h"
#include "../Common/AppResource.h"

using namespace concurrency;
using namespace Platform;

/** 
 * CTOR
 */
GameRenderer::GameRenderer()
  : _state(GameRendererState::None)
  , _world(nullptr)
{
}


/**
 * Create device independent
 *
 */
void GameRenderer::CreateDeviceIndependentResources()
{
  baseClass::CreateDeviceIndependentResources();
}

/**
 * Create window size dependent resources
 *
 */
void GameRenderer::CreateWindowSizeDependentResources()
{
  baseClass::CreateWindowSizeDependentResources();
}


/**
 * Create device resources
 *
 */
void GameRenderer::CreateDeviceResources()
{
  baseClass::CreateDeviceResources();

  DX::ThrowIfFailed(
    m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(0x00FF00FF, 1.0),
                                        &_pinkBrush)
    );
}


/**
 * Render data
 */
void GameRenderer::Render()
{
  static const D2D1::ColorF bgcolor = D2D1::ColorF::DeepPink;

  m_d2dContext->BeginDraw();
  m_d2dContext->Clear(D2D1::ColorF(bgcolor));

  switch (_state)
  {
  case None:
    break;
  case Loading:
    break;
  case Playing:
    break;
  case Pause:
    break;
  default:
    break;
  }
  
  auto hr = m_d2dContext->EndDraw();
  if(hr == D2DERR_RECREATE_TARGET) {
    m_d2dContext->SetTarget(nullptr);
    m_d2dTargetBitmap = nullptr;
    CreateWindowSizeDependentResources();
  }
  else {
    DX::ThrowIfFailed(hr);
  }
}

/**
 * Renderer is being updated.
 *
 */
void GameRenderer::Update( float timeTotal, float timeDelta )
{
  (void)timeTotal;
  (void)timeDelta;

  switch(_state) {
  case GameRendererState::None:
    StateTo(GameRendererState::Loading);
    break;
  case GameRendererState::Loading:
    break;
  }
}

/**
 * Change game status
 *
 */
void GameRenderer::StateTo( GameRendererState newstate )
{
  auto oldstate = _state;
  if(oldstate == newstate)
    return;

  OnBeforeStateChange(oldstate, newstate);
  _state = newstate;
  OnAfterStateChange(oldstate, newstate);
}


/**
 * Before state changed
 *
 */
void GameRenderer::OnBeforeStateChange(
      GameRendererState oldstate, 
      GameRendererState newstate )
{
}


/**
 * After state changed
 *
 */
void GameRenderer::OnAfterStateChange(
      GameRendererState oldstate, 
      GameRendererState newstate )
{
  if(newstate == GameRendererState::Loading) {
    OnLoadGame();
  }
}

/**
 * Let's load game
 *
 */
void GameRenderer::OnLoadGame()
{
  auto task = create_task([&]() {
    return AppResource::ReadTextFile(L"Sample.txt");
  }).then([&](String^ json) {
    auto world = world_create(json);
    this->_world = world;
    this->StateTo(GameRendererState::Playing);
  });
}

