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

        void VRender( float deltaMs );
        void VUpdate( float deltaMs );
    };
}