////////////////////////////////////////////////////
// window implementation
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "WndImpl.h"

#ifdef ZN_SYSTEM_WINDOWS
#   include "Win32\WndImplWin32.h"
    typedef zn::WndImplWin32 WndSystemImpl;
#endif

namespace zn
{
    WndImpl::WndImpl() : m_isFullscreen( true )
    {

    }

    WndImpl::~WndImpl()
    {

    }

    WndImpl* WndImpl::InstancePtr()
    {
        return ZN_NEW WndSystemImpl();
    }

    bool WndImpl::PopMessage( Message& message )
    {
        if( m_messages.empty() )
        {
            ProcessMessages();
        }
        if( !m_messages.empty() )
        {
            message = m_messages.front();
            m_messages.pop();
            return true;
        }
       return false;
    }

    bool WndImpl::IsFullscreen()
    {
        return m_isFullscreen;
    }
}