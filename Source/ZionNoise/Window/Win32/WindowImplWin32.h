#pragma once
////////////////////////////////////////////////////
// window win32 implementation
////////////////////////////////////////////////////

#include "..\IWindowImpl.h"
#include "..\InputDevices.h"

namespace zn
{
    class WindowImplWin32 : public IWindowImpl
    {
    public:
        WindowImplWin32();
        ~WindowImplWin32();
        
        // static window proc function
        static LRESULT CALLBACK StaticWndProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
        // translate virtual key code to key message
        static KeyType VirtualKeyToKey( WPARAM wParam );

        // window's proc function
        LRESULT CALLBACK WndProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
        // switch window to fullscreen mode
        void SwitchToFullscreen( const uint16Vec2& windowSize );
        // call when window is destroyed
        void WindowDestroyed();
        
        // initialize window
        const bool VInit( const string& title, const uint16Vec2& windowSize, const WindowStyleType windowStyle );
        // set window visibility
        void VSetVisible( const bool visible );
        // set cursor visibility
        void VSetMouseCursorVisible( const bool visible );
        // process window messages
        void VProcessMessages();
        const uint16Vec2 VGetCursorPos() const;
        void VCaptureMouse();
        void VReleaseMouse();

        // accessors
        HWND GetWndHandle() { return m_wndHandle; }

    private:
        // window handle
        HWND m_wndHandle;
        // mouse cursor
        HCURSOR m_cursor;
        // old key states
        KeyStates m_oldKeyStates;
        // is mouse captured
        bool m_isMouseCaptured;
    };
}