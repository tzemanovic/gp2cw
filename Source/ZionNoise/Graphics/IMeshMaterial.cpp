#pragma once
////////////////////////////////////////////////////
// mesh material interface
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "IMeshMaterial.h"
#include "D3D11\MeshMaterialD3D11.h"

namespace zn
{
    IMeshMaterial* IMeshMaterial::CreateDefault() 
    {
        IMeshMaterial* pMeshMaterial;
        switch( g_pGame->GetRendererType() )
        {
            case RendererType::D3D11:
                pMeshMaterial = new MeshMaterialD3D11();
                break;
            default:
                pMeshMaterial = NULL;
        }
        return pMeshMaterial;
    }
}