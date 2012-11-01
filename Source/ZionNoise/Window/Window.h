#pragma once
////////////////////////////////////////////////////
// window
////////////////////////////////////////////////////

#include "..\Utilities\INoCopy.h"
#include "WndStyle.h"
#include "Message.h"

namespace zn
{
    class WndImpl;
    class Window : private INoCopy
    {
    public:
        Window();
        ~Window();

        bool Open( const string&, const iVec2&, const uint8 = WndStyle::Default );
        void Close();
        bool IsOpen() const;
        void SetVisible( const bool );
        void SetMouseCursorVisible( const bool );
        bool PollMessage( Message& );
        bool IsFullscreen();

    private:
        WndImpl* m_pWndImpl;
    };
}