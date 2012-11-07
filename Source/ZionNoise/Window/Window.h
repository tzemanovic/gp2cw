#pragma once
////////////////////////////////////////////////////
// window
////////////////////////////////////////////////////

#include "..\Utilities\INoCopy.h"
#include "WindowStyle.h"
#include "Message.h"

namespace zn
{
    class IWindowImpl;
    class Window : private INoCopy
    {
    public:
        Window();
        ~Window();

        // open window
        const bool Open( const string& title, const uint16Vec2& windowSize, const WindowStyleType windowStyle );
        // close window
        void Close();
        // is window open
        const bool IsOpen() const;
        // set window visibility
        void SetVisible( const bool visible );
        // set cursor visibility
        void SetMouseCursorVisible( const bool visible );
        // poll a message
        const bool PollMessage( Message& message );
        // is window fullscreen
        const bool IsFullscreen() const;

        // accessors
        IWindowImpl* GetWindowImpl() const { return m_pWindowImpl; }

    private:
        // window implementation
        IWindowImpl* m_pWindowImpl;
    };
}