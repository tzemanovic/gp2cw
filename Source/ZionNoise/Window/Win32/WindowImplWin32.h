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
        void SwitchToFullscreen( const iVec2& );
        // call when window is destroyed
        void WindowDestroyed();
        
        // initialize window
        virtual bool Init( const string&, const iVec2&, const uint8 );
        // set window visibility
        virtual void SetVisible( const bool );
        // set cursor visibility
        virtual void SetMouseCursorVisible( const bool );
        // process window messages
        virtual void ProcessMessages();

        // accessors
        HWND GetWndHandle() { return m_wndHandle; }

    private:
        // window handle
        HWND m_wndHandle;
        // mouse cursor
        HCURSOR m_cursor;
    };
}