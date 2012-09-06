//
// BlankPage.xaml.cpp
// Implementation of the BlankPage.xaml class.
//

#include "pch.h"
#include "DirectXPage.xaml.h"

using namespace LiquidusDx;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Input;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Graphics::Display;


/**
 *  CTOR
 */
DirectXPage::DirectXPage() :
	m_renderNeeded(true),
	m_lastPointValid(false)
{
	InitializeComponent();

  _gameRenderer = ref new GameRenderer();
  _gameRenderer->Initialize(
    Window::Current->CoreWindow,
    this,
    DisplayProperties::LogicalDpi);

  /*
	m_renderer = ref new SimpleTextRenderer();
	m_renderer->Initialize(
		Window::Current->CoreWindow,
		this,
		DisplayProperties::LogicalDpi
		);
    */

	Window::Current->CoreWindow->SizeChanged +=  ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &DirectXPage::OnWindowSizeChanged);
	DisplayProperties::LogicalDpiChanged += ref new DisplayPropertiesEventHandler(this, &DirectXPage::OnLogicalDpiChanged);

	m_eventToken = CompositionTarget::Rendering::add(ref new EventHandler<Object^>(this, &DirectXPage::OnRendering));
	m_timer = ref new BasicTimer();
}



void DirectXPage::OnPointerMoved(Platform::Object^ sender, 
                                 Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args)
{
	auto currentPoint = args->GetCurrentPoint(nullptr);
	if (currentPoint->IsInContact)
	{
		if (m_lastPointValid)
		{
			Windows::Foundation::Point delta(
				currentPoint->Position.X - m_lastPoint.X,
				currentPoint->Position.Y - m_lastPoint.Y
				);

			//m_renderer->UpdateView(delta);
			m_renderNeeded = true;
		}
		m_lastPoint = currentPoint->Position;
		m_lastPointValid = true;
	}
	else
	{
		m_lastPointValid = false;
	}
}

void DirectXPage::OnPointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args)
{
	m_lastPointValid = false;
}

void DirectXPage::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
{
  _gameRenderer->UpdateForWindowSizeChange();
	//m_renderer->UpdateForWindowSizeChange();
	m_renderNeeded = true;
}

void DirectXPage::OnLogicalDpiChanged(Platform::Object^ sender)
{
  _gameRenderer->SetDpi(DisplayProperties::LogicalDpi);
	//m_renderer->SetDpi(DisplayProperties::LogicalDpi);
	m_renderNeeded = true;
}

/**
 * Rendering by FrameRendering feature
 */
void DirectXPage::OnRendering(Platform::Object^ sender, 
                              Platform::Object^ args)
{
  if (m_renderNeeded)
	{
		m_timer->Update();

    auto g = _gameRenderer;
		g->Update(m_timer->Total, m_timer->Delta);
		g->Render();
		g->Present();

		m_renderNeeded = false;
	}
}

void DirectXPage::CycleColorPrevious(Platform::Object^ sender, 
                                     RoutedEventArgs^ args)
{
  /*m_renderer->BackgroundColorNext();
	m_renderNeeded = true;*/
}

void DirectXPage::CycleColorNext(Platform::Object^ sender, 
                                 RoutedEventArgs^ args)
{
	/*m_renderer->BackgroundColorPrevious();
	m_renderNeeded = true;*/
}
