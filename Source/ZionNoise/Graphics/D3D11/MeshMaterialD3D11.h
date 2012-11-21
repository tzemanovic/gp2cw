#pragma once
////////////////////////////////////////////////////
// Direct3D 11 mesh material
////////////////////////////////////////////////////

#include "..\IMeshMaterial.h"

namespace zn
{
    class MeshMaterialD3D11 : public IMeshMaterial
    {
    public:
        MeshMaterialD3D11();
        virtual ~MeshMaterialD3D11();

        bool VInit();
        bool CreateVertexLayout();

        void VSetProjection( const Mat4x4& mat ) 
        { 
            m_pProjectionMatrixVariable->SetMatrix( ( float* )( &mat ) ); 
        }

        void VSetView( const Mat4x4& mat ) 
        { 
            m_pViewMatrixVariable->SetMatrix( ( float* )( &mat ) ); 
        }

        void VSetWorld( const Mat4x4& mat ) 
        { 
            m_pWorldMatrixVariable->SetMatrix( ( float* )( &mat ) ); 
        }

        void VSetAbientLightColor( const Color& color )
        {
            m_pAmbientLightColourVariable->SetFloatVector( ( float* )( &color ) );
        }

        void VSetDiffuseLightColor( const Color& color )
        {
            m_pDiffuseLightColourVariable->SetFloatVector( ( float* )( &color ) );
        }

        void VSetSpecularLightColor( const Color& color )
        {
            m_pSpecularLightColourVariable->SetFloatVector( ( float* )( &color ) );
        }

        void VSetLightDirection( const fVec3& dir )
        {
            m_pLightDirectionVariable->SetFloatVector( ( float* )( &dir ) );
        }

        void VSetCameraPosition( const fVec3& dir )
        {
            m_pCameraPositionVariable->SetFloatVector( ( float* )( &dir ) );
        }

        void VSetTextures()
        {
            m_pDiffuseTextureVariable->SetResource( m_pDiffuseTexture );
            m_pEnvMapVariable->SetResource( m_pEnvMapTexture );
        }

        void VSetMaterials()
        {
            m_pAmbientMaterialVariable->SetFloatVector( ( float* )( m_ambientMaterial ) );
		    m_pDiffuseMaterialVariable->SetFloatVector( ( float* )( m_diffuseMaterial ) );
		    m_pSpecularMaterialVariable->SetFloatVector( ( float* )( m_specularMaterial ) );
		    m_pSpecularPowerVariable->SetFloat( m_specularPower );
        }

        void VBindInputLayout()
        {
            g_pGame->GetRenderer()->GetDeviceContext()->D3D11->IASetInputLayout( m_pInputLayout );
        }

        uint32 VGetPassCount()
        {
            return m_techniqueDesc.Passes;
        }

        void VApplyPass( uint32 i )
        {
            m_pPass = m_pTechnique->GetPassByIndex( i );
            m_pPass->Apply( 0, g_pGame->GetRenderer()->GetDeviceContext()->D3D11 );
        }

    protected:
        bool LoadEffectFromFile();
        bool CompileD3DShader( const string& filePath, const string& shaderModel, ID3DBlob** ppBuffer );

        string m_techniqueName;
        //effect variables
	    ID3DX11Effect* m_pEffect;
	    ID3DX11EffectTechnique* m_pTechnique;
        ID3DX11EffectPass* m_pPass;
	    //input layout
	    ID3D11InputLayout* m_pInputLayout;
	    //technique desc
	    D3DX11_TECHNIQUE_DESC m_techniqueDesc;
	    //effect variables(constants)
	    ID3DX11EffectMatrixVariable* m_pViewMatrixVariable;
	    ID3DX11EffectMatrixVariable* m_pProjectionMatrixVariable;
	    ID3DX11EffectMatrixVariable* m_pWorldMatrixVariable;
	    //Textures
	    ID3DX11EffectShaderResourceVariable* m_pDiffuseTextureVariable;
	    ID3D11ShaderResourceView *m_pDiffuseTexture;
	    //Light
	    ID3DX11EffectVectorVariable* m_pAmbientLightColourVariable;
	    ID3DX11EffectVectorVariable* m_pDiffuseLightColourVariable;
	    ID3DX11EffectVectorVariable* m_pSpecularLightColourVariable;
	    //Direction
	    ID3DX11EffectVectorVariable* m_pLightDirectionVariable;
	    //Material
	    ID3DX11EffectVectorVariable* m_pAmbientMaterialVariable;
	    ID3DX11EffectVectorVariable* m_pDiffuseMaterialVariable;
	    ID3DX11EffectVectorVariable* m_pSpecularMaterialVariable;
	    ID3DX11EffectScalarVariable* m_pSpecularPowerVariable;
	    //Camera
	    ID3DX11EffectVectorVariable* m_pCameraPositionVariable;
        //Environment
        ID3D11ShaderResourceView* m_pEnvMapTexture;
        ID3DX11EffectShaderResourceVariable* m_pEnvMapVariable;
	    //Material colours
	    Color m_ambientMaterial;
	    Color m_diffuseMaterial;
	    Color m_specularMaterial;
	    float m_specularPower;
    };
}