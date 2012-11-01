////////////////////////////////////////////////////
// window
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Window.h"
#include "WndImpl.h"

namespace zn
{
    Window::Window() : m_pWndImpl( NULL )
    {

    }

    Window::~Window()
    {
        Close();
    }

    bool Window::Open( const string& title, const iVec2& windowSize, const uint8 windowStyle )
    {
        Close();
        m_pWndImpl = WndImpl::InstancePtr();
        if( !m_pWndImpl->Init( title, windowSize, windowStyle ) )
            return false;
        SetVisible( true );
        SetMouseCursorVisible( true );
        return true;
    }

    void Window::Close()
    {
        ZN_SAFE_DELETE( m_pWndImpl );
    }

    bool Window::IsOpen() const
    {
        return m_pWndImpl != NULL;
    }

    void Window::SetVisible( const bool visible )
    {
        if( m_pWndImpl )
            m_pWndImpl->SetVisible( visible );
    }

    void Window::SetMouseCursorVisible( const bool visible )
    {
        if( m_pWndImpl )
            m_pWndImpl->SetMouseCursorVisible( visible );
    }

    bool Window::PollMessage( Message& message )
    {
        if ( m_pWndImpl && m_pWndImpl->PopMessage( message ) )
            return true;
        else
            return false;
    }

    bool Window::IsFullscreen()
    {
        if( m_pWndImpl )
            return m_pWndImpl->IsFullscreen();
        else
            return false;
    }
}