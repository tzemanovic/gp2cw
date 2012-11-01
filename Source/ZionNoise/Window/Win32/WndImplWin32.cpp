////////////////////////////////////////////////////
// window win32 implementation
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "WndImplWin32.h"
#include "..\WndStyle.h"

namespace
{
    // current window pointer
    zn::WndImplWin32* g_pWindow = NULL;
    // class name
    const wchar_t* classNameW = L"ZionNoise_Window";
}

namespace zn
{
    WndImplWin32::WndImplWin32() : m_wndHandle( NULL ), m_cursor( NULL )
    {
        g_pWindow = this;
    }

    WndImplWin32::WndImplWin32( const string& title, const iVec2& windowSize, const uint8 windowStyle ) :
        m_wndHandle( NULL ), m_cursor( NULL )
    {
        g_pWindow = this;
        Init( title, windowSize, windowStyle );
    }

    WndImplWin32::~WndImplWin32()
    {
        if( m_wndHandle )
            DestroyWindow( m_wndHandle );
        UnregisterClass( classNameW, GetModuleHandle( NULL ) );
    }

    LRESULT CALLBACK WndImplWin32::StaticWndProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam )
    {
        return g_pWindow->WndProc( handle, message, wParam, lParam );
    }

    bool WndImplWin32::Init( const string& title, const iVec2& windowSize, const uint8 windowStyle )
    {
        // covert title string to wstring
        wstring wTitle;
        wTitle.assign( title.begin(), title.end() );

        // window class details
        WNDCLASSEX windowClass;
        windowClass.cbSize = sizeof( WNDCLASSEX );
        windowClass.style = CS_VREDRAW | CS_HREDRAW;
        windowClass.lpfnWndProc = &WndImplWin32::StaticWndProc;
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
        if( windowStyle == WndStyle::Window )
        {
            m_isFullscreen = false;
            style |= WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_SYSMENU;
            // adjust the window size with the borders etc.
            RECT rectangle = {0, 0, width, height};
            AdjustWindowRect(&rectangle, style, false);
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

    LRESULT CALLBACK WndImplWin32::WndProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam )
    {
	    switch( message )
	    {
		    case WM_DESTROY:
			    {
                    // destroy window
                    Destroy();
			        break;
			    }
            case WM_CLOSE:
                {
                    Message msg( Message::Close );
                    m_messages.push( msg );
                }
			default:
                return DefWindowProc( handle, message, wParam, lParam );
	    }
	    return 0;
    }

    void WndImplWin32::SwitchToFullscreen( const iVec2& windowSize )
    {
        // set display settings
        DEVMODE devMode;
        devMode.dmSize = sizeof( devMode );
        devMode.dmPelsWidth = windowSize.x;
        devMode.dmPelsHeight = windowSize.y;
        devMode.dmBitsPerPel = 32;
        devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

        if( ChangeDisplaySettings( &devMode, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
        {
            return;
        }
        SetWindowLong( m_wndHandle, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );
        SetWindowLong( m_wndHandle, GWL_EXSTYLE, WS_EX_APPWINDOW );
        SetWindowPos( m_wndHandle, HWND_TOP, 0, 0, windowSize.x, windowSize.y, SWP_FRAMECHANGED );
        ShowWindow( m_wndHandle, SW_SHOW );
    }

    void WndImplWin32::Destroy()
    {
        // show cursor in case it was hidden
        SetMouseCursorVisible( true );
        if( g_pWindow )
        {
            // reset display settings
            ChangeDisplaySettings( 0, 0 );
            g_pWindow = NULL;
        }
    }

    void WndImplWin32::SetVisible( const bool visible )
    {
        // show window
        ShowWindow( m_wndHandle, visible ? SW_SHOW : SW_HIDE );
    }

    void WndImplWin32::SetMouseCursorVisible( const bool visible )
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

    void WndImplWin32::ProcessMessages()
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