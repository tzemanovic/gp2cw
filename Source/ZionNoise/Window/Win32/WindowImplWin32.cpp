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
    WindowImplWin32::WindowImplWin32() : m_wndHandle( NULL ), m_cursor( NULL ), m_isMouseCaptured( false )
    {
        g_pWindow = this;
        for( int i = 0; i < ARRAYSIZE( m_oldKeyStates ); ++i )
            m_oldKeyStates[i] = false;
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

    
    KeyType WindowImplWin32::VirtualKeyToKey( WPARAM wParam )
    {
        switch( wParam )
        {
        case 'A':
            return Key::A;
        case 'B':
            return Key::B;
        case 'C':
            return Key::C;
        case 'D':
            return Key::D;
        case 'E':
            return Key::E;
        case 'F':
            return Key::F;
        case 'G':
            return Key::G;
        case 'H':
            return Key::H;
        case 'I':
            return Key::I;
        case 'J':
            return Key::J;
        case 'K':
            return Key::K;
        case 'L':
            return Key::L;
        case 'M':
            return Key::M;
        case 'N':
            return Key::N;
        case 'O':
            return Key::O;
        case 'P':
            return Key::P;
        case 'Q':
            return Key::Q;
        case 'R':
            return Key::R;
        case 'S':
            return Key::S;
        case 'T':
            return Key::T;
        case 'U':
            return Key::U;
        case 'V':
            return Key::V;
        case 'W':
            return Key::W;
        case 'X':
            return Key::X;
        case 'Y':
            return Key::Y;
        case 'Z':
            return Key::Z;
        case VK_LEFT:
            return Key::ArrowLeft;
        case VK_RIGHT:
            return Key::ArrowRight;
        case VK_UP:
            return Key::ArrowUp;
        case VK_DOWN:
            return Key::ArrowDown;
        case VK_NUMPAD0:
            return Key::Num0;
        case VK_NUMPAD1:
            return Key::Num1;
        case VK_NUMPAD2:
            return Key::Num2;
        case VK_NUMPAD3:
            return Key::Num3;
        case VK_NUMPAD4:
            return Key::Num4;
        case VK_NUMPAD5:
            return Key::Num5;
        case VK_NUMPAD6:
            return Key::Num6;
        case VK_NUMPAD7:
            return Key::Num7;
        case VK_NUMPAD8:
            return Key::Num8;
        case VK_NUMPAD9:
            return Key::Num9;
        case VK_F1:
            return Key::F1;
        case VK_F2:
            return Key::F2;
        case VK_F3:
            return Key::F3;
        case VK_F4:
            return Key::F4;
        case VK_F5:
            return Key::F5;
        case VK_F6:
            return Key::F6;
        case VK_F7:
            return Key::F7;
        case VK_F8:
            return Key::F8;
        case VK_F9:
            return Key::F9;
        case VK_F10:
            return Key::F10;
        case VK_F11:
            return Key::F11;
        case VK_F12:
            return Key::F12;
        case VK_ESCAPE:
            return Key::Esc;
        case VK_TAB:
            return Key::Tab;
        case VK_SPACE:
            return Key::Space;
        case VK_RETURN:
            return Key::Return;
        case VK_CONTROL:
            return Key::Ctrl;
        case VK_MENU:
            return Key::Alt;
        case VK_SHIFT:
            return Key::Shift;
        }
        return Key::Undef;
    }

    const bool WindowImplWin32::VInit( const string& title, const uint16Vec2& windowSize, const WindowStyleType windowStyle )
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
        m_windowSize = uint16Vec2( width, height );
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
                    break;
                }
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                {
                    KeyType type = VirtualKeyToKey( wParam );
                    if( !m_oldKeyStates[type] )
                    {
                        Message msg( Message::KeyDown );
                        msg.key.type = type;
                        msg.key.lCtrl = HIWORD( GetKeyState( VK_RCONTROL ) ) != 0;
                        msg.key.rCtrl = HIWORD( GetKeyState( VK_RCONTROL ) ) != 0;
                        msg.key.lAlt = HIWORD( GetKeyState( VK_LMENU ) ) != 0;
                        msg.key.rAlt = HIWORD( GetKeyState( VK_RMENU ) ) != 0;
                        msg.key.lShift = HIWORD( GetKeyState( VK_LSHIFT ) ) != 0;
                        msg.key.rShift = HIWORD( GetKeyState( VK_RSHIFT ) ) != 0;
                        m_messages.push( msg );
                        m_oldKeyStates[type] = true;
                    }
                    break;
                }
            case WM_KEYUP:
            case WM_SYSKEYUP:
                {
                    Message msg( Message::KeyUp );
                    KeyType type = VirtualKeyToKey( wParam );
                    msg.key.type = type;
                    msg.key.lCtrl = HIWORD( GetKeyState( VK_RCONTROL ) ) != 0;
                    msg.key.rCtrl = HIWORD( GetKeyState( VK_RCONTROL ) ) != 0;
                    msg.key.lAlt = HIWORD( GetKeyState( VK_LMENU ) ) != 0;
                    msg.key.rAlt = HIWORD( GetKeyState( VK_RMENU ) ) != 0;
                    msg.key.lShift = HIWORD( GetKeyState( VK_LSHIFT ) ) != 0;
                    msg.key.rShift = HIWORD( GetKeyState( VK_RSHIFT ) ) != 0;
                    m_messages.push( msg );
                    m_oldKeyStates[type] = false;
                    break;
                }
            case WM_LBUTTONDOWN:
                {
                    Message msg( Message::MouseButtonDown );
                    msg.mouseButton.type = MouseButton::LeftButton;
                    msg.mouseButton.ctrl = ( wParam & MK_CONTROL ) != 0;
                    msg.mouseButton.lButton = ( wParam & MK_LBUTTON ) != 0;
                    msg.mouseButton.mButton = ( wParam & MK_MBUTTON ) != 0;
                    msg.mouseButton.rButton = ( wParam & MK_RBUTTON ) != 0;
                    msg.mouseButton.shift = ( wParam & MK_SHIFT ) != 0;
                    msg.mouseButton.xButton1 = ( wParam & MK_XBUTTON1 ) != 0;
                    msg.mouseButton.xButton2 = ( wParam & MK_XBUTTON2 ) != 0;
                    msg.mouseButton.x = static_cast< int16 >( LOWORD( lParam ) );
                    msg.mouseButton.y = static_cast< int16 >( HIWORD( lParam ) );
                    m_messages.push( msg );
                    VCaptureMouse();
                    break;
                }
            case WM_LBUTTONUP:
                {
                    Message msg( Message::MouseButtonUp );
                    msg.mouseButton.type = MouseButton::LeftButton;
                    msg.mouseButton.x = static_cast< int16 >( LOWORD( lParam ) );
                    msg.mouseButton.y = static_cast< int16 >( HIWORD( lParam ) );
                    m_messages.push( msg );
                    VReleaseMouse();
                    break;
                }
            case WM_RBUTTONDOWN:
                {
                    Message msg( Message::MouseButtonDown );
                    msg.mouseButton.type = MouseButton::RightButton;
                    msg.mouseButton.ctrl = ( wParam & MK_CONTROL ) != 0;
                    msg.mouseButton.lButton = ( wParam & MK_LBUTTON ) != 0;
                    msg.mouseButton.mButton = ( wParam & MK_MBUTTON ) != 0;
                    msg.mouseButton.rButton = ( wParam & MK_RBUTTON ) != 0;
                    msg.mouseButton.shift = ( wParam & MK_SHIFT ) != 0;
                    msg.mouseButton.xButton1 = ( wParam & MK_XBUTTON1 ) != 0;
                    msg.mouseButton.xButton2 = ( wParam & MK_XBUTTON2 ) != 0;
                    msg.mouseButton.x = static_cast< int16 >( LOWORD( lParam ) );
                    msg.mouseButton.y = static_cast< int16 >( HIWORD( lParam ) );
                    m_messages.push( msg );
                    VCaptureMouse();
                    break;
                }
            case WM_RBUTTONUP:
                {
                    Message msg( Message::MouseButtonUp );
                    msg.mouseButton.type = MouseButton::RightButton;
                    msg.mouseButton.x = static_cast< int16 >( LOWORD( lParam ) );
                    msg.mouseButton.y = static_cast< int16 >( HIWORD( lParam ) );
                    m_messages.push( msg );
                    VReleaseMouse();
                    break;
                }
            case WM_MBUTTONDOWN:
                {
                    Message msg( Message::MouseButtonDown );
                    msg.mouseButton.type = MouseButton::MiddleButton;
                    msg.mouseButton.ctrl = ( wParam & MK_CONTROL ) != 0;
                    msg.mouseButton.lButton = ( wParam & MK_LBUTTON ) != 0;
                    msg.mouseButton.mButton = ( wParam & MK_MBUTTON ) != 0;
                    msg.mouseButton.rButton = ( wParam & MK_RBUTTON ) != 0;
                    msg.mouseButton.shift = ( wParam & MK_SHIFT ) != 0;
                    msg.mouseButton.xButton1 = ( wParam & MK_XBUTTON1 ) != 0;
                    msg.mouseButton.xButton2 = ( wParam & MK_XBUTTON2 ) != 0;
                    msg.mouseButton.x = static_cast< int16 >( LOWORD( lParam ) );
                    msg.mouseButton.y = static_cast< int16 >( HIWORD( lParam ) );
                    m_messages.push( msg );
                    VCaptureMouse();
                    break;
                }
            case WM_MBUTTONUP:
                {
                    Message msg( Message::MouseButtonUp );
                    msg.mouseButton.type = MouseButton::MiddleButton;
                    msg.mouseButton.x = static_cast< int16 >( LOWORD( lParam ) );
                    msg.mouseButton.y = static_cast< int16 >( HIWORD( lParam ) );
                    m_messages.push( msg );
                    VReleaseMouse();
                    break;
                }
            case WM_XBUTTONDOWN:
                {
                    Message msg( Message::MouseButtonDown );
                    msg.mouseButton.type = HIWORD( wParam ) == XBUTTON1 ? MouseButton::XButton1 : MouseButton::XButton2;
                    msg.mouseButton.ctrl = ( wParam & MK_CONTROL ) != 0;
                    msg.mouseButton.lButton = ( wParam & MK_LBUTTON ) != 0;
                    msg.mouseButton.mButton = ( wParam & MK_MBUTTON ) != 0;
                    msg.mouseButton.rButton = ( wParam & MK_RBUTTON ) != 0;
                    msg.mouseButton.shift = ( wParam & MK_SHIFT ) != 0;
                    msg.mouseButton.xButton1 = ( wParam & MK_XBUTTON1 ) != 0;
                    msg.mouseButton.xButton2 = ( wParam & MK_XBUTTON2 ) != 0;
                    msg.mouseButton.x = static_cast< int16 >( LOWORD( lParam ) );
                    msg.mouseButton.y = static_cast< int16 >( HIWORD( lParam ) );
                    m_messages.push( msg );
                    break;
                }
            case WM_XBUTTONUP:
                {
                    Message msg( Message::MouseButtonUp );
                    msg.mouseButton.type = HIWORD( wParam ) == XBUTTON1 ? MouseButton::XButton1 : MouseButton::XButton2;
                    msg.mouseButton.x = static_cast< int16 >( LOWORD( lParam ) );
                    msg.mouseButton.y = static_cast< int16 >( HIWORD( lParam ) );
                    m_messages.push( msg );
                    break;
                }
            case WM_MOUSEMOVE:
                {
                    Message msg( Message::MouseMove );
                    msg.mouseMove.x = static_cast< int16 >( LOWORD( lParam ) );
                    msg.mouseMove.y = static_cast< int16 >( HIWORD( lParam ) );
                    msg.mouseMove.ctrl = ( wParam & MK_CONTROL ) != 0;
                    msg.mouseMove.lButton = ( wParam & MK_LBUTTON ) != 0;
                    msg.mouseMove.mButton = ( wParam & MK_MBUTTON ) != 0;
                    msg.mouseMove.rButton = ( wParam & MK_RBUTTON ) != 0;
                    msg.mouseMove.shift = ( wParam & MK_SHIFT ) != 0;
                    msg.mouseMove.xButton1 = ( wParam & MK_XBUTTON1 ) != 0;
                    msg.mouseMove.xButton2 = ( wParam & MK_XBUTTON2 ) != 0;
                    m_messages.push( msg );
                    break;
                }
            case WM_MOUSEWHEEL:
                {
                    POINT screenPos;
                    screenPos.x = LOWORD( lParam );
                    screenPos.y = HIWORD( lParam );
                    ScreenToClient( m_wndHandle, &screenPos );
                    Message msg( Message::MouseWheel );
                    msg.mouseWheel.ctrl = ( wParam & MK_CONTROL ) != 0;
                    msg.mouseWheel.lButton = ( wParam & MK_LBUTTON ) != 0;
                    msg.mouseWheel.mButton = ( wParam & MK_MBUTTON ) != 0;
                    msg.mouseWheel.rButton = ( wParam & MK_RBUTTON ) != 0;
                    msg.mouseWheel.shift = ( wParam & MK_SHIFT ) != 0;
                    msg.mouseWheel.xButton1 = ( wParam & MK_XBUTTON1 ) != 0;
                    msg.mouseWheel.xButton2 = ( wParam & MK_XBUTTON2 ) != 0;
                    msg.mouseWheel.x = static_cast< int16 >( screenPos.x );
                    msg.mouseWheel.y = static_cast< int16 >( screenPos.y );
                    msg.mouseWheel.delta = static_cast< int16 >( HIWORD( wParam ) ) / 120;
                    m_messages.push( msg );
                    break;
                }
            case WM_CHAR:
                {
                    Message msg( Message::Text );
                    msg.text.unicode = static_cast< uint32 >( wParam );
                    m_messages.push( msg );
                    break;
                }
            case WM_ACTIVATEAPP:
                {
                    if( wParam && m_isMouseCaptured )
                        SetCapture( m_wndHandle );
                    break;
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

    const uint16Vec2 WindowImplWin32::VGetCursorPos() const
    {
        POINT lpPoint;
        GetCursorPos( &lpPoint );
        return uint16Vec2( uint16( lpPoint.x ), uint16( lpPoint.y ) );
    }

    void WindowImplWin32::VCaptureMouse()
    {
        SetCapture( m_wndHandle );
        m_isMouseCaptured = true;
    }
    
    void WindowImplWin32::VReleaseMouse()
    {
        ReleaseCapture();
        m_isMouseCaptured = false;
    }
}