﻿

#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------

namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class TextBlock;
                ref class StackPanel;
                ref class Button;
            }
        }
    }
}

namespace LiquidusDx
{
    partial ref class DirectXPage : public ::Windows::UI::Xaml::Controls::SwapChainBackgroundPanel, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
    
        private: ::Windows::UI::Xaml::Controls::TextBlock^ SimpleTextBlock;
        private: ::Windows::UI::Xaml::Controls::StackPanel^ LeftPanel;
        private: ::Windows::UI::Xaml::Controls::StackPanel^ RightPanel;
        private: ::Windows::UI::Xaml::Controls::Button^ Next;
        private: ::Windows::UI::Xaml::Controls::Button^ Previous;
    };
}

