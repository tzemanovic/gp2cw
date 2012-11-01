#pragma once
////////////////////////////////////////////////////
// window messages
////////////////////////////////////////////////////

namespace zn
{
    class Message
    {
    public:
        enum Type
        {
            Close,
            KeyPressed,
            KeyReleased
        };

        Message() {}
        Message( const Message::Type type ) : type( type ) {}

        bool operator==( const Message::Type type ) const { return Message::type == type; }

        Type type;
    };
}