#pragma once
////////////////////////////////////////////////////
// keyboard handler interface
////////////////////////////////////////////////////

#include "..\Window\Message.h"

namespace zn
{
    class IKeyboardHandler
    {
    public:
        virtual bool VOnKeyMsg( const Message& msg ) = 0;
    };
}