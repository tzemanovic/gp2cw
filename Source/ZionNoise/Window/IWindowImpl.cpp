////////////////////////////////////////////////////
// window implementation
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "IWindowImpl.h"

// decide which implementation is required
#ifdef ZN_PLATFORM_WIN32
#   include "Win32\WindowImplWin32.h"
    typedef zn::WindowImplWin32 WindowPlatformImpl;
#endif

namespace zn
{
    IWindowImpl::IWindowImpl() : m_isFullscreen( true )
    {

    }

    IWindowImpl::~IWindowImpl()
    {

    }

    IWindowImpl* IWindowImpl::InstancePtr()
    {
        return ZN_NEW WindowPlatformImpl();
    }

    const bool IWindowImpl::PopMessage( Message& message )
    {
        // if there are no messages in the queue, check for new ones
        if( m_messages.empty() )
        {
            VProcessMessages();
        }
        // if there are messages, pop a next message
        if( !m_messages.empty() )
        {
            message = m_messages.front();
            m_messages.pop();
            return true;
        }
       return false;
    }
}