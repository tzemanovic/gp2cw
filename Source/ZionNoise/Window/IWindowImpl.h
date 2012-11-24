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
        virtual const bool VInit( const string& title, const uint16Vec2& windowSize, const WindowStyleType windowStyle ) = 0;
        // set window visibility
        virtual void VSetVisible( const bool visible ) = 0;
        // set cursor visibility
        virtual void VSetMouseCursorVisible( const bool visible ) = 0;
        // process window messages
        virtual void VProcessMessages() = 0;
        virtual const uint16Vec2 VGetCursorPos() const = 0;
        virtual void VCaptureMouse() = 0;
        virtual void VReleaseMouse() = 0;

        // accessors
        const bool IsFullscreen() const { return m_isFullscreen; }
        const uint16Vec2& GetWindowSize() { return m_windowSize; }

    protected:
        queue<Message> m_messages;
        bool m_isFullscreen;
        uint16Vec2 m_windowSize;
    };
}