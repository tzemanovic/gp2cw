////////////////////////////////////////////////////
// human view interface
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "ViewHuman.h"

namespace zn
{
    ViewHuman::ViewHuman()
    {

    }

    ViewHuman::~ViewHuman()
    {

    }

    void ViewHuman::VRender( const float deltaMs )
    {
        g_pGame->GetRenderer()->PreRender();

        g_pGame->GetRenderer()->PostRender();
        g_pGame->GetRenderer()->Present();
    }

    void ViewHuman::VUpdate( const float deltaMs )
    {

    }
    
    const bool ViewHuman::VProcessMessage( const Message& message )
    {
        return false;
    }
}