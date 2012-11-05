#pragma once
////////////////////////////////////////////////////
// window win32 implementation
////////////////////////////////////////////////////

#include "..\IWindowImpl.h"
#include <Windows.h>

namespace zn
{
    class WindowImplWin32 : public IWindowImpl
    {
    public:
        WindowImplWin32();
        ~WindowImplWin32();
        
        // static window proc function
        static LRESULT CALLBACK StaticWndProc( HWND, UINT, WPARAM, LPARAM );

        // window's proc function
        LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
        // switch window to fullscreen mode
        void SwitchToFullscreen( const uint16Vec2& );
        // call when window is destroyed
        void WindowDestroyed();
        
        // initialize window
        const bool VInit( const string& title, const uint16Vec2& windowSize, const uint8 windowStyle );
        // set window visibility
        void VSetVisible( const bool visible );
        // set cursor visibility
        void VSetMouseCursorVisible( const bool visible );
        // process window messages
        void VProcessMessages();

        // accessors
        HWND GetWndHandle() { return m_wndHandle; }

    private:
        // window handle
        HWND m_wndHandle;
        // mouse cursor
        HCURSOR m_cursor;
    };
}