////////////////////////////////////////////////////
// Direct3D 11 mesh material
////////////////////////////////////////////////////

#include "ZionNoiseStd.h"
#include "MeshMaterialD3D11.h"
#include "..\Device.h"

namespace zn
{
    MeshMaterialD3D11::MeshMaterialD3D11( const string& filename ) : m_techniqueName( "Render" ), m_pEffect( NULL ), m_pTechnique( NULL ),
        m_pInputLayout( NULL ), m_pDiffuseTexture( NULL ), m_pSpecularTexture( NULL ), m_pBumpTexture( NULL ), 
        m_pParallaxTexture( NULL ), m_pEnvMapTexture( NULL ), 
        m_ambientMaterial( Color( 0.5f, 0.5f, 0.5f, 1.0f ) ), m_diffuseMaterial( Color( 0.8f, 0.8f, 0.8f, 1.0f ) ),
        m_specularMaterial( Color( 1.0f, 1.0f, 1.0f, 1.0f ) ), m_specularPower( 25.f )
    {
        m_filename = filename;
        ZeroMemory( &m_techniqueDesc, sizeof( D3D10_TECHNIQUE_DESC ) );
    }

    MeshMaterialD3D11::~MeshMaterialD3D11()
    {
        ZN_SAFE_RELEASE( m_pEnvMapTexture );
        ZN_SAFE_RELEASE( m_pParallaxTexture );
        ZN_SAFE_RELEASE( m_pBumpTexture );
        ZN_SAFE_RELEASE( m_pSpecularTexture );
        ZN_SAFE_RELEASE( m_pDiffuseTexture );
        ZN_SAFE_RELEASE( m_pInputLayout );
        ZN_SAFE_RELEASE( m_pEffect );
    }

    bool MeshMaterialD3D11::VInit()
    {
        if( LoadEffectFromFile() )
        {
            m_pTechnique = m_pEffect->GetTechniqueByName( m_techniqueName.c_str() );
            m_pTechnique->GetDesc( &m_techniqueDesc );
            if( CreateVertexLayout() )
            {
                // retrieve all variables using semantic
                m_pWorldMatrixVariable = m_pEffect->GetVariableBySemantic( "WORLD" )->AsMatrix();
	            m_pViewMatrixVariable = m_pEffect->GetVariableBySemantic( "VIEW" )->AsMatrix();
	            m_pProjectionMatrixVariable = m_pEffect->GetVariableBySemantic( "PROJECTION" )->AsMatrix();
	            m_pDiffuseTextureVariable = m_pEffect->GetVariableByName( "diffuseMap" )->AsShaderResource();
	            m_pSpecularTextureVariable = m_pEffect->GetVariableByName( "specularMap" )->AsShaderResource();
	            m_pBumpTextureVariable = m_pEffect->GetVariableByName( "bumpMap" )->AsShaderResource();
	            m_pParallaxTextureVariable = m_pEffect->GetVariableByName( "heightMap" )->AsShaderResource();
                m_pEnvMapVariable = m_pEffect->GetVariableByName( "envMap" )->AsShaderResource();
	            // lights
	            m_pAmbientLightColourVariable = m_pEffect->GetVariableByName( "ambientLightColour" )->AsVector();
	            m_pDiffuseLightColourVariable = m_pEffect->GetVariableByName( "diffuseLightColour" )->AsVector();
	            m_pSpecularLightColourVariable = m_pEffect->GetVariableByName( "specularLightColour" )->AsVector();
	            m_pLightDirectionVariable = m_pEffect->GetVariableByName( "lightDirection" )->AsVector();
	            // materials
	            m_pAmbientMaterialVariable = m_pEffect->GetVariableByName( "ambientMaterialColour" )->AsVector();
	            m_pDiffuseMaterialVariable = m_pEffect->GetVariableByName( "diffuseMaterialColour" )->AsVector();
	            m_pSpecularMaterialVariable = m_pEffect->GetVariableByName( "specularMaterialColour" )->AsVector();
	            m_pSpecularPowerVariable = m_pEffect->GetVariableByName( "specularPower" )->AsScalar();
	            // camera
	            m_pCameraPositionVariable = m_pEffect->GetVariableByName( "cameraPosition" )->AsVector();
                // booleans
                m_pUseDiffuseTextureVariable = m_pEffect->GetVariableByName( "useDiffuseTexture" )->AsScalar();
	            m_pUseSpecularTextureVariable = m_pEffect->GetVariableByName( "useSpecularTexture" )->AsScalar();
	            m_pUseBumpTextureVariable = m_pEffect->GetVariableByName( "useBumpTexture" )->AsScalar();
	            m_pUseParallaxTextureVariable = m_pEffect->GetVariableByName( "useHeightTexture" )->AsScalar();
                return true;
            }
        }
        return false;
    }

