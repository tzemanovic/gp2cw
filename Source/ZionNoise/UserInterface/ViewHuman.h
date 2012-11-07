#pragma once
////////////////////////////////////////////////////
// human view interface
////////////////////////////////////////////////////

#include "..\Utilities\IView.h"

namespace zn
{
    class ViewHuman : public IView
    {
    public:
        ViewHuman();
        ~ViewHuman();

        virtual void VRender( const float deltaMs );
        virtual void VUpdate( const float deltaMs );
        virtual const bool VProcessMessage( const Message& message );
    };
}