#pragma once
////////////////////////////////////////////////////
// mesh component
////////////////////////////////////////////////////

#include "RenderComponent.h"
#include "..\..\..\Geometry\MeshGeometry.h"

namespace zn
{
    class IMeshMaterial;

    typedef vector< MeshGeometry* > MeshGeometryVector;

    class MeshComponent : public RenderComponent
    {
    public:
        MeshComponent();
        ~MeshComponent();

        bool VInit();
        
        void LoadGeometryFromFile( const string& filename );
        void AddGeometry( MeshGeometry* pMeshGeometry );
        MeshGeometry* GetGeometry( uint32 index );

        uint32 GetGeometryCount() { return m_meshGeometries.size(); }
        IMeshMaterial* GetMeshMaterial() { return m_pMeshMaterial; }

    private:
        shared_ptr< SceneNode > VCreateSceneNode();

        IMeshMaterial* m_pMeshMaterial;
        MeshGeometryVector m_meshGeometries;
    };
}