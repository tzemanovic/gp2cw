#pragma once
////////////////////////////////////////////////////
// mouse handler interface
////////////////////////////////////////////////////

#include "..\Window\Message.h"

namespace zn
{
    class IMouseHandler
    {
    public:
        virtual bool VOnMouseMsg( const Message& msg ) = 0;
    };
}