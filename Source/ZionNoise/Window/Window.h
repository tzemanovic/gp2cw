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
        bool Open( const string&, const iVec2&, const uint8 = WindowStyle::Default );
        // close window
        void Close();
        // is window open
        bool IsOpen() const;
        // set window visibility
        void SetVisible( const bool );
        // set cursor visibility
        void SetMouseCursorVisible( const bool );
        // poll a message
        bool PollMessage( Message& );
        // is window fullscreen
        bool IsFullscreen();

    private:
        // window implementation
        IWindowImpl* m_pWindowImpl;
    };
}