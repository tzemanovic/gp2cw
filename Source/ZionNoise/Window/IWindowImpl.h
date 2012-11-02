#pragma once
////////////////////////////////////////////////////
// window implementation
////////////////////////////////////////////////////

#include "..\Utilities\INoCopy.h"
#include "Message.h"
#include <queue>

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
        bool PopMessage( Message& );
        
        // initialize window
        virtual bool Init( const string&, const iVec2&, const uint8 ) = 0;
        // set window visibility
        virtual void SetVisible( const bool ) = 0;
        // set cursor visibility
        virtual void SetMouseCursorVisible( const bool ) = 0;
        // process window messages
        virtual void ProcessMessages() = 0;

        // is window fullscreen?
        bool IsFullscreen() { return m_isFullscreen; }

    protected:
        queue<Message> m_messages;
        bool m_isFullscreen;
    };
}