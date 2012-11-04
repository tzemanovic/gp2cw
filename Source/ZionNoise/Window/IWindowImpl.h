#pragma once
////////////////////////////////////////////////////
// window implementation
////////////////////////////////////////////////////

#include "..\Utilities\INoCopy.h"
#include "Message.h"

namespace zn
{
    class IWindowImpl : INoCopy
    {
    public:
        IWindowImpl();
        virtual ~IWindowImpl();

        // get window implementation pointer
        static IWindowImpl* InstancePtr();

        // pop message from the message queue
        const bool PopMessage( Message& message );
        
        // initialize window
        virtual const bool VInit( const string& title, const uint16Vec2& windowSize, const uint8 windowStyle ) = 0;
        // set window visibility
        virtual void VSetVisible( const bool visible ) = 0;
        // set cursor visibility
        virtual void VSetMouseCursorVisible( const bool visible ) = 0;
        // process window messages
        virtual void VProcessMessages() = 0;

        // accessors
        const bool IsFullscreen() const { return m_isFullscreen; }

    protected:
        queue<Message> m_messages;
        bool m_isFullscreen;
    };
}