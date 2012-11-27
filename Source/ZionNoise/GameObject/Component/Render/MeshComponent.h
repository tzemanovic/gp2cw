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
        friend class ModelLoader;

    public:
        MeshComponent();
        virtual ~MeshComponent();

        virtual bool VInit();
        
        void LoadGeometryFromFile( const string& filename );
        void CreateCubeGeometry( const fVec3& dimensions );
        MeshGeometry* GetGeometry( uint32 index );

        uint32 GetGeometryCount() { return m_meshGeometries.size(); }
        IMeshMaterial* GetMeshMaterial() { return m_pMeshMaterial; }

    protected:
        void AddGeometry( MeshGeometry* pMeshGeometry );

        virtual shared_ptr< SceneNode > VCreateSceneNode();
        virtual const float VCalculateBoudingSphereRadius();

        IMeshMaterial* m_pMeshMaterial;
        MeshGeometryVector m_meshGeometries;
    };
}