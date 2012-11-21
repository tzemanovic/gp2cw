#pragma once
////////////////////////////////////////////////////
// Screen element scene implementation
////////////////////////////////////////////////////

#include "..\Graphics\IScreenElement.h"
#include "..\Graphics\Scene.h"

namespace zn
{
    class ScreenElementScene : public IScreenElement, public Scene
    {
    public:
        ScreenElementScene( shared_ptr< Renderer > pRenderer ) : IScreenElement(), Scene( pRenderer ) {}
        virtual ~ScreenElementScene() {}

        virtual void VRender( const float deltaMs ) { Render( deltaMs ); }
        virtual void VUpdate( const float deltaMs ) { Update( deltaMs ); }
    };
}