    bool MeshMaterialD3D11::CreateVertexLayout()
    {
        uint32 elementsCount = ARRAYSIZE( D3D11_LAYOUT );
        D3DX11_PASS_DESC passDesc;
        m_pTechnique->GetPassByIndex( 0 )->GetDesc( &passDesc );
        if ( FAILED( g_pGame->GetRenderer()->GetDevice()->D3D11->CreateInputLayout( D3D11_LAYOUT, elementsCount, 
            passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_pInputLayout ) ) )
        {
            return false;
        }
        return true;
    }
    
    bool MeshMaterialD3D11::VLoadDiffuseTexture( const string& filename )
    {
        wstring wFilename;
        wFilename.assign( filename.begin(), filename.end() );
        if( FAILED( D3DX11CreateShaderResourceViewFromFile( g_pGame->GetRenderer()->GetDevice()->D3D11,
            wFilename.c_str(), NULL, NULL, &m_pDiffuseTexture, NULL ) ) )
            return false;
        return true;
    }
    
    bool MeshMaterialD3D11::VLoadSpecularTexture( const string& filename )
    {
        wstring wFilename;
        wFilename.assign( filename.begin(), filename.end() );
        if( FAILED( D3DX11CreateShaderResourceViewFromFile( g_pGame->GetRenderer()->GetDevice()->D3D11,
            wFilename.c_str(), NULL, NULL, &m_pSpecularTexture, NULL ) ) )
            return false;
        return true;
    }
    
    bool MeshMaterialD3D11::VLoadBumpTexture( const string& filename )
    {
        wstring wFilename;
        wFilename.assign( filename.begin(), filename.end() );
        if( FAILED( D3DX11CreateShaderResourceViewFromFile( g_pGame->GetRenderer()->GetDevice()->D3D11,
            wFilename.c_str(), NULL, NULL, &m_pBumpTexture, NULL ) ) )
            return false;
        return true;
    }
    
    bool MeshMaterialD3D11::VLoadParallaxTexture( const string& filename )
    {
        wstring wFilename;
        wFilename.assign( filename.begin(), filename.end() );
        if( FAILED( D3DX11CreateShaderResourceViewFromFile( g_pGame->GetRenderer()->GetDevice()->D3D11,
            wFilename.c_str(), NULL, NULL, &m_pParallaxTexture, NULL ) ) )
            return false;
        return true;
    }
    
    bool MeshMaterialD3D11::VLoadEnvMapTexture( const string& filename )
    {
        wstring wFilename;
        wFilename.assign( filename.begin(), filename.end() );
        if( FAILED( D3DX11CreateShaderResourceViewFromFile( g_pGame->GetRenderer()->GetDevice()->D3D11,
            wFilename.c_str(), NULL, NULL, &m_pEnvMapTexture, NULL ) ) )
            return false;
        return true;
    }

    bool MeshMaterialD3D11::LoadEffectFromFile()
    {
        ID3DBlob* pBuffer = NULL;
        if( !CompileD3DShader( m_filename, "fx_5_0", &pBuffer ) )
        {
            return false;
        }
        if( FAILED( D3DX11CreateEffectFromMemory( pBuffer->GetBufferPointer(), pBuffer->GetBufferSize(), 0, 
            g_pGame->GetRenderer()->GetDevice()->D3D11, &m_pEffect ) ) )
        {
            ZN_SAFE_RELEASE( pBuffer );
            return false;
        }
        return true;
    }

    bool MeshMaterialD3D11::CompileD3DShader( const string& filePath, const string& shaderModel, ID3DBlob** ppBuffer )
    {
        wstring wFilePath;
        wFilePath.assign( filePath.begin(), filePath.end() );
        DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#       ifdef ZN_DEBUG
            shaderFlags |= D3DCOMPILE_DEBUG;
#       endif

        ID3DBlob* errorBuffer = 0;
        HRESULT result;

        result = D3DX11CompileFromFile( wFilePath.c_str(), 0, 0, 0, shaderModel.c_str(),
            shaderFlags, 0, 0, ppBuffer, &errorBuffer, 0 );
        if( FAILED( result ) )
        {
            ZN_SAFE_RELEASE( errorBuffer );
            return false;
        }

        ZN_SAFE_RELEASE( errorBuffer );
        return true;
    }
}