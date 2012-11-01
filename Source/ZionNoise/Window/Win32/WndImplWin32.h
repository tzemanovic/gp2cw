#pragma once
////////////////////////////////////////////////////
// window win32 implementation
////////////////////////////////////////////////////

#include "..\WndImpl.h"
#include <Windows.h>

namespace zn
{
    class WndImplWin32 : public WndImpl
    {
    public:
        WndImplWin32();
        WndImplWin32( const string&, const iVec2&, const uint8 );
        ~WndImplWin32();
        
        static LRESULT CALLBACK StaticWndProc( HWND, UINT, WPARAM, LPARAM );

        LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
        void SwitchToFullscreen( const iVec2& );
        void Destroy();
        
        virtual bool Init( const string&, const iVec2&, const uint8 );
        virtual void SetVisible( const bool );
        virtual void SetMouseCursorVisible( const bool );
        virtual void ProcessMessages();

        HWND GetWndHandle() { return m_wndHandle; }

    private:
        HWND m_wndHandle;
        HCURSOR m_cursor;
    };
}