////////////////////////////////////////////////////
// window win32 implementation
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "WindowImplWin32.h"
#include "..\WindowStyle.h"

namespace
{
    // current window pointer
    zn::WindowImplWin32* g_pWindow = NULL;
    // class name
    const wchar_t* classNameW = L"ZionNoise_Window";
}

namespace zn
{
    WindowImplWin32::WindowImplWin32() : m_wndHandle( NULL ), m_cursor( NULL )
    {
        g_pWindow = this;
    }

    WindowImplWin32::~WindowImplWin32()
    {
        // if there is a window, destroy it
        if( m_wndHandle )
            DestroyWindow( m_wndHandle );
        // unregister window class
        UnregisterClass( classNameW, GetModuleHandle( NULL ) );
    }

    LRESULT CALLBACK WindowImplWin32::StaticWndProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam )
    {
        // call the non-static window proc
        return g_pWindow->WndProc( handle, message, wParam, lParam );
    }

    const bool WindowImplWin32::VInit( const string& title, const uint16Vec2& windowSize, const uint8 windowStyle )
    {
        // covert title string to wstring
        wstring wTitle;
        wTitle.assign( title.begin(), title.end() );

        // window class details
        WNDCLASSEX windowClass = { 0 };
        windowClass.cbSize = sizeof( WNDCLASSEX );
        windowClass.style = CS_VREDRAW | CS_HREDRAW;
        windowClass.lpfnWndProc = &WindowImplWin32::StaticWndProc;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = 0;
        windowClass.hInstance = GetModuleHandle( NULL );
        windowClass.hIcon = 0;
        windowClass.hIconSm = 0;
        windowClass.hCursor = 0;
        windowClass.hbrBackground = 0;
        windowClass.lpszMenuName = 0;
        windowClass.lpszClassName = classNameW;
        // register the window
        if( !RegisterClassEx( &windowClass ) )
            return false;

        // find position and size
        HDC screenDC = GetDC( NULL );
        int left = ( GetDeviceCaps( screenDC, HORZRES ) - windowSize.x )  / 2;
        int top = ( GetDeviceCaps( screenDC, VERTRES ) - windowSize.y ) / 2;
        int width = windowSize.x;
        int height = windowSize.y;
        ReleaseDC( NULL, screenDC );

        // set the style of the window
        DWORD style = WS_VISIBLE;
        if( windowStyle == WindowStyle::Window )
        {
            m_isFullscreen = false;
            style |= WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_SYSMENU;
            // adjust the window size with the borders etc.
            RECT rectangle = { 0, 0, width, height };
            AdjustWindowRect( &rectangle, style, false );
            width  = rectangle.right - rectangle.left;
            height = rectangle.bottom - rectangle.top;
        }
        
        // create the window
        m_wndHandle = CreateWindowEx( NULL, classNameW, wTitle.c_str(), style, left, top,  width,  height, 
            GetDesktopWindow(), NULL, GetModuleHandle( NULL ), NULL );
        
        if( m_isFullscreen )
            SwitchToFullscreen( windowSize );

        return true;
    }

    LRESULT CALLBACK WindowImplWin32::WndProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam )
    {
	    switch( message )
	    {
		    case WM_DESTROY:
			    {
                    // destroy window
                    WindowDestroyed();
			        break;
			    }
            case WM_CLOSE:
                {
                    // create close message and push it to the queue
                    Message msg( Message::Close );
                    m_messages.push( msg );
                }
			default:
                // default window procedure
                return DefWindowProc( handle, message, wParam, lParam );
	    }
	    return 0;
    }

    void WindowImplWin32::SwitchToFullscreen( const uint16Vec2& windowSize )
    {
        // set display settings
        DEVMODE devMode;
        devMode.dmSize = sizeof( devMode );
        devMode.dmPelsWidth = windowSize.x;
        devMode.dmPelsHeight = windowSize.y;
        devMode.dmBitsPerPel = 32;
        devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

        // change default display device settings
        if( ChangeDisplaySettings( &devMode, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
            return;
        // set window style
        SetWindowLong( m_wndHandle, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );
        // set extended window style
        SetWindowLong( m_wndHandle, GWL_EXSTYLE, WS_EX_APPWINDOW );
        // set window size, position and z-order
        SetWindowPos( m_wndHandle, HWND_TOP, 0, 0, windowSize.x, windowSize.y, SWP_FRAMECHANGED );
        // show the window
        VSetVisible( true );
    }

    void WindowImplWin32::WindowDestroyed()
    {
        // show cursor in case it was hidden
        VSetMouseCursorVisible( true );
        if( g_pWindow )
        {
            // reset display settings
            ChangeDisplaySettings( 0, 0 );
            g_pWindow = NULL;
        }
    }

    void WindowImplWin32::VSetVisible( const bool visible )
    {
        // show window
        ShowWindow( m_wndHandle, visible ? SW_SHOW : SW_HIDE );
    }

    void WindowImplWin32::VSetMouseCursorVisible( const bool visible )
    {
        if( visible )
        {
            // load arrow cursor if it hasn't been loaded yet
            if( !m_cursor )
                m_cursor = LoadCursor( NULL, IDC_ARROW );
            // show cursor
            SetCursor( m_cursor );
        }
        else
        {
            // hide cursor
            SetCursor( NULL );
        }
    }

    void WindowImplWin32::VProcessMessages()
    {
        // process window messages
        MSG message;
        while( PeekMessage( &message, m_wndHandle, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &message );
            DispatchMessage( &message );
        }
    }
}