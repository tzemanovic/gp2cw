#pragma once
////////////////////////////////////////////////////
// window messages
////////////////////////////////////////////////////

#include "InputDevices.h"

namespace zn
{
    class Message
    {
    public:
        enum Type
        {
            Close,
            KeyDown,
            KeyUp,
            MouseButtonDown,
            MouseButtonUp,
            MouseMove,
            MouseWheel,
            Text,
            Count
        };

        struct KeyMessage
        {
            KeyType type;
            bool lCtrl;
            bool rCtrl;
            bool lAlt;
            bool rAlt;
            bool lShift;
            bool rShift;
        };

        struct MouseButtonMessage
        {
            MouseButtonType type;
            int16 x;
            int16 y;
            bool ctrl;
            bool lButton;
            bool mButton;
            bool rButton;
            bool shift;
            bool xButton1;
            bool xButton2;
        };

        struct MouseMoveMessage
        {
            int16 x;
            int16 y;
            bool ctrl;
            bool lButton;
            bool mButton;
            bool rButton;
            bool shift;
            bool xButton1;
            bool xButton2;
        };

        struct MouseWheelMessage
        {
            int16 x;
            int16 y;
            int16 delta;
            bool ctrl;
            bool lButton;
            bool mButton;
            bool rButton;
            bool shift;
            bool xButton1;
            bool xButton2;
        };

        struct TextMessage
        {
            uint32 unicode; 
        };

        Message() {}
        Message( const Message::Type type ) : type( type ) {}

        // compare messages' type
        bool operator==( const Message::Type type ) const { return Message::type == type; }

        Type type;

        union
        {
            KeyMessage key;
            MouseButtonMessage mouseButton;
            MouseMoveMessage mouseMove;
            MouseWheelMessage mouseWheel;
            TextMessage text;
        };
    };
}