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

    void ViewHuman::VRender( float deltaMs )
    {
        g_pGame->GetRenderer()->PreRender();

        g_pGame->GetRenderer()->PostRender();
        g_pGame->GetRenderer()->Present();
    }

    void ViewHuman::VUpdate( float deltaMs )
    {

    }
}