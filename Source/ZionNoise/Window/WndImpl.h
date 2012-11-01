#pragma once
////////////////////////////////////////////////////
// window implementation
////////////////////////////////////////////////////

#include "..\Utilities\INoCopy.h"
#include "Message.h"
#include <queue>

namespace zn
{
    class WndImpl : INoCopy
    {
    public:
        WndImpl();
        virtual ~WndImpl();

        static WndImpl* InstancePtr();

        bool PopMessage( Message& );
        bool IsFullscreen();
        
        virtual bool Init( const string&, const iVec2&, const uint8 ) = 0;
        virtual void SetVisible( const bool ) = 0;
        virtual void SetMouseCursorVisible( const bool ) = 0;
        virtual void ProcessMessages() = 0;

    protected:
        queue<Message> m_messages;
        bool m_isFullscreen;
    };
}