////////////////////////////////////////////////////
// window
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "Window.h"
#include "IWindowImpl.h"

namespace zn
{
    Window::Window() : m_pWindowImpl( NULL )
    {

    }

    Window::~Window()
    {
        Close();
    }

    bool Window::Open( const string& title, const iVec2& windowSize, const uint8 windowStyle )
    {
        // close window in case it is already opened
        Close();
        // instatiate window implementation
        m_pWindowImpl = IWindowImpl::InstancePtr();
        // initialize window
        if( !m_pWindowImpl->Init( title, windowSize, windowStyle ) )
            return false;
        SetVisible( true );
        SetMouseCursorVisible( true );
        return true;
    }

    void Window::Close()
    {
        // delete window implementation
        ZN_SAFE_DELETE( m_pWindowImpl );
    }

    bool Window::IsOpen() const
    {
        return m_pWindowImpl != NULL;
    }

    void Window::SetVisible( const bool visible )
    {
        if( m_pWindowImpl )
            m_pWindowImpl->SetVisible( visible );
    }

    void Window::SetMouseCursorVisible( const bool visible )
    {
        if( m_pWindowImpl )
            m_pWindowImpl->SetMouseCursorVisible( visible );
    }

    bool Window::PollMessage( Message& message )
    {
        // if there is a message, pop it
        if ( m_pWindowImpl && m_pWindowImpl->PopMessage( message ) )
            return true;
        return false;
    }

    bool Window::IsFullscreen()
    {
        if( m_pWindowImpl )
            return m_pWindowImpl->IsFullscreen();
        return false;
    }
}