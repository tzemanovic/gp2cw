#pragma once
////////////////////////////////////////////////////
// sky sphere component
////////////////////////////////////////////////////

#include "MeshComponent.h"

namespace zn
{
    class SkySphereComponent : public MeshComponent
    {
    public:
        SkySphereComponent( const string& textureFilename );

        bool VInit();

    protected:
        shared_ptr< SceneNode > VCreateSceneNode();
        string m_textureFilename;
    };
